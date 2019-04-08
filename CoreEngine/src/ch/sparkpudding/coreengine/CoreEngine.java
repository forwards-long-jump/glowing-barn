package ch.sparkpudding.coreengine;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.JPanel;
import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

import ch.sparkpudding.coreengine.ecs.Component;
import ch.sparkpudding.coreengine.ecs.Entity;
import ch.sparkpudding.coreengine.ecs.Field;
import ch.sparkpudding.coreengine.ecs.Scene;
import ch.sparkpudding.coreengine.filereader.LelFile;
import ch.sparkpudding.coreengine.filereader.XMLParser;

/**
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class CoreEngine {

	private double msPerUpdate = (1000 / 60);
	private boolean exit = false;
	
	private JPanel panel;
	public Input input;
	
	private LelFile lelFile;
	
	private Map<String, Component> componentTemplates;
	private Map<String, Entity> entityTemplates;
	private Map<String, Scene> scenes;
	private Scene currentScene;
	
	private List<System> systems;
	private System renderSystem;	

	public CoreEngine(JPanel panel, String gameFolder) throws Exception {
		this.panel = panel;
		this.input = new Input(panel);
		
		this.lelFile = new LelFile(gameFolder);
		populateComponentTemplates();
		populateEntityTemplates();
		populateScenes();
		loadSystems();
		
		
		new Thread(() -> {
			startGame();
		}).start();
	}

	/**
	 * Populates systems list with system files
	 */
	private void loadSystems() {
		systems = new ArrayList<System>();
		renderSystem = null;
	}

	/**
	 * Populates scenes list with scene files
	 */
	private void populateScenes() {
		scenes = new HashMap<String, Scene>();
		currentScene = null;
	}

	/**
	 * Populates entity templates list with entity template files
	 */
	private void populateEntityTemplates() {
		// TODO Auto-generated method stub
		
	}

	/**
	 * Populates component templates list with component template files
	 */
	private void populateComponentTemplates() throws ParserConfigurationException, SAXException, IOException {
		componentTemplates = new HashMap<String, Component>();
		for (File xmlFile : lelFile.getComponentsXML()) {
			Component c = new Component(XMLParser.parse(xmlFile));
			componentTemplates.put(c.getType(), c);
		}
		for (Entry<String, Component> components : componentTemplates.entrySet()) {
			System.out.println(components.getKey() +" :");
			for (Entry<String, Field> fields : components.getValue().getFields().entrySet())
			{
				System.out.println(" " + fields.getKey() + " -> " + fields.getValue().getValue());				
			}
			System.out.println();
		}
	}

	/**
	 * Runs update and render loops
	 */
	private void startGame() {
		double previous = System.currentTimeMillis();
		double lag = 0.0;

		while (!exit) {
			double current = System.currentTimeMillis();
			double elapsed = current - previous;

			previous = current;
			lag += elapsed;

			while (lag >= msPerUpdate) {
				update();
				lag -= msPerUpdate;
			}

			render();
		}
	}

	/**
	 * Runs all systems once
	 */
	private void update() {
		// TODO: Update logic
		// for 
	}

	/**
	 * Runs the renderer system
	 */
	private void render() {
		// TODO: Render logic
		// using panel and renderSystem
	}
	
	/**
	 * Pauses all systems indescriminately
	 */
	public void pauseAll()
	{
		// TODO: pause
	}
	
	/**
	 * Pauses all systems which are labelled "pausable"
	 */
	public void pause()
	{
		// TODO: pause (toggle)
	}
	
	/**
	 * Add scene to scenes list
	 * @param name Name of the scene
	 * @param s Scene
	 */
	public void addScene(String name, Scene s)
	{
		scenes.put(name, s);
	}
	
	/**
	 * Sets scene as current scene, without reloading
	 * @param name Name of the scene
	 */
	public void setScene(String name)
	{
		setScene(name, false);
	}
	
	/**
	 * Sets scene as current scene, and reloads it if demanded
	 * @param name Name of the Scene
	 * @param reset The scene will be reloaded when set to true
	 */
	public void setScene(String name, boolean reset)
	{
		// TODO: set current scene
	}
	
	/**
	 * Resets current scene
	 */
	public void resetScene()
	{
		// TODO: reset current scene
	}
}
