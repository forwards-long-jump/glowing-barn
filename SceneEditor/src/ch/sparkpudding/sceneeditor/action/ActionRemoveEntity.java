package ch.sparkpudding.sceneeditor.action;

import javax.swing.SwingUtilities;

import ch.sparkpudding.coreengine.Scheduler.Trigger;
import ch.sparkpudding.coreengine.ecs.entity.Scene;
import ch.sparkpudding.sceneeditor.SceneEditor;
import ch.sparkpudding.sceneeditor.ecs.SEEntity;

/**
 * The action to register the removal of an entity
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 20 May 2019
 *
 */
public class ActionRemoveEntity extends AbstractAction {

	private static final long serialVersionUID = 1L;
	private SEEntity entity;
	private Scene scene;

	/**
	 * ctor
	 * 
	 * @param scene Scene to remove
	 */
	public ActionRemoveEntity(String name, SEEntity entity, Scene scene) {
		super(name + entity.getLiveEntity().getName());
		this.entity = entity;
		this.scene = scene;
	}

	@Override
	public void undoAction() {
		SceneEditor.coreEngine.getScheduler().schedule(Trigger.GAME_LOOP_START, new Runnable() {

			@Override
			public void run() {
				if (entity.getDefaultEntity() != null) {
					scene.addDefault(entity.getDefaultEntity());
				}
				scene.add(entity.getLiveEntity());

				SwingUtilities.invokeLater(new Runnable() {

					@Override
					public void run() {
						SceneEditor.createEntityList();
					}
				});
			}
		});
	}

	@Override
	public boolean doAction() {
		SceneEditor.coreEngine.getScheduler().schedule(Trigger.GAME_LOOP_START, new Runnable() {

			@Override
			public void run() {
				if (entity.getDefaultEntity() != null) {
					SceneEditor.coreEngine.deleteDefaultEntity(entity.getDefaultEntity());
				}
				SceneEditor.coreEngine.deleteEntity(entity.getLiveEntity());

				SwingUtilities.invokeLater(new Runnable() {

					@Override
					public void run() {
						SceneEditor.createEntityList();
					}
				});
			}
		});

		return true;
	}

}
