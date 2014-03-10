/**
 * CS349 Winter 2014
 * Assignment 3 Demo Code
 * Jeff Avery & Michael Terry
 */
import java.awt.*;
import java.awt.geom.*;
import java.util.ArrayList;
import java.util.logging.*;

/**
 * Class that represents a Fruit. Can be split into two separate fruits.
 */

public class Fruit implements FruitInterface {
    protected Area            fruitShape   = null;
    protected Color           fillColor    = Color.yellow;
    protected Color			sliceColor	=	Color.yellow;
    protected Color           outlineColor = Color.BLACK;
    private AffineTransform transform    = new AffineTransform();
    private double          outlineWidth = 5;
    protected double			velocityX 		=	0;
    protected double			velocityY 		=	0;
    private double 			accelX			= 	0;
    protected double 			accelY			= 	Settings.accelY;
    private int				slices			=	0;
    protected boolean isStrike	=	false;
    
    public boolean getIsStrike(){
    	return isStrike;
    }
    
    private final static Logger LOGGER = Logger.getLogger(Fruit.class.getName());

    /**
     * A fruit is represented using any arbitrary geometric shape.
     */
    Fruit (Area fruitShape) {
        this.fruitShape = (Area)fruitShape.clone();
    }
    
    public int getSlices(){
    	return slices;
    }
    
    public void setVelocityX(double vx){
    	velocityX = vx;
    }
    public void setVelocityY(double vy){
    	velocityY = vy;
    }
    public void setAccelX(double ax){
    	accelX = ax;
    }
    public void setAccelY(double ay){
    	accelY = ay;
    }
    
    public double getVelocityX(){
    	return velocityX;
    }
    public double getVelocityY(){
    	return velocityY;
    }
    public double getAccelX(){
    	return accelX;
    }
    public double getAccelY(){
    	return accelY;
    }

    /**
     * The color used to paint the interior of the Fruit.
     */
    public Color getFillColor() {
        return fillColor;
    }
    /**
     * The color used to paint the interior of the Fruit.
     */
    public void setFillColor(Color color) {
        fillColor = color;
    }
    /**
     * The color used to paint the outline of the Fruit.
     */
    public Color getOutlineColor() {
        return outlineColor;
    }
    public Color getSliceColor(){
    	return sliceColor;
    }
    /**
     * The color used to paint the outline of the Fruit.
     */
    public void setOutlineColor(Color color) {
        outlineColor = color;
    }
    
    /**
     * Gets the width of the outline stroke used when painting.
     */
    public double getOutlineWidth() {
        return outlineWidth;
    }

    /**
     * Sets the width of the outline stroke used when painting.
     */
    public void setOutlineWidth(double newWidth) {
        outlineWidth = newWidth;
    }

    /**
     * Concatenates a rotation transform to the Fruit's affine transform
     */
    public void rotate(double theta) {
        transform.rotate(theta);
    }

    /**
     * Concatenates a scale transform to the Fruit's affine transform
     */
    public void scale(double x, double y) {
        transform.scale(x, y);
    }

    /**
     * Concatenates a translation transform to the Fruit's affine transform
     */
    public void translate(double tx, double ty) {
        transform.translate(tx, ty);
    }

    /**
     * Returns the Fruit's affine transform that is used when painting
     */
    public AffineTransform getTransform() {
        return (AffineTransform)transform.clone();
    }

    /**
     * Creates a transformed version of the fruit. Used for painting
     * and intersection testing.
     */
    public Area getTransformedShape() {
        return fruitShape.createTransformedArea(transform);
    }

    /**
     * Paints the Fruit to the screen using its current affine
     * transform and paint settings (fill, outline)
     */
    public void draw(Graphics2D g2) {
//    	g2.setColor(outlineColor);
//    	g2.draw(getTransformedShape());
    	if(slices == 0) g2.setColor(fillColor);
    	else g2.setColor(sliceColor);
    	g2.fill(getTransformedShape());
    }
    
    public void copySpeed(Fruit f){
    	this.velocityX = f.getVelocityX();
    	this.velocityY = f.getVelocityY();
    	this.accelX = f.getAccelX();
    	this.accelY = f.getAccelY();
    	this.fillColor = f.getFillColor();
    	this.outlineColor = f.getOutlineColor();
    	this.sliceColor = f.getSliceColor();
    }
    public static Area getLineArea(Point2D p1,Point2D p2){
    	double width = 2;
        double x1,y1,x2,y2,length,theta;
        x1 = p1.getX();
        y1 = p1.getY();
        x2 = p2.getX();
        y2 = p2.getY();
        
        if(y1>=y2);
        else{
        	x1 = x2;
        	y1 = y2;
        	x2 = p1.getX();
        	y2 = p1.getY();
        }
        
        theta = -1 * (Math.PI/2 - Math.atan2(y1-y2,x1-x2)); //use atan2 to prevent x2=x1 exception
        length = Math.sqrt(Math.pow(y1-y2,2)+Math.pow(x1-x2,2));
        
        x1 = (x1+x2)/2 - width/2;
        x2 = width;
        y1 = (y1+y2)/2 - length/2;
        y2 = length;
        
        Area line = new Area(new Rectangle2D.Double(x1,y1,x2,y2));
        AffineTransform apply = new AffineTransform();
        apply.translate((x1+x2/2),(y1+y2/2));
        apply.rotate(theta);
        apply.translate(-1*(x1+x2/2),-1*(y1+y2/2));
        line = line.createTransformedArea(apply);
        return line;
    }
    /**
     * Tests whether the line represented by the two points intersects
     * this Fruit.
     */
    public boolean intersects(Point2D p1, Point2D p2) {
    	Area lineArea = Fruit.getLineArea(p1,p2);
    	
        Area intersectArea = (Area) this.getTransformedShape();
        intersectArea.intersect(lineArea);
        
        if(!intersectArea.isEmpty()){
        	return true;
        }
    	return false;
    }

    /**
     * Returns whether the given point is within the Fruit's shape.
     */
    public boolean contains(Point2D p1) {
        return this.getTransformedShape().contains(p1);
    }

    /**
     * This method assumes that the line represented by the two points
     * intersects the fruit. If not, unpredictable results will occur.
     * Returns two new Fruits, split by the line represented by the
     * two points given.
     */
    public Fruit[] split(Point2D p1, Point2D p2) throws NoninvertibleTransformException {
        Area topArea = null;
        Area bottomArea = null;
        
        double x1,y1,x2,y2,offset,theta,angle;
        offset = 2;
        angle = Math.PI * 3 / 360;
        
        x1 = p1.getX();
        y1 = p1.getY();
        x2 = p2.getX();
        y2 = p2.getY();
        
        if(y1>=y2);
        else{
        	x1 = x2;
        	y1 = y2;
        	x2 = p1.getX();
        	y2 = p1.getY();
        }
        
        theta = Math.atan2(y1-y2,x1-x2); //use atan2 to prevent x2=x1 exception
        
        Area intersectArea = (Area) this.getTransformedShape().clone();
        AffineTransform apply = new AffineTransform();
        apply.rotate(-1 * theta);
        apply.translate(-1*x2,-1*y2);
        
        
        topArea = intersectArea.createTransformedArea(apply);
        bottomArea = (Area)topArea.clone();
        topArea.intersect(new Area(new Rectangle2D.Double(-1000,-1000,2000,1000)));
        bottomArea.subtract(topArea);
        
        AffineTransform topApply = new AffineTransform();
        AffineTransform bottomApply = new AffineTransform();
        
        
        topApply.translate(x2,y2);
        topApply.rotate(theta);
        topApply.translate(0,-1 * offset);
        topApply.rotate(-1 * angle);
        
        bottomApply.translate(x2,y2);
        bottomApply.rotate(theta);
        bottomApply.translate(0,offset);
        bottomApply.rotate(angle);
        
        topArea = topArea.createTransformedArea(topApply);
        bottomArea = bottomArea.createTransformedArea(bottomApply);
        
        //rotate shape + line
        //bisect shaep above/below x-axis
        //cut shape into two fruits
        //return.
        
        
        // TODO BEGIN CS349
        // Rotate shape to align slice with x-axis
        // Bisect shape above/below x-axis (look at intersection methods!)
        // TODO END CS349
        ++slices;
        if (topArea != null && bottomArea != null){
        	Fruit top = new Fruit(topArea);
        	Fruit bottom = new Fruit(bottomArea);
        	top.slices = slices;
        	bottom.slices = slices;
        	top.copySpeed(this);
        	bottom.copySpeed(this);
        	top.setAccelY(top.getAccelY()*2);
        	bottom.setAccelY(bottom.getAccelY()*2);
        	return new Fruit[] { top, bottom };
        }
        return new Fruit[0];
     }
}
