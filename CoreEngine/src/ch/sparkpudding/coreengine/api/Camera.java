package ch.sparkpudding.coreengine.api;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Point2D;

import ch.sparkpudding.coreengine.Camera.Mode;
import ch.sparkpudding.coreengine.CoreEngine;
import ch.sparkpudding.coreengine.Lel;

/**
 * Expose camera features to lua APIs
 *
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 *
 */
public class Camera {
	private CoreEngine coreEngine;
	private static Camera instance;

	/**
	 * Get Camera API instance
	 *
	 * @return Camera
	 */
	public static Camera getInstance() {
		if (instance == null) {
			instance = new Camera();
		}

		return instance;
	}

	/**
	 * ctor
	 *
	 * @param coreEngine
	 */
	private Camera() {
		this.coreEngine = Lel.coreEngine;
	}

	/**
	 * Apply translate and scale to the context. Context must be saved and restaured
	 * manually
	 *
	 * @param g2d
	 */
	public void applyTransforms(Graphics2D g2d) {
		this.coreEngine.getCamera().applyTransforms(g2d);
	}

	/**
	 * Apply translate and scale to the context. Context must be saved and restaured
	 * manually
	 *
	 * @param g2d
	 */
	public void resetTransforms(Graphics2D g2d) {
		this.coreEngine.getCamera().resetTransforms(g2d);
	}

	/**
	 * Teleport the camera to the specified position, cancel all momentum
	 *
	 * @param x
	 * @param y
	 */
	public void setPosition(float x, float y) {
		this.coreEngine.getCamera().setPosition(x, y);
	}

	/**
	 * Set the target position for the camera to move to
	 *
	 * @param x
	 * @param y
	 */
	public void setTargetScaling(float s) {
		this.coreEngine.getCamera().setTargetScaling(s);
	}

	/**
	 * Set the target position to the current position
	 */
	public void setTargetToPosition() {
		this.coreEngine.getCamera().setTargetToPosition();
	}

	/**
	 * Center the target of the camera at the specified location. Center of entity
	 * is calculated automatically if width and height are given
	 *
	 * @param x top-left position
	 * @param y top-left position
	 * @param w width of the entity
	 * @param h height of the entity
	 */
	public void centerTargetAt(float x, float y, float w, float h) {
		this.coreEngine.getCamera().centerTargetAt(x, y, w, h);
	}

	/**
	 * Center the camera at the specified location. Center of entity is calculated
	 * automatically if width and height are given
	 *
	 * @param x top-left position
	 * @param y top-left position
	 * @param w width of the entity
	 * @param h height of the entity
	 */
	public void centerAt(float x, float y, float w, float h) {
		this.coreEngine.getCamera().centerAt(x, y, w, h);
	}

	/**
	 * Center the camera at the specified location. Center of entity is calculated
	 * automatically if width and height are given
	 *
	 * @param x top-left position
	 * @param y top-left position
	 */
	public void centerAt(float x, float y) {
		centerAt(x, y, 0, 0);
	}

	/**
	 * Center the target of camera at the specified location. Center of entity is
	 * calculated automatically if width and height are given
	 *
	 * @param x top-left position
	 * @param y top-left position
	 */
	public void centerTargetAt(float x, float y) {
		centerTargetAt(x, y, 0, 0);
	}

	/**
	 * Set the target position for the camera to move to
	 *
	 * @param x
	 * @param y
	 */
	public void setTargetPosition(float x, float y) {
		this.coreEngine.getCamera().setTargetPosition(x, y);
	}

	/**
	 * Change translate mode
	 *
	 * @param mode
	 */
	public void setMode(String mode) {
		this.coreEngine.getCamera().setTranslateMode(Mode.valueOf(mode));
	}

	/**
	 * Clear current boundary
	 */
	public void clearBoundary() {
		this.coreEngine.getCamera().setBoundary(null);
	}

	/**
	 * @param boundary the boundary to set
	 */
	public void setBoundary(float x, float y, float w, float h) {
		this.coreEngine.getCamera().setBoundary(new Rectangle((int) x, (int) y, (int) w, (int) h));
	}

	/**
	 * @param springTranslateForce the springTranslateForce to set
	 */
	public void setSpringTranslateForce(Point2D springTranslateForce) {
		this.coreEngine.getCamera().setSpringTranslateForce(springTranslateForce);
	}

	/**
	 * @param springTranslateConstant the springTranslateConstant to set
	 */
	public void setSpringTranslateConstant(Point2D springTranslateConstant) {
		this.coreEngine.getCamera().setSpringTranslateConstant(springTranslateConstant);
	}

	/**
	 * @param springTranslateSpeedCoeff the springTranslateSpeedCoeff to set
	 */
	public void setSpringTranslateSpeedCoeff(Point2D springTranslateSpeedCoeff) {
		this.coreEngine.getCamera().setSpringTranslateSpeedCoeff(springTranslateSpeedCoeff);
	}

	/**
	 * @param smoothSpeedCoeff the smoothSpeedCoeff to set
	 */
	public void setSmoothSpeedCoeff(Point2D smoothSpeedCoeff) {
		this.coreEngine.getCamera().setSmoothSpeedCoeff(smoothSpeedCoeff);
	}

	/**
	 * @param linearSpeedDelta the linearSpeedDelta to set
	 */
	public void setLinearSpeedDelta(Point2D linearSpeedDelta) {
		this.coreEngine.getCamera().setLinearSpeedDelta(linearSpeedDelta);
	}

	/**
	 * @param smoothScaleSpeedCoeff the smoothScaleSpeedCoeff to set
	 */
	public void setSmoothScaleSpeedCoeff(float smoothScaleSpeedCoeff) {
		this.coreEngine.getCamera().setSmoothScaleSpeedCoeff(smoothScaleSpeedCoeff);
	}

	/**
	 * @param scalingPoint the scalingPoint to set
	 */
	public void setScalingPoint(double x, double y) {
		this.coreEngine.getCamera().setScalingPoint(new Point2D.Double(x, y));
	}

	/**
	 * Make the camera shake
	 *
	 * @param intensity in pixel
	 * @param duration  in tick
	 */
	public void shake(float intensity, int duration) {
		this.coreEngine.getCamera().shake(intensity, duration);
	}

	/**
	 * Return true if the given rectangle is visible
	 *
	 * @param x      coordinates of the rectangle
	 * @param y      coordinates of the rectangle
	 * @param width  of the rectangle
	 * @param height of the rectangle
	 * @return true if the given rectangle is visible
	 */
	public boolean isInView(float x, float y, float width, float height) {
		return this.coreEngine.getCamera().isInView(x, y, width, height);
	}
}
