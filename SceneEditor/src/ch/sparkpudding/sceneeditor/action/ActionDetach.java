package ch.sparkpudding.sceneeditor.action;

import ch.sparkpudding.coreengine.ecs.component.Component;
import ch.sparkpudding.sceneeditor.SceneEditor;

/**
 * Detach a component from its template, allowing manual edition in the Scene
 * Editor
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 20 May 2019
 * 
 */
@SuppressWarnings("serial")
public class ActionDetach extends AbstractAction {

	private Component component;

	/**
	 * ctor
	 * 
	 * @param component Component to detach
	 */
	public ActionDetach(Component component) {
		// TODO: Use entity to attach	
		super("Detach component " + component.getName());
		this.component = component;
	}

	@Override
	public boolean doAction() {
		component.setAttached(false, true);
		SceneEditor.fireSelectedEntityChanged();
		return true;
	}

	@Override
	public void undoAction() {
		component.setAttached(true, true);
		SceneEditor.fireSelectedEntityChanged();
	}

}
