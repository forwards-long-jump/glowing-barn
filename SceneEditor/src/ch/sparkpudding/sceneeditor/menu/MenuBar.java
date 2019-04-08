package ch.sparkpudding.sceneeditor.menu;

import javax.swing.JMenuBar;

/**
 * 
 * @author Alexandre Bianchi, Pierre B�rki, Lo�ck Jeanneret, John Leuba
 * 
 */
@SuppressWarnings("serial")
public class MenuBar extends JMenuBar {

	private MenuFile menuFile;
	private MenuEdit menuEdit;

	public MenuBar() {
		init();
		addMenu();
	}

	private void init() {
		menuFile = new MenuFile();
		menuEdit = new MenuEdit();
	}

	private void addMenu() {
		add(menuFile);
		add(menuEdit);
	}
}
