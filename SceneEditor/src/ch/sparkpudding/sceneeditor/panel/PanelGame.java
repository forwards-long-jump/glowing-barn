package ch.sparkpudding.sceneeditor.panel;

import java.awt.BorderLayout;

import javax.swing.JPanel;

import ch.sparkpudding.sceneeditor.SceneEditor;

/**
 * The panel which show the game
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 29 April 2019
 *
 */
@SuppressWarnings("serial")
public class PanelGame extends JPanel {

	/**
	 * ctor
	 */
	public PanelGame() {
		setupLayout();
	}

	/**
	 * Setup the layout of the panel
	 */
	private void setupLayout() {
		setLayout(new BorderLayout());

		add(SceneEditor.coreEngine, BorderLayout.CENTER);
	}
}
