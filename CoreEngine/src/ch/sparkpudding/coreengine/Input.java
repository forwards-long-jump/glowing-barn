package ch.sparkpudding.coreengine;

import java.awt.Point;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.swing.JPanel;

/**
 * Keeps tabs of all keyboard and mouse inputs for the game. Should be updated
 * once before all systems are.
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class Input {

	// Values read by the panel
	private List<Integer> keysPressed;
	private List<Integer> keysReleased;
	private List<Integer> mouseButtonsPressed;
	private List<Integer> mouseButtonsReleased;
	private Point mousePositionBuffer;
	private boolean mouseClickedBuffer = false;

	// Values to be read by systems
	private Map<Integer, Boolean> keys;
	private Map<Integer, Boolean> mouseButtons;
	private Point mousePosition;
	private boolean mouseClicked = false;

	private JPanel panel;

	/**
	 * Handle key and mouse actions
	 * 
	 * @param panel
	 */
	public Input(JPanel panel) {
		this.panel = panel;
		this.panel.setFocusable(true);
		createListeners();

		keysPressed = new ArrayList<Integer>();
		keysReleased = new ArrayList<Integer>();
		mouseButtonsPressed = new ArrayList<Integer>();
		mouseButtonsReleased = new ArrayList<Integer>();
		mousePositionBuffer = new Point();

		keys = new HashMap<Integer, Boolean>();
		mouseButtons = new HashMap<Integer, Boolean>();
		mousePosition = new Point();
	}

	/**
	 * Update inputs, must be called before system update
	 */
	public void update() {
		for (Integer key : keysPressed) {
			keys.put(key, true);
		}
		keysPressed.clear();

		for (Integer key : keysReleased) {
			keys.put(key, false);
		}
		keysReleased.clear();

		for (Integer key : mouseButtonsPressed) {
			mouseButtons.put(key, true);
		}
		mouseButtonsPressed.clear();

		for (Integer key : mouseButtonsReleased) {
			mouseButtons.put(key, false);
		}
		mouseButtonsReleased.clear();

		mousePosition = mousePositionBuffer;

		mouseClicked = mouseClickedBuffer;
		mouseClickedBuffer = false;
	}

	/**
	 * Add listeners to the panel
	 */
	public void createListeners() {
		panel.addKeyListener(new KeyAdapter() {

			@Override
			public void keyReleased(KeyEvent e) {
				keys.put(e.getKeyCode(), false);
			}

			@Override
			public void keyPressed(KeyEvent e) {
				keys.put(e.getKeyCode(), true);
			}
		});

		panel.addMouseListener(new MouseAdapter() {

			@Override
			public void mouseReleased(MouseEvent e) {
				mouseButtonsReleased.add(e.getButton());
			}

			@Override
			public void mousePressed(MouseEvent e) {
				mouseButtonsPressed.add(e.getButton());
			}

			@Override
			public void mouseClicked(MouseEvent e) {
				mouseClickedBuffer = true;
			}
		});

		panel.addMouseMotionListener(new MouseMotionAdapter() {

			@Override
			public void mouseMoved(MouseEvent e) {
				mousePositionBuffer = e.getPoint();
			}

			// This stays commented in case we ever want to add it later
//			@Override
//			public void mouseDragged(MouseEvent e) {
//				// TODO Auto-generated method stub
//				
//			}
		});
	}

	/**
	 * Return the state of specified key
	 * 
	 * @param keyCode
	 * @return the state of specified key
	 */
	public boolean isKeyDown(int keyCode) {
		return keys.getOrDefault(keyCode, false);
	}

	/**
	 * Return the state of specified mouse button
	 * 
	 * @param keyCode
	 * @return the state of specified mouse button
	 */
	public boolean isMouseButtonDown(int keyCode) {
		return mouseButtons.getOrDefault(keyCode, false);
	}

	/**
	 * Return true if the mouse was clicked
	 * 
	 * @return true if the mouse was clicked
	 */
	public boolean isMouseClicked() {
		return mouseClicked;
	}

	/**
	 * Return the mouse position relative to the jpanel
	 * 
	 * @return mouse position relative to the jpanel
	 */
	public Point getMousePosition() {
		return mousePosition;
	}
}
