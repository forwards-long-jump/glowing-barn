package ch.sparkpudding.coreengine.ecs;

import java.awt.Graphics2D;
import java.io.File;

import org.luaj.vm2.LuaTable;
import org.luaj.vm2.LuaValue;
import org.luaj.vm2.lib.jse.CoerceJavaToLua;

import ch.sparkpudding.coreengine.CoreEngine;

public class RenderSystem extends System {
	public static final String LUA_FILE_NAME = "render.lua";
	private LuaValue renderMethod;

	/**
	 * Constructs the render system from its lua file
	 * 
	 * @param file
	 * @param coreEngine
	 */
	public RenderSystem(File file, CoreEngine coreEngine) {
		super(file, coreEngine);
		reload();
	}

	/**
	 * Get a LuaValue reference to update and isPausable lua methods
	 */
	@Override
	protected void readMethodsFromLua() {
		super.readMethodsFromLua();

		renderMethod = globals.get("render");
	}

	/**
	 * Reloads the system from file
	 */
	@Override
	public void reload() {
		super.reload();

		readMethodsFromLua();
	}
	
	/**
	 *
	 * Runs the render function of the Lua script on every entity
	 *
	 * 
	 * @param g Graphics2D context
	 */
	public void render(Graphics2D g) {
		for (LuaTable entityLua : entitiesLua) {
			renderMethod.call(entityLua, CoerceJavaToLua.coerce(g));
		}
	}
}
