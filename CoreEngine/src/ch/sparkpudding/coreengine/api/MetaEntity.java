package ch.sparkpudding.coreengine.api;

import ch.sparkpudding.coreengine.Lel;
import ch.sparkpudding.coreengine.TaskScheduler.Trigger;
import ch.sparkpudding.coreengine.ecs.entity.Entity;

/**
 * API which serves to give meta access to entities from lua systems.
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class MetaEntity {
	private Entity entity;

	/**
	 * ctor
	 * 
	 * @param entity
	 */
	public MetaEntity(Entity entity) {
		this.entity = entity;
	}

	/**
	 * Sets the caller entity to be deleted at the end of the update
	 */
	public void delete() {
		Lel.coreEngine.getTaskScheduler().schedule(Trigger.AFTER_UPDATE, new Runnable() {

			@Override
			public void run() {
				Lel.coreEngine.deleteEntity(entity);
			}
		});
	}

	/**
	 * Sets the entity to have its specified component remove after the current
	 * update
	 * 
	 * @param componentName
	 */
	public void deleteComponent(String componentName) {
		Lel.coreEngine.getTaskScheduler().schedule(Trigger.AFTER_UPDATE, new Runnable() {

			@Override
			public void run() {
				Lel.coreEngine.removeComponent(entity, componentName);
			}
		});
	}

	/**
	 * Adds the given component to the entity, and schedules the Core Engine to
	 * update the systems after the current update
	 * 
	 * @param componentName
	 */
	public void addComponent(String componentName) {
		if (entity.add(componentName)) {
			Lel.coreEngine.getTaskScheduler().schedule(Trigger.AFTER_UPDATE, new Runnable() {

				@Override
				public void run() {
					Lel.coreEngine.notifySystemsOfNewComponent(entity, componentName);
				}
			});
		}
	}
}
