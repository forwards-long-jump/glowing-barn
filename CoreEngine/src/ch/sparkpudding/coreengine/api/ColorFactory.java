package ch.sparkpudding.coreengine.api;

import java.awt.Color;

/**
 * Helper class to generate Color objects
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class ColorFactory {
	private static ColorFactory instance;

	/**
	 * Get the instance of the ColorFactory
	 * 
	 * @return the instance of the ColorFactory
	 */
	public static ColorFactory getInstance() {
		if (instance == null) {
			instance = new ColorFactory();
		}

		return instance;
	}

	/**
	 * Singleton class has private constructor
	 */
	private ColorFactory() {
	}

	/**
	 * Create a color from rgb
	 * 
	 * @param r red value from 0 to 255
	 * @param g green value from 0 to 255
	 * @param b blue value from 0 to 255
	 * @return A Color of the specified color
	 */
	public Color fromRGB(float r, float g, float b) {
		return new Color((int) r, (int) g, (int) b);
	}

	/**
	 * Create a color from rgba
	 * 
	 * @param r red value from 0 to 255
	 * @param g green value from 0 to 255
	 * @param b blue value from 0 to 255
	 * @param a alpha value from 0 to 255
	 * @return A Color of the specified color
	 */
	public Color fromRGBA(float r, float g, float b, float a) {
		return new Color((int) r, (int) g, (int) b, (int) a);
	}
}
