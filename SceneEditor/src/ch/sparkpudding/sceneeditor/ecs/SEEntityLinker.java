package ch.sparkpudding.sceneeditor.ecs;

import ch.sparkpudding.coreengine.ecs.entity.Entity;

/**
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 15 avr. 2019
 * 
 *         Allow to track a game entity from the SceneEditor and duplicate it
 *         with it default values
 * 
 */
public class SEEntityLinker {

	private Entity gameEntity;
	private Entity editorEntity;

	/**
	 * Ctor create a SEEntity and it components as SEComponent
	 * 
	 * @param gameEntity the entity link to this SceneEditor Entity
	 */
	public SEEntityLinker(Entity gameEntity) {

		this.gameEntity = gameEntity;
		this.editorEntity = new Entity(gameEntity);

	}

	/**
	 * Getter for gameEntity
	 * 
	 * @return the gameEntity attached to this
	 */
	public Entity getGameEntity() {
		return gameEntity;
	}

	/**
	 * Getter for editorEntity
	 * 
	 * @return the gameEntity attached to this
	 */
	public Entity getEditorEntity() {
		return editorEntity;
	}
}