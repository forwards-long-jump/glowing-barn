package ch.sparkpudding.sceneeditor.panel;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JPanel;

/**
 * 
 * @author Alexandre Bianchi, Pierre B�rki, Lo�ck Jeanneret, John Leuba
 * 
 */
@SuppressWarnings("serial")
public class PanelSidebarLeft extends JPanel {

	private JButton btnPlay;
	private JButton btnReset;

	private BoxLayout layout;

	public PanelSidebarLeft() {
		init();
		setupLayout();
	}

	private void init() {
		layout = new BoxLayout(this, BoxLayout.Y_AXIS);
		
		btnPlay = new JButton("Play");
		btnReset = new JButton("Reset");
	}

	private void setupLayout() {
		setLayout(layout);

		add(btnPlay);
		add(btnReset);
	}

}
