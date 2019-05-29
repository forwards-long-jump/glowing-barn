package ch.sparkpudding.sceneeditor.panel;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Map;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import ch.sparkpudding.coreengine.Scheduler.Trigger;
import ch.sparkpudding.coreengine.ecs.entity.Scene;
import ch.sparkpudding.coreengine.utils.RunnableOneParameter;
import ch.sparkpudding.sceneeditor.SceneEditor;
import ch.sparkpudding.sceneeditor.action.ActionRemoveScene;
import ch.sparkpudding.sceneeditor.action.ActionRenameScene;
import ch.sparkpudding.sceneeditor.ecs.SEScene;
import ch.sparkpudding.sceneeditor.listener.EntityEventAdapter;
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

		buttonAddScene = new JButton("+");
		buttonRemoveScene = new JButton("-");
		buttonRemoveScene.setPreferredSize(buttonAddScene.getPreferredSize());

		comboBoxScenes.setEditable(true);
	}

	/**
	 * Setup the layout of the panel
	 */
	private void setupLayout() {
		setLayout(new FlowLayout());

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
		SceneEditor.coreEngine.getScheduler().notify(Trigger.SCENE_CHANGED, new RunnableOneParameter() {

			@Override
			public void run() {
				if (SceneEditor.currentScene != null) {
					SwingUtilities.invokeLater(new Runnable() {

						@Override
						public void run() {
							comboBoxScenes.setSelectedItem(((Scene) getObject()).getName());
						}
					});
				}
			}
		});

		SceneEditor.coreEngine.getScheduler().notify(Trigger.SCENE_LIST_CHANGED, new Runnable() {

			@Override
			public void run() {
				SceneEditor.updateSeSceneList();
				SwingUtilities.invokeLater(new Runnable() {

					@Override
					public void run() {
						populateComboBox(SceneEditor.seScenes);
					}
				});
			}
		});

		SceneEditor.addEntityEventListener(new EntityEventAdapter() {
			@Override
			public void entityListChanged(Map<String, SEScene> seScenes) {
				SceneEditor.updateSeSceneList();
				populateComboBox(seScenes);
			}
		});

		comboBoxScenes.addItemListener(new ItemListener() {

			@Override
			public void itemStateChanged(ItemEvent e) {
				if (e.getStateChange() == ItemEvent.SELECTED) {
					String selected = (String) comboBoxScenes.getSelectedItem();

					// Prevent modifying of main scene
					// (not the only measure taken, but helps indicate the intent to the user)
					boolean alterable = !selected.equals("main");
					comboBoxScenes.setEditable(alterable);
					buttonRemoveScene.setEnabled(alterable);

					SEScene newScene = SceneEditor.seScenes.get(selected);

					// Change scene if it exists
					if (newScene != null) {
						if (newScene != SceneEditor.currentScene) {
							panelEntityTree.clearSelectedEntity();
						}

						SceneEditor.setCurrentScene(newScene);
						SceneEditor.coreEngine.setCurrentScene(newScene.getLiveScene());
						panelEntityTree.updateListEntities(newScene);
					} else {
						new ActionRenameScene(SceneEditor.currentScene.getLiveScene().getName(), selected)
								.actionPerformed(null);
					}
				}
			}
		});

		buttonAddScene.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				new ModalScene();
			}
		});

		buttonRemoveScene.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				String toRemove = (String) comboBoxScenes.getSelectedItem();
				comboBoxScenes.setSelectedItem("main");
				new ActionRemoveScene(toRemove).actionPerformed(null);
			}
		});

	}

	private void populateComboBox(Map<String, SEScene> seScenes) {
		Scene lastScene = SceneEditor.coreEngine.getCurrentScene();

		// Populate
		comboBoxScenes.removeAllItems();
		for (SEScene scene : seScenes.values()) {
			comboBoxScenes.addItem(scene.getLiveScene().getName());
		}

		comboBoxScenes.setSelectedItem(lastScene.getName());
	}

}
