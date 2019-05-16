package ch.sparkpudding.sceneeditor.action;

import javax.swing.SwingUtilities;

import ch.sparkpudding.coreengine.Lel;
import ch.sparkpudding.coreengine.Scheduler.Trigger;
import ch.sparkpudding.coreengine.ecs.entity.Scene;
import ch.sparkpudding.sceneeditor.SceneEditor;

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
		Lel.coreEngine.getScheduler().schedule(Trigger.GAME_LOOP_START, new Runnable() {
			
			@Override
			public void run() {
				Lel.coreEngine.addScene(scene.getName(), scene);
				SwingUtilities.invokeLater(new Runnable() {
					
					@Override
					public void run() {
						SceneEditor.fireEntityListChanged();
					}
				});
			}
		});
		return true;
	}

	/**
	 * Removes scene from the game's scenes
	 */
	@Override
	public void undoAction() {
		Lel.coreEngine.getScheduler().schedule(Trigger.GAME_LOOP_START, new Runnable() {
			
			@Override
			public void run() {
				Lel.coreEngine.removeScene(scene.getName());
				SwingUtilities.invokeLater(new Runnable() {
					
					@Override
					public void run() {
						SceneEditor.fireEntityListChanged();
					}
				});
			}
		});
	}

}
