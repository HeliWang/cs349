/**
 * CS349 Winter 2014
 * Assignment 4 Demo Code
 * Jeff Avery
 */
package com.example.a4;
import android.graphics.*;
import android.util.Log;

/**
 * Class that represents a Fruit. Can be split into two separate fruits.
 */
public class Fruit {
	public static Region baseRegion = new Region(-2000,-2000,MainActivity.displaySize.x,MainActivity.displaySize.y);
	protected Path path = new Path();
    protected Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);
    protected Matrix transform = new Matrix();
    private double outlineWidth = 5;
    protected double velocityX 		=	0;
    protected double velocityY 		=	0;
    private double accelX = 0;
    protected double accelY = -9.8;
    private int	slices = 0;
    protected boolean isStrike	=	false;
    
    public boolean getIsStrike(){
    	return isStrike;
    }
    
	public static int rand(int min,int max){
		return min + (int)(Math.random() * ((max - min) + 1));
	}
	
	Fruit(){
		init();
	}

    /**
     * A fruit is represented as Path, typically populated 
     * by a series of points 
     */
    Fruit(float[] points) {
        init();
        this.path.reset();
        this.path.moveTo(points[0], points[1]);
        for (int i = 2; i < points.length; i += 2) {
            this.path.lineTo(points[i], points[i + 1]);
        }
        this.path.moveTo(points[0], points[1]);
    }

    Fruit(Region region) {
        init();
        this.path = region.getBoundaryPath();
    }

    Fruit(Path path) {
        init();
        this.path = path;
    }

    private void init() {
        this.paint.setColor(Color.BLACK);
        this.paint.setStrokeWidth(5);
        slices = 0;
    }

    /**
     * The color used to paint the interior of the Fruit.
     */
    public int getFillColor() { return paint.getColor(); }
    public void setFillColor(int color) { paint.setColor(color); }

    /**
     * The width of the outline stroke used when painting.
     */
    public double getOutlineWidth() { return paint.getStrokeWidth(); }
    public void setOutlineWidth(float newWidth) { paint.setStrokeWidth(newWidth); }

    /**
     * Concatenates transforms to the Fruit's affine transform
     */
    public void rotate(float theta) { transform.postRotate(theta); }
    public void scale(float x, float y) { transform.postScale(x, y); }
    public void translate(float tx, float ty) { transform.postTranslate(tx, ty); }

    /**
     * Returns the Fruit's affine transform that is used when painting
     */
    public Matrix getTransform() { return transform; }

    /**
     * The path used to describe the fruit shape.
     */
    public Path getTransformedPath() {
        Path originalPath = new Path(path);
        Path transformedPath = new Path();
        originalPath.transform(transform, transformedPath);
        return transformedPath;
    }
    
    public static Region getTRegion(Path p){
    	Region region = new Region();
    	region.setPath(p,Fruit.baseRegion);
    	return region;
    }
    public Region getTransformedRegion() {
    	Region region = new Region();
    	region.setPath(this.getTransformedPath(),Fruit.baseRegion);
    	return region;
    }

    /**
     * Paints the Fruit to the screen using its current affine
     * transform and paint settings (fill, outline)
     */
    public void draw(Canvas canvas) {
        // TODO BEGIN CS349
    	canvas.drawPath(this.getTransformedPath(), this.paint);
        // TODO END CS349
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
    
    public void copySpeed(Fruit f){
    	this.velocityX = f.getVelocityX();
    	this.velocityY = f.getVelocityY();
    	this.accelX = f.getAccelX();
    	this.accelY = f.getAccelY();
    }
    
    /**
     * Tests whether the line represented by the two points intersects
     * this Fruit.
     */
    public boolean intersects(PointF p1, PointF p2) {
        // TODO BEGIN CS349
    	Path temp = new Path();
    	int a = 1;
    	if(p1.y <= p2.y) a = -1;
    	temp.reset();
    	temp.moveTo(p1.x, p1.y);
    	temp.lineTo(p1.x, p1.y - a);
    	temp.lineTo(p2.x, p2.y);
    	temp.moveTo(p1.x, p1.y);
    	//temp.op(temp, this.getTransformedPath(), Path.Op.INTERSECT);
    	Region r = new Region();
    	r.setPath(temp,Fruit.baseRegion);
    	r.op(this.getTransformedRegion(), Region.Op.INTERSECT);
    	return !r.isEmpty();
    	//return !temp.isEmpty();
        // TODO END CS349
    }

    /**
     * Returns whether the given point is within the Fruit's shape.
     */
    public boolean contains(PointF p1) {
        Region region = new Region();
        boolean valid = region.setPath(getTransformedPath(), new Region());
        return valid && region.contains((int) p1.x, (int) p1.y);
    }

    /**
     * This method assumes that the line represented by the two points
     * intersects the fruit. If not, unpredictable results will occur.
     * Returns two new Fruits, split by the line represented by the
     * two points given.
     */
    public Fruit[] split(PointF p1, PointF p2) {
    	Path topPath = null;
    	Path bottomPath = null;
    	Region topRegion = null;
    	Region bottomRegion = null;
    	
    	float x1,y1,x2,y2,offset,theta,angle;
        offset = 3;
        angle = (float) (Math.PI * 6 / 360);
        
        x1 = p1.x;
        y1 = p1.y;
        x2 = p2.x;
        y2 = p2.y;
        
        if(y1>=y2);
        else{
        	x1 = x2;
        	y1 = y2;
        	x2 = p1.x;
        	y2 = p1.y;
        }
        
        theta = (float) Math.atan2(y1-y2,x1-x2); //use atan2 to prevent x2=x1 exception
        //theta = (float) (Math.PI - theta);
        
        Path intersectArea = (Path) this.getTransformedPath();
        Matrix apply = new Matrix();
        apply.postTranslate(-1 * x1,-1 * y1);
        apply.postRotate((float) (-1 * Math.toDegrees(theta)));
        intersectArea.transform(apply);
        
        
        topPath = new Path(intersectArea);
        bottomPath = new Path(intersectArea);
        topRegion = Fruit.getTRegion(topPath);
        bottomRegion = Fruit.getTRegion(bottomPath);
        
//        reset.postTranslate(x2,y2);
//        reset.postRotate(theta);
        
        Path bottom_cutout = new Path();
        bottom_cutout.reset();
        bottom_cutout.moveTo(-1000,1000);
        bottom_cutout.lineTo(-1000,0);
        bottom_cutout.lineTo(2000,0);
        bottom_cutout.lineTo(2000,1000);
        bottom_cutout.moveTo(-1000,1000);
        Region compare = Fruit.getTRegion(bottom_cutout);
        
        bottomRegion.op(compare, Region.Op.INTERSECT);
        topRegion.op(bottomRegion, Region.Op.DIFFERENCE);
        
        topPath = topRegion.getBoundaryPath();
        bottomPath = bottomRegion.getBoundaryPath();
        
        apply.reset();
        apply = new Matrix();
        apply.postRotate(angle);
        apply.postTranslate(0,-1 * offset);
        apply.postRotate((float) Math.toDegrees(theta));
        apply.postTranslate(x1,y1);
        
        topPath.transform(apply);
        
        apply = new Matrix();
        apply.postRotate(-1 * angle);
        apply.postTranslate(0,offset);
        apply.postRotate((float) Math.toDegrees(theta));
        apply.postTranslate(x1,y1);
        bottomPath.transform(apply);
        
        if(topPath.isEmpty()){
        	Log.e("fruit_ninja","top path is empty");
        }
        if(bottomPath.isEmpty()){
        	Log.e("fruit_ninja","bot path is empty");
        }
    	// TODO BEGIN CS349
        // calculate angle between points
        // rotate and flatten points passed in
        // rotate region
        // define region masks and use to split region into top and bottom
        // TODO END CS349
        ++slices;
        if (topPath != null && bottomPath != null){
        	Fruit top = new Fruit(topPath);
        	Fruit bottom = new Fruit(bottomPath);
        	top.slices = slices;
        	bottom.slices = slices;
        	top.copySpeed(this);
        	bottom.copySpeed(this);
        	top.setAccelY(top.getAccelY()*2);
        	bottom.setAccelY(bottom.getAccelY()*2);
        	top.setVelocityX(top.getVelocityX()+Fruit.rand(-80,80)/MainView.fps);
        	bottom.setVelocityX(bottom.getVelocityX()+Fruit.rand(-80,80)/MainView.fps);
        	return new Fruit[] { top, bottom };
        }
        return new Fruit[0];
    }
}
