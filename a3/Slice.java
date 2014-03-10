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
 * Class that represents slices on the screen.
 */

public class Slice{
	private int displayCounter = 0;
	private Point2D p1 = null;
	private Point2D p2 = null;
	private boolean isDrag;
	
	
	public Slice(){
		p1 = new Point2D.Double();
		p2 = new Point2D.Double();
		isDrag = false;
	}
	
	public Slice(Point2D s, Point2D e){
		p1 = s;
		p2 = e;
		isDrag = false;
	}
	public Slice(Point2D s, Point2D e,boolean i){
		p1 = s;
		p2 = e;
		isDrag = i;
	}
	public boolean getIsDrag(){
		return isDrag;
	}
	
	public void setPoints(Point2D s, Point2D e){
		p1 = s;
		p2 = e;
	}
	
    public void draw(Graphics2D g2){
    	++displayCounter;
    	int xoffset = (p1.getX()>p2.getX()?1:-1);
    	int yoffset = (p1.getY()>p2.getY()?1:-1);
//    	int[] xs = {(int)p1.getX(),(int)p2.getX()+xoffset*10,(int)p2.getX(),(int)p2.getX()+xoffset*5};
//    	int[] ys = {(int)p1.getY(),(int)p2.getY()+yoffset*5,(int)p2.getY(),(int)p2.getY()+yoffset*10};
    	int n = 4;
    	
    	int[] xs = {(int)p1.getX(),(int)p2.getX()};
    	int[] ys = {(int)p1.getY(),(int)p2.getY()};
    	n = 2;
    	
    	g2.setColor(Settings.colorSliceFill);
    	g2.fillPolygon(xs,ys,n);
    	g2.setColor(Settings.colorSliceDraw);
    	g2.drawPolygon(xs,ys,n);
    	
//	    g2.drawLine((int)p1.getX(),(int)p1.getY(),(int)p2.getX(),(int)p2.getY());
    }
    
    public boolean isHide(){
    	return (!(displayCounter < (double)Settings.displayFor));
    }
}
