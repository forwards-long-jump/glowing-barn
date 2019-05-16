package ch.sparkpudding.sceneeditor;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import ch.sparkpudding.coreengine.CoreEngine;

/**
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class Main {

	public static void main(String[] args) {

		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (InstantiationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (UnsupportedLookAndFeelException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		try {
			SceneEditor.coreEngine = new CoreEngine(Main.class.getResource("/emptygame").getPath(),
					Main.class.getResource("/leleditor").getPath());
		} catch (Exception e) {
			e.printStackTrace();
		}

		SceneEditor.frameSceneEditor = new FrameSceneEditor();
	}

}
