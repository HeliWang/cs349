import java.awt.Color;
import java.awt.geom.Area;
import java.awt.geom.Ellipse2D;

public class Apple extends Fruit{
	private int rand(int min,int max){
		return min + (int)(Math.random() * ((max - min) + 1));
	}
	Apple(){
		super(new Area());
		int z = rand(0,Settings.width);
		fruitShape = new Area(new Ellipse2D.Double(z,Settings.height,75,75));
		fillColor    = Settings.colorApple;
		sliceColor = Settings.colorSuccess;
	    outlineColor = Color.BLACK;
		velocityY = ((double)rand(-13*10,-11*10))/10;
		velocityX = (Settings.width/2 - z)/3/Settings.fps;
	}
}
