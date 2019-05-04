package ch.sparkpudding.coreengine.ecs.system;

import java.io.File;

import org.luaj.vm2.LuaError;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.lib.jse.CoerceJavaToLua;

import ch.sparkpudding.coreengine.CoreEngine;
import ch.sparkpudding.coreengine.Lel;
import ch.sparkpudding.coreengine.api.InputAPI;

/**
 * Handle systems that will be updated. These systems can also be paused
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class UpdateSystem extends System {
	private boolean pausable;
	private LuaValue updateMethod;
	private LuaValue isPausableMethod;

	/**
	 * Constructs the update system from its lua file
	 * 
	 * @param file
	 * @param coreEngine
	 */
	public UpdateSystem(File file, CoreEngine coreEngine) {
		super(file, coreEngine);
		// (re)Load system from filepath
		reload();
	}

	/**
	 * Get a LuaValue reference to update and isPausable lua methods
	 */
	@Override
	protected void readMethodsFromLua() {
		super.readMethodsFromLua();

		updateMethod = globals.get("update");
		isPausableMethod = globals.get("isPausable");
	}

	/**
	 * Reloads the system from file
	 */
	@Override
	public void reload() {
		super.reload();

		if (!loadingFailed) {
			readMethodsFromLua();

			if (isPausableMethod.isnil()) {
				pausable = false;
			} else {
				pausable = isPausableMethod.call().toboolean();
			}

			loadUpdateApis();
		}
	}

	/**
	 * Load update related APIs
	 */
	private void loadUpdateApis() {
		apiTable.set("input", CoerceJavaToLua.coerce(InputAPI.getInstance()));
	}

	/**
	 * Returns whether the system should be affected by the in-game pause
	 * 
	 * @return boolean True if pausable
	 */
	public boolean isPausable() {
		return pausable;
	}

	/**
	 * Runs the update function of the Lua script, entities can be accessed using
	 * "global" lua variables
	 */
	public void update() {
		if (!loadingFailed) {
			try {
				updateMethod.call();
			} catch (LuaError error) {
				Lel.coreEngine.notifyLuaError(error);
				error.printStackTrace();
			} catch (StackOverflowError error) {
				Lel.coreEngine.notifyLuaError(new LuaError(
						"Stack overflow in " + filepath +". This sometimes happens when trying to read an inexisting field from a component."));
			}
		}
	}
}
