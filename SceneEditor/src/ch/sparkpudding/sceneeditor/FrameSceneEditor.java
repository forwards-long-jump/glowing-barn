package ch.sparkpudding.sceneeditor;

import java.awt.BorderLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JFrame;
import javax.swing.JSplitPane;

import ch.sparkpudding.sceneeditor.SceneEditor.EditorState;
import ch.sparkpudding.sceneeditor.menu.MenuBar;
import ch.sparkpudding.sceneeditor.panel.PanelGame;
import ch.sparkpudding.sceneeditor.panel.PanelSidebarLeft;
import ch.sparkpudding.sceneeditor.panel.PanelSidebarRight;

/**
 * Main frame containing the SceneEditor and a static reference to the core
 * engine
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba<br/>
 *         Creation Date : 29 April 2019
 *
 */
@SuppressWarnings("serial")
public class FrameSceneEditor extends JFrame {
	private final String TITLE = "Scene Editor";
	private final int WIDTH = 1280;
	private final int HEIGHT = 720;

	private MenuBar menuBar;
	private PanelSidebarRight panelSidebarRight;
	private PanelSidebarLeft panelSidebarLeft;
	private PanelGame panelGame;
	private BorderLayout borderLayout;

	/**
	 * ctor
	 * 
	 * @param gameFolder the path to the folder containing the current game
	 * @throws Exception thrown if the coreEngine can't read the gameFolder
	 */
	public FrameSceneEditor() {
		init();
		setupFrame();
		setupLayout();
		addListener();

		SceneEditor.setGameState(EditorState.STOP);
	}

	/**
	 * Initialize the different element of the frame
	 */
	private void init() {
		borderLayout = new BorderLayout();

		menuBar = new MenuBar();

		panelSidebarRight = new PanelSidebarRight();
		panelSidebarLeft = new PanelSidebarLeft();
		panelGame = new PanelGame();
	}

	/**
	 * Setup the layout of the frame
	 */
	private void setupLayout() {
		setLayout(borderLayout);
		setJMenuBar(menuBar);

		add(panelSidebarLeft, BorderLayout.WEST);
		JSplitPane sp = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, panelGame, panelSidebarRight);
		sp.setDividerLocation(this.getWidth() - PanelSidebarRight.DEFAULT_PANEL_SIZE);
		add(sp, BorderLayout.CENTER);
	}

	/**
	 * Add the different listener for each element of the panel
	 */
	private void addListener() {
		SceneEditor.coreEngine.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseReleased(MouseEvent e) {
				SceneEditor.coreEngine.requestFocus();
			}
		});
	}

	/**
	 * Setup the basic value of the Frame
	 */
	private void setupFrame() {
		setSize(WIDTH, HEIGHT);
		setExtendedState(getExtendedState() | JFrame.MAXIMIZED_BOTH);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setTitle(TITLE);
		setJMenuBar(menuBar);
		setLocationRelativeTo(null);
		setVisible(true);
	}

	/**
	 * Populate all the component of the sidebarRight
	 */
	public void populateSidebarRight() {
		panelSidebarRight.populatePanel();
	}

	/**
	 * Get panelSidebarRight
	 * 
	 * @return panelSidebarRight
	 */
	public PanelSidebarRight getPanelSidebarRight() {
		return panelSidebarRight;
	}
}
