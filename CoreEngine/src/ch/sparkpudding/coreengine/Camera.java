package ch.sparkpudding.coreengine;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;

import ch.sparkpudding.coreengine.utils.Collision;

/**
 * Class controlling screen position
 * 
 * @author Alexandre Bianchi, Pierre Bürki, Loïck Jeanneret, John Leuba
 * 
 */
public class Camera {
	private static final double SPRING_MIN_FORCE_REQUIRED = 0.001;
	private AffineTransform transformationState;

	/**
	 * Linear = constant speed Smooth = the further it is from the target, the
	 * faster it goes Spring = spring effect that overshoot the target and goes back
	 * to it
	 */
	public enum Mode {
		NO_FOLLOW, INSTANT, LINEAR, SMOOTH, SPRING;
	}

	private Mode translateMode;

	private Rectangle boundary;

	// Position
	private Point2D position;
	private Point2D targetPosition;

	// Spring
	private Point2D springTranslateForce;
	private Point2D springTranslateConstant;
	private Point2D springTranslateSpeedCoeff;
	// Smooth
	private Point2D smoothSpeedCoeff;
	// Linear
	private Point2D linearSpeedDelta;

	// Scaling
	private float scaling;
	private float targetScaling;
	// Smooth
	private float smoothScaleSpeedCoeff;

	// Zoom
	private Point2D scalingPoint;

	// Shaking
	private float shakeIntensity;
	private int shakeDurationLeft;

	/**
	 * ctor
	 */
	public Camera() {
		translateMode = Mode.SPRING;

		// Position
		position = new Point2D.Double(0.0, 0.0);
		targetPosition = new Point2D.Double(0.0, 0.0);

		springTranslateForce = new Point2D.Double(0.0, 0.0);
		springTranslateConstant = new Point2D.Double(1.7, 1.7);
		springTranslateSpeedCoeff = new Point2D.Double(0.2, 0.2);

		smoothSpeedCoeff = new Point2D.Double(0.1, 0.1);

		linearSpeedDelta = new Point2D.Double(15, 15);

		// Scaling
		scaling = 1f;
		targetScaling = 1f;
		// Smooth
		smoothScaleSpeedCoeff = 0.1f;

		// Zoom
		scalingPoint = new Point2D.Double(Lel.coreEngine.getGameWidth() / 2, Lel.coreEngine.getGameHeight() / 2);

		shakeDurationLeft = 0;
		shakeIntensity = 1.0f;

	}

	/**
	 * To be called in the update loop, handle moving camera to target position
	 */
	public void update() {
		double x = position.getX();
		double y = position.getY();

		// Translation
		switch (translateMode) {
		case NO_FOLLOW:
			break;
		case INSTANT:
			x = targetPosition.getX();
			y = targetPosition.getY();
			break;
		case LINEAR:
			// x
			if (Math.abs(targetPosition.getX() - x) > 1) {
				if (targetPosition.getX() > x) {
					x += linearSpeedDelta.getX();
					if (targetPosition.getX() < x) {
						x = targetPosition.getX();
					}
				} else {
					x -= linearSpeedDelta.getX();
					if (targetPosition.getX() > x) {
						x = targetPosition.getX();
					}
				}
			}

			// y
			if (Math.abs(targetPosition.getY() - y) > 1) {
				if (targetPosition.getY() > y) {
					y += linearSpeedDelta.getY();
					if (targetPosition.getY() < y) {
						y = targetPosition.getY();
					}
				} else {
					y -= linearSpeedDelta.getY();
					if (targetPosition.getY() > y) {
						y = targetPosition.getY();
					}
				}
			}
			break;
		case SMOOTH:
			x += (targetPosition.getX() - x) * smoothSpeedCoeff.getX();
			y += (targetPosition.getY() - y) * smoothSpeedCoeff.getY();
			break;
		case SPRING:
			double forceX = springTranslateForce.getX();
			double forceY = springTranslateForce.getY();

			forceX += (targetPosition.getX() - x) * springTranslateSpeedCoeff.getX();
			forceY += (targetPosition.getY() - y) * springTranslateSpeedCoeff.getY();

			forceX /= springTranslateConstant.getX();
			forceY /= springTranslateConstant.getY();

			if (Math.abs(forceX) < SPRING_MIN_FORCE_REQUIRED) {
				forceX = 0;
			}
			if (Math.abs(forceY) < SPRING_MIN_FORCE_REQUIRED) {
				forceY = 0;
			}

			x += forceX;
			y += forceY;

			springTranslateForce.setLocation(forceX, forceY);
			break;
		}

		// Scaling (smooth)
		float newTargetScaling = scaling + (targetScaling - scaling) * smoothScaleSpeedCoeff;
		float relativeScaling = newTargetScaling / scaling;

		// Scaling point is the coordinate to zoom in in "real" coordinates
		x = x * relativeScaling + scalingPoint.getX() * (relativeScaling - 1);
		y = y * relativeScaling + scalingPoint.getY() * (relativeScaling - 1);

		if (boundary != null) {
			if (boundary.getWidth() * scaling >= Lel.coreEngine.getGameWidth()) {
				x = Math.max(x, boundary.getX() * scaling);
				x = Math.min(x, (boundary.getWidth() + boundary.getX()) * scaling - Lel.coreEngine.getGameWidth());
			} else {
				x = -Lel.coreEngine.getGameWidth() / 2 + scaling * (boundary.getWidth()) / 2
						+ boundary.getX() * scaling;
			}

			if (boundary.getHeight() * scaling >= Lel.coreEngine.getGameHeight()) {
				y = Math.max(y, boundary.getY() * scaling);
				y = Math.min(y, (boundary.getHeight() + boundary.getY()) * scaling - Lel.coreEngine.getGameHeight());
			} else {
				y = -Lel.coreEngine.getGameHeight() / 2 + scaling * (boundary.getHeight()) / 2
						+ boundary.getY() * scaling;
			}
		}

		// Shaking
		if (shakeDurationLeft > 0) {
			shakeDurationLeft--;
			x += 2 * (Math.random() - 0.5) * shakeIntensity;
			y += 2 * (Math.random() - 0.5) * shakeIntensity;
		}

		position.setLocation(x, y);

		scaling = newTargetScaling;
	}

	/**
	 * Reset current forces applied to the camera to 0
	 */
	private void resetForces() {
		springTranslateForce = new Point2D.Double(0.0, 0.0);
	}

	/**
	 * Apply translate and scale to the context. Context must be saved and restored
	 * manually
	 * 
	 * @param g2d graphic context
	 */
	public void applyTransforms(Graphics2D g2d) {
		transformationState = g2d.getTransform();

		g2d.translate(-position.getX(), -position.getY());
		g2d.scale(scaling, scaling);
	}

	/**
	 * Apply translate and scale to the context. Context must be saved and restored
	 * manually
	 * 
	 * @param g2d graphic context
	 */
	public void resetTransforms(Graphics2D g2d) {
		g2d.setTransform(transformationState);
	}

	/**
	 * Teleport the camera to the specified world position, cancel all momentum
	 * 
	 * @param x coordinate
	 * @param y coordinate
	 */
	public void setWorldPosition(double x, double y) {
		position.setLocation(x * scaling, y * scaling);
		targetPosition.setLocation(position.getX(), position.getY());
		resetForces();
	}

	/**
	 * Teleport the camera to the specified position
	 * 
	 * @param x coordinate
	 * @param y coordinate
	 */
	public void setPosition(double x, double y) {
		position.setLocation(x, y);
	}

	/**
	 * Set current camera scaling
	 * 
	 * @param current scaling
	 */
	public void setScaling(float scaling) {
		this.scaling = scaling;
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
		targetPosition.setLocation(x * scaling + (w * scaling - Lel.coreEngine.getGameWidth()) / 2,
				y * scaling + (h * scaling - Lel.coreEngine.getGameHeight()) / 2);
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
		position.setLocation(x * scaling + (w * scaling - Lel.coreEngine.getGameWidth()) / 2,
				y * scaling + (h * scaling - Lel.coreEngine.getGameHeight()) / 2);
		targetPosition.setLocation(position.getX(), position.getY());
		resetForces();
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
		targetPosition.setLocation(x, y);
	}

	/**
	 * Set the target position for the camera to move to
	 * 
	 * @param x
	 * @param y
	 */
	public void setTargetScaling(float s) {
		targetScaling = s;
	}

	/**
	 * Change translate mode
	 * 
	 * @param mode
	 */
	public void setTranslateMode(Mode mode) {
		translateMode = mode;
	}

	/**
	 * @param boundary the boundary to set
	 */
	public void setBoundary(Rectangle boundary) {
		this.boundary = boundary;
	}

	/**
	 * @param springTranslateForce the springTranslateForce to set
	 */
	public void setSpringTranslateForce(Point2D springTranslateForce) {
		this.springTranslateForce = springTranslateForce;
	}

	/**
	 * @param springTranslateConstant the springTranslateConstant to set
	 */
	public void setSpringTranslateConstant(Point2D springTranslateConstant) {
		this.springTranslateConstant = springTranslateConstant;
	}

	/**
	 * @param springTranslateSpeedCoeff the springTranslateSpeedCoeff to set
	 */
	public void setSpringTranslateSpeedCoeff(Point2D springTranslateSpeedCoeff) {
		this.springTranslateSpeedCoeff = springTranslateSpeedCoeff;
	}

	/**
	 * @param smoothSpeedCoeff the smoothSpeedCoeff to set
	 */
	public void setSmoothSpeedCoeff(Point2D smoothSpeedCoeff) {
		this.smoothSpeedCoeff = smoothSpeedCoeff;
	}

	/**
	 * @param linearSpeedDelta the linearSpeedDelta to set
	 */
	public void setLinearSpeedDelta(Point2D linearSpeedDelta) {
		this.linearSpeedDelta = linearSpeedDelta;
	}

	/**
	 * @param smoothScaleSpeedCoeff the smoothScaleSpeedCoeff to set
	 */
	public void setSmoothScaleSpeedCoeff(float smoothScaleSpeedCoeff) {
		this.smoothScaleSpeedCoeff = smoothScaleSpeedCoeff;
	}

	/**
	 * @param scalingPoint the scalingPoint to set
	 */
	public void setScalingPoint(Point2D scalingPoint) {
		this.scalingPoint = scalingPoint;
	}

	/**
	 * Make the camera shake
	 * 
	 * @param intensity in pixel
	 * @param duration  in tick
	 */
	public void shake(float intensity, int duration) {
		this.shakeIntensity = intensity;
		this.shakeDurationLeft = duration;
	}

	/**
	 * Get current position of the camera
	 * 
	 * @return
	 */
	public Point2D getPosition() {
		return position;
	}

	/**
	 * Get current scaling of the camera
	 * 
	 * @return
	 */
	public float getScaling() {
		return scaling;
	}

	/**
	 * Reset forces and set target position to current position
	 */
	public void setTargetToPosition() {
		targetPosition.setLocation(position.getX(), position.getY());
		resetForces();
	}

	/**
	 * Return true if the given rectangle is visible
	 * 
	 * @param x      coordinates of the rectangle
	 * @param y      coordinates of the rectangle
	 * @param width  of the rectangle
	 * @param height of the rectangle
	 * @return
	 */
	public boolean isInView(double x, double y, double width, double height) {
		double cx = this.position.getX() / this.scaling;
		double cy = this.position.getY() / this.scaling;
		double cw = Lel.coreEngine.getGameWidth() / this.scaling;
		double ch = Lel.coreEngine.getGameHeight() / this.scaling;
		return Collision.rectIntersectRect(x, y, width, height, cx, cy, cw, ch);
	}

	/**
	 * Get target scaling
	 * 
	 * @return target scaling
	 */
	public float getTargetScaling() {
		return targetScaling;
	}

	/**
	 * Get scaling point
	 * 
	 * @return scaling point
	 */
	public Point2D getScalingPoint() {
		return scalingPoint;
	}

	/**
	 * Return current translate mode
	 * 
	 * @return current translate mode
	 */
	public Mode getTranslateMode() {
		return translateMode;
	}
}
