package ch.sparkpudding.sceneeditor.panel;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Map;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;

import ch.sparkpudding.coreengine.ecs.entity.Scene;
import ch.sparkpudding.sceneeditor.SceneEditor;
import ch.sparkpudding.sceneeditor.ecs.SEScene;
import ch.sparkpudding.sceneeditor.listener.EntityEventAdapter;
import ch.sparkpudding.sceneeditor.panel.modal.ModalComponent;
import ch.sparkpudding.sceneeditor.panel.modal.ModalScene;

/**
 * The panel which show the different scene
 *
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 29 April 2019
 *
 */
@SuppressWarnings("serial")
public class PanelScene extends JPanel {

	private PanelEntityTree panelEntityTree;

	private JComboBox<String> comboBoxScenes;
	private JButton buttonRemoveScene;
	private JButton buttonAddScene;

	private static final String TITLE = "Scenes";

	/**
	 * ctor
	 *
	 * @param panelEntityTree the panel which show the entities of a scene
	 */
	public PanelScene(PanelEntityTree panelEntityTree) {
		this.panelEntityTree = panelEntityTree;

		init();
		setupLayout();
		addListener();
	}

	/**
	 * Initialize the different element of the panel
	 */
	private void init() {
		comboBoxScenes = new JComboBox<String>();

		buttonRemoveScene = new JButton("Remove");
		buttonAddScene = new JButton("Add");

		comboBoxScenes.setEditable(true);
	}

	/**
	 * Setup the layout of the panel
	 */
	private void setupLayout() {
		setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));

		comboBoxScenes.setPreferredSize(
				new Dimension(PanelSidebarRight.BASIC_ELEMENT_WIDTH, comboBoxScenes.getPreferredSize().height));
		comboBoxScenes.setMaximumSize(
				new Dimension(PanelSidebarRight.BASIC_ELEMENT_WIDTH, comboBoxScenes.getPreferredSize().height));

		add(comboBoxScenes);
		add(buttonRemoveScene);
		add(buttonAddScene);

		setBorder(BorderFactory.createTitledBorder(TITLE));
	}

	private void addListener() {
		SceneEditor.addEntityEventListener(new EntityEventAdapter() {
			@Override
			public void entityListChanged(Map<String, SEScene> seScenes) {
				Scene lastScene = SceneEditor.coreEngine.getCurrentScene();

				// Populate
				comboBoxScenes.removeAllItems();
				for (SEScene scene : seScenes.values()) {
					comboBoxScenes.addItem(scene.getLiveScene().getName());
				}

				comboBoxScenes.setSelectedItem(lastScene.getName());
			}
		});

		comboBoxScenes.addItemListener(new ItemListener() {

			@Override
			public void itemStateChanged(ItemEvent e) {
				if (e.getStateChange() == ItemEvent.SELECTED) {
					SEScene newScene = SceneEditor.seScenes.get(comboBoxScenes.getSelectedItem());
					SceneEditor.setCurrentScene(newScene);
					SceneEditor.coreEngine.setCurrentScene(newScene.getLiveScene());
					panelEntityTree.updateListEntities(newScene);
				}
			}
		});

		comboBoxScenes.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				int index = comboBoxScenes.getSelectedIndex();
				if (index >= 0) {
					comboBoxScenes.setSelectedIndex(index);
				} else if (e.getActionCommand().equals("comboBoxEdited")) {
					// rename selected scene
				}
			}
		});

		buttonAddScene.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				new ModalScene(SceneEditor.frameSceneEditor).setVisible(true);
			}
		});

	}

}
