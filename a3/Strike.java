import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.geom.Area;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

public class Strike extends Fruit{
	private int x,y;
	Strike(int x,int y){
		super(new Area());
		this.x = x;
		this.y = y;
		Area a = new Area();
		a.add(new Area(new Rectangle2D.Double(-50,-10,100,20)));
		a.add(new Area(new Rectangle2D.Double(-10,-50,20,100)));
		fruitShape = a;
		fillColor    = Settings.colorStrike;
	    outlineColor = Color.BLACK;
	    velocityY = 0;
		velocityX = 0;
		translate(x,y);
		rotate(Math.PI/4);
		isStrike = true;
	}
	
	@Override
	public void draw(Graphics2D g2) {
		g2.setColor(fillColor);
    	g2.fill(getTransformedShape());
    }
	
	@Override
	public boolean intersects(Point2D p1, Point2D p2) {
		return false;
	}
}
