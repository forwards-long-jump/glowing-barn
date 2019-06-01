package ch.sparkpudding.sceneeditor.action;

import ch.sparkpudding.coreengine.Scheduler.Trigger;
import ch.sparkpudding.coreengine.ecs.entity.Scene;
import ch.sparkpudding.sceneeditor.SceneEditor;
import ch.sparkpudding.sceneeditor.SceneEditor.EditorState;

/**
 * The action to register the addition of a new scene
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 16 May 2019
 *
 */
@SuppressWarnings("serial")
public class ActionAddScene extends AbstractAction {

	private Scene scene;


	/**
	 * ctor
	 * 
	 * @param name Name of the new scene
	 */
	public ActionAddScene(String name) {
		super("Add scene (" + name + ")");
		this.scene = new Scene(name);
	}

	/**
	 * Add scene to the game's scenes
	 */
	@Override
	public boolean doAction() {		
		if (SceneEditor.seScenes.containsKey(scene.getName())) {
			return false;
		}
		SceneEditor.coreEngine.getScheduler().schedule(Trigger.GAME_LOOP_START, new Runnable() {
			
			@Override
			public void run() {
				SceneEditor.coreEngine.addScene(scene.getName(), scene);
				SceneEditor.coreEngine.setCurrentScene(scene, SceneEditor.getGameState() == EditorState.STOP);
			}
		});
		return true;
	}

	/**
	 * Removes scene from the game's scenes
	 */
	@Override
	public void undoAction() {
		SceneEditor.coreEngine.getScheduler().schedule(Trigger.GAME_LOOP_START, new Runnable() {
			
			@Override
			public void run() {
				SceneEditor.coreEngine.setScene("main", false, SceneEditor.getGameState() == EditorState.STOP);
				SceneEditor.coreEngine.deleteScene(scene.getName());
			}
		});
	}

}
