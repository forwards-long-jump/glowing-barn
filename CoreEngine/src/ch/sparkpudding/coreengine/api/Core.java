package ch.sparkpudding.coreengine.api;

import org.luaj.vm2.LuaValue;

import ch.sparkpudding.coreengine.CoreEngine;
import ch.sparkpudding.coreengine.ecs.entity.Entity;
import ch.sparkpudding.coreengine.ecs.system.System;

/**
 * Expose features from the CoreEngine mainly for lua apis
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class Core {
	private CoreEngine coreEngine;
	private static Core instance;
	
	/**
	 * ctor
	 * @param coreEngine
	 */
	private Core(CoreEngine coreEngine) {
		this.coreEngine = coreEngine;
	}
	
	/**
	 * Init the API. We do not test instance so init must be called before any getInstance!
	 * @param coreEngine
	 */
	public static void init(CoreEngine coreEngine) {
		instance = new Core(coreEngine);
	}
	
	/**
	 * Get Core API instance
	 * 
	 * @return Core
	 */
	public static Core getInstance() {
		return instance;
	}

	/**
	 * Get current tick
	 * @return current tick
	 */
	public int getTick() {
		return coreEngine.getTick();
	}
	
	/**
	 * Get current frameRate
	 * @return current tick
	 */
	public int getFPS() {
		return coreEngine.getFPS();
	}
	
	/**
	 * Change current scene
	 * @param name of the scene to display
	 */
	public void setScene(String name) {
		coreEngine.setScene(name);
	}
	
	/**
	 * Change current scene
	 * @param name of the scene to display
	 * @param reset or not the new scene
	 */
	public void setScene(String name, boolean reset) {
		coreEngine.setScene(name, reset);
	}
	
	/**
	 * Change current scene
	 * @param name of the scene to display
	 * @param reset or not the new scene
	 */
	public LuaValue createEntity(String templateName) {
		Entity e = new Entity(Entity.getTemplates().get(templateName));
		coreEngine.addEntity(e);
		return e.coerceToLua(System.metatableSetterMethod);
	}
}
