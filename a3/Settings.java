import java.awt.Color;

public class Settings {
	public static int fps = 35;
	
	
	/* Window Settings */
	public static int width = 800-105;
	public static int height = 500;
	
	
	/* fruits per second */
	public static double fruitps = .7;//fruit per second
	
	public static Color colorOrange = Color.orange;
	public static Color colorApple = Color.red;
	public static Color colorWatermelon = Color.green;
	public static Color colorGrape = Color.blue;
	
	public static Color colorStrike = Color.black;
	
	public static Color colorSuccess = Color.lightGray;
	
	/* Don't touch! */
	public static double accelX = 0;
	public static double accelY = (-9.8*fps/1500);
	
	public static double displayFor = .1*fps; //display slice for
	public static Color colorSliceDraw = new Color((float)92/255,(float)92/255,(float)92/255);
	public static Color colorSliceFill = new Color((float)175/255,(float)175/255,(float)175/255);
	
	public static int screen = 1;
	public static int nummissed = 5;
}
