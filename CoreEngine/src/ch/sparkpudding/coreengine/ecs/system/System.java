package ch.sparkpudding.coreengine.ecs.system;

import java.io.File;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.luaj.vm2.Globals;
import org.luaj.vm2.LoadState;
import org.luaj.vm2.LuaError;
import org.luaj.vm2.LuaTable;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.Varargs;
import org.luaj.vm2.compiler.LuaC;
import org.luaj.vm2.lib.PackageLib;
import org.luaj.vm2.lib.StringLib;
import org.luaj.vm2.lib.jse.CoerceJavaToLua;
import org.luaj.vm2.lib.jse.JseBaseLib;
import org.luaj.vm2.lib.jse.JseMathLib;

import ch.sparkpudding.coreengine.Lel;
import ch.sparkpudding.coreengine.api.Camera;
import ch.sparkpudding.coreengine.api.Core;
import ch.sparkpudding.coreengine.api.Resource;
import ch.sparkpudding.coreengine.api.Sound;
import ch.sparkpudding.coreengine.ecs.entity.Entity;
import ch.sparkpudding.coreengine.utils.Pair;

/**
 * Read components required by a lua script, builds a list of entities affected
 * by this system that can be passed to lua functions. Expose CoreEngine APIs
 * Part of the ECS design pattern
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public abstract class System {
	protected String filepath;
	private String name;

	// named lists of required components
	protected Map<String, List<String>> componentGroups;
	// named lists of entities having the above required components
	private Map<String, List<Entity>> entityGroups;

	// list sorted by z-index, allowing to use render
	protected List<Pair<String, Entity>> sortedEntities;
	// map containing lua functions (if defined) associated to a group
	protected Map<String, LuaValue> componentGroupsLuaFunctions;

	private LuaValue getRequiredComponentsMethod;

	protected LuaValue apiTable;
	protected Globals globals;

	protected boolean loadingFailed;

	// Systems should use this to execute their lua in a safe manner
	Thread sandboxThread;
	protected ExecutorService executor;
	protected static final int MAX_EXECUTION_TIME_IN_SECONDS = 3;

	/**
	 * Sort sortedEntities using zIndex
	 */
	public void sortEntities() {
		sortedEntities.sort(new Comparator<Pair<String, Entity>>() {
			@Override
			public int compare(Pair<String, Entity> arg0, Pair<String, Entity> arg1) {
				if (arg0.second().getZIndex() > arg1.second().getZIndex()) {
					return 1;
				} else if (arg0.second().getZIndex() < arg1.second().getZIndex()) {
					return -1;
				} else {
					return 0;
				}
			}
		});
	}

	/**
	 * Constructs the system from the Lua file
	 * 
	 * @param file Lua script file
	 */
	public System(File file) {
		this.filepath = file.getAbsolutePath();
		this.name = file.getName();
		executor = Executors.newFixedThreadPool(1);

		// (re)Load this system
		reload();
	}

	/**
	 * (re)Loads the system from file
	 */
	public void reload() {
		globals = new Globals();
		componentGroups = new HashMap<String, List<String>>();
		entityGroups = new HashMap<String, List<Entity>>();
		sortedEntities = new ArrayList<Pair<String, Entity>>();
		componentGroupsLuaFunctions = new HashMap<String, LuaValue>();
		loadingFailed = false;

		loadLuaLibs();
		// Compilation error, do not load this system
		if (!loadLuaSystem()) {
			loadingFailed = true;
		} else {
			readMethodsFromLua();
			loadApis();
			loadRequiredComponents();
		}
	}

	/**
	 * Load APIs and make them accessible trough the "game" variable
	 */
	private void loadApis() {
		apiTable = new LuaTable();
		globals.set("game", apiTable);

		apiTable.set("core", CoerceJavaToLua.coerce(Core.getInstance()));
		apiTable.set("camera", CoerceJavaToLua.coerce(Camera.getInstance()));
		apiTable.set("resources", CoerceJavaToLua.coerce(Resource.getInstance()));
		apiTable.set("sound", CoerceJavaToLua.coerce(Sound.getInstance()));
	}

	/**
	 * Load basic libraries that are exposed to systems
	 */
	private void loadLuaLibs() {
		globals.load(new JseBaseLib());
		globals.load(new PackageLib());
		globals.load(new JseMathLib());
		globals.load(new StringLib());

		LoadState.install(globals); // http://luaj.org/luaj/3.0/api/org/luaj/vm2/LoadState.html
		LuaC.install(globals); // Install the compiler
	}

	/**
	 * Load the system from the specified filepath
	 */
	private boolean loadLuaSystem() {
		try {
			globals.get("dofile").call(LuaValue.valueOf(filepath));
			return true;
		} catch (LuaError error) {
			Lel.coreEngine.notifyGameError(error);
		} catch (Exception error) {
			Lel.coreEngine.notifyGameError(error);
		}

		return false;
	}

	/**
	 * Get a LuaValue reference to all methods that should be defined in all system
	 * globals
	 */
	protected void readMethodsFromLua() {
		getRequiredComponentsMethod = globals.get("getRequiredComponents");
	}

	/**
	 * Updates the component names list according to lua file
	 */
	private void loadRequiredComponents() {
		componentGroups.clear();
		componentGroupsLuaFunctions.clear();
		LuaTable list = null;

		try {
			list = (LuaTable) getRequiredComponentsMethod.call(); // Return { entity = {"comp1", "comp2"}}
		} catch (ClassCastException error) {
			Lel.coreEngine.notifyGameError(new Exception(filepath + ": could not parse required components."));
			loadingFailed = true;
			return;
		} catch (LuaError error) {
			Lel.coreEngine.notifyGameError(new Exception(filepath + ": missing function getRequiredComponents."));
			loadingFailed = true;
			return;
		}
		// list iteration in LuaJ
		LuaValue key = LuaValue.NIL;
		Varargs entry = list.next(key);

		// entry.arg(1): key
		// entry.arg(2): value

		// entry.arg(2) is either {"comp1", "comp2"} or "comp" depending on the returned
		// value
		if (entry.arg(2).istable()) {
			// System needs multiple lists of entities
			while (!(key = entry.arg(1)).isnil()) {
				List<String> components = new ArrayList<String>();
				String groupName = entry.arg(1).tojstring();

				LuaValue innerKey = LuaValue.NIL;
				Varargs innerEntry = entry.arg(2).next(innerKey);
				// Read all strings from the table
				while (!(innerKey = innerEntry.arg(1)).isnil()) {
					components.add(innerEntry.arg(2).tojstring());
					innerEntry = entry.arg(2).next(innerKey);
				}

				componentGroups.put(groupName, components);

				entry = list.next(key);
			}

		} else {
			// System needs only one list of entities
			List<String> components = new ArrayList<String>();
			// Read all strings from the table
			while (!(key = entry.arg(1)).isnil()) {
				components.add(entry.arg(2).tojstring());
				entry = list.next(key);
			}
			componentGroups.put("entities", components);
		}
	}

	/**
	 * Sets the entities list, to be called after a scene change
	 * 
	 * @param newEntities List of entities of the new scene
	 */
	public void setEntities(List<Entity> newEntities) {
		sortedEntities.clear();
		for (String listName : componentGroups.keySet()) {
			setEntityList(newEntities, listName);
			addEntityGroupToGlobals(listName);
		}
	}

	/**
	 * Create entityList from given entities.
	 * 
	 * @param newEntities Entities to insert into lists
	 * @param listName    Name of the entity list
	 */
	private void setEntityList(List<Entity> newEntities, String listName) {
		List<String> componentList = componentGroups.get(listName);
		List<Entity> entities = new ArrayList<Entity>();

		// Check entities for compatibility with system
		for (Entity entity : newEntities) {
			if (entity.hasComponents(componentList)) {
				entities.add(entity);
				sortedEntities.add(new Pair<String, Entity>(listName, entity));
			}
		}

		entityGroups.put(listName, entities);
		sortEntities();
	}

	/**
	 * Once the entity groups are built, call this function to add them to the Lua
	 * gloabls
	 * 
	 * @param listName name of an entityGroup
	 */
	private void addEntityGroupToGlobals(String listName) {

		List<Entity> entities = entityGroups.get(listName);

		// Build Lua instances of entities
		LuaTable entitiesTableLua = new LuaTable();
		for (int i = 0; i < entities.size(); ++i) {
			// TODO prevent accessing all components
			// Lua table starts at 1
			entitiesTableLua.set(i + 1, entities.get(i).getLuaEntity());
		}

		// Lua code has access to all of these entities via the name of the list
		globals.set(listName, entitiesTableLua);
	}

	/**
	 * Check if an entity should be handled by this system and add it if it's the
	 * case
	 * 
	 * @param e entity
	 */
	public void tryAdd(Entity entity) {
		for (Entry<String, List<String>> componentList : componentGroups.entrySet()) {
			// Check entities for compatibility with system
			if (entity.hasComponents(componentList.getValue())) {
				entityGroups.get(componentList.getKey()).add(entity);
				sortedEntities.add(new Pair<String, Entity>(componentList.getKey(), entity));

				LuaTable entityGroup = (LuaTable) globals.get(componentList.getKey());
				// TODO prevent accessing all components
				entityGroup.set(entityGroup.keyCount() + 1, entity.getLuaEntity());
			}
		}

		sortEntities();
	}

	/**
	 * Finds whether the entity is in the system's list and removes it if found
	 * 
	 * @param entity
	 */
	public void tryRemove(Entity entity) {
		for (Entry<String, List<Entity>> entityList : entityGroups.entrySet()) {
			List<Entity> entities = entityList.getValue();
			for (int i = 0; i < entities.size(); i++) {
				if (entities.get(i) == entity) {
					entities.remove(i);
					addEntityGroupToGlobals(entityList.getKey());
					break;
				}
			}
		}

		for (int i = 0; i < sortedEntities.size(); i++) {
			Pair<String, Entity> entityPair = sortedEntities.get(i);
			if (entityPair.second() == entity) {
				sortedEntities.remove(i);
				i--;
			}
		}
	}

	/**
	 * Receives an entity and the name of a newly removed component of it, and
	 * checks if it should be forgotten from this system
	 * 
	 * @param entity        Entity which has had its component removed
	 * @param componentName Name of the component which was removed
	 */
	public void notifyRemovedComponent(Entity entity, String componentName) {
		for (Entry<String, List<Entity>> entityList : entityGroups.entrySet()) {
			if (componentGroups.get(entityList.getKey()).contains(componentName)) {
				// any system which requires the removed component will remove the entity
				entityList.getValue().remove(entity);
				addEntityGroupToGlobals(entityList.getKey());
			}
		}

		for (int i = 0; i < sortedEntities.size(); i++) {
			Pair<String, Entity> entityPair = sortedEntities.get(i);
			if (entity == entityPair.second() && componentGroups.get(entityPair.first()).contains(componentName)) {
				sortedEntities.remove(i);
				i--;
			}
		}
	}

	/**
	 * Receives an entity and the name of a newly added component of it, and checks
	 * if it should be added to this system
	 * 
	 * @param entity        Entity which has had its component added
	 * @param componentName Name of the component which was removed
	 */
	public void notifyNewComponent(Entity entity, String componentName) {
		for (String listName : entityGroups.keySet()) {
			// we must first check if the list needs the new component, lest we add the
			// entity twice to the system
			List<String> componentList = componentGroups.get(listName);
			if (componentList.contains(componentName) && entity.hasComponents(componentGroups.get(listName))) {
				entityGroups.get(listName).add(entity);
				sortedEntities.add(new Pair<String, Entity>(listName, entity));
				addEntityGroupToGlobals(listName);
				sortEntities();
				// LuaTable entityGroup = (LuaTable) globals.get(entityList.getKey());
				// TODO prevent accessing all components
				// entityGroup.set(entityGroup.keyCount() + 1, entity.getLuaEntity());
			}
		}
	}

	/**
	 * Return the filepath of the system
	 * 
	 * @return the filepath of the system
	 */
	public String getFilepath() {
		return filepath;
	}

	/**
	 * Return the name of the system
	 * 
	 * @return the name of the system
	 */
	public String getName() {
		return name;
	}

	/**
	 * Return the map of component group
	 * 
	 * @return the map of component group
	 */
	public Map<String, List<String>> getComponentGroups() {
		return componentGroups;
	}
}
