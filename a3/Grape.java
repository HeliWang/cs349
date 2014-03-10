import java.awt.Color;
import java.awt.Polygon;
import java.awt.geom.Area;
import java.awt.geom.Ellipse2D;

public class Grape extends Fruit{
	private int rand(int min,int max){
		return min + (int)(Math.random() * ((max - min) + 1));
	}
	Grape(){
		super(new Area());
		int z = rand(0,Settings.width);

		int[] xx,yy;
		if(z%2 == 0){
			xx = new int[]{z-30,z+30,z};
			yy = new int[]{Settings.height,Settings.height,Settings.height-60};
		}else{
			xx = new int[]{z-30,z,z+30};
			yy = new int[]{Settings.height-60,Settings.height,Settings.height-60};
		}
		Polygon p = new Polygon(xx,yy,3);  // This polygon represents a triangle with the above
		                                   //   vertices.
		
		fruitShape = new Area(p);
		fillColor    = Settings.colorGrape;
		sliceColor = Settings.colorSuccess;
	    outlineColor = Color.BLACK;
		velocityY = ((double)rand(-13*10,-11*10))/10;
		velocityX = (Settings.width/2 - z)/3/Settings.fps;
	}
}
