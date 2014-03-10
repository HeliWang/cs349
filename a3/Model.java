/**
 * CS349 Winter 2014
 * Assignment 3 Demo Code
 * Jeff Avery & Michael Terry
 */
import java.io.IOException;
import java.util.ArrayList;
import java.util.Vector;
import java.util.logging.Logger;

/*
 * Class the contains a list of fruit to display.
 * Follows MVC pattern, with methods to add observers,
 * and notify them when the fruit list changes.
 */
public class Model {
  // Observer list
  private Vector<ModelListener> views = new Vector();

  // Fruit that we want to display
  private ArrayList<Fruit> shapes = new ArrayList();
  
  private ArrayList<Slice> slices = new ArrayList<Slice>();

  private final static Logger LOGGER = Logger.getLogger(Fruit.class.getName());
  
  // Constructor
  Model() {
    shapes.clear();
    slices.clear();
  }

  // MVC methods
  // These likely don't need to change, they're just an implementation of the
  // basic MVC methods to bind view and model together.
  public void addObserver(ModelListener view) {
    views.add(view);
  }

  public void notifyObservers() {
    for (ModelListener v : views) {
    	v.update();
    }
  }
  
  public void notifyTimers() {
	    for (ModelListener v : views) {
	    	v.timer();
	    }
	  }

  public void addSlice(Slice s){
	  slices.add(s);
  }
  public ArrayList<Slice> getSlices(){
	  return (ArrayList<Slice>) slices.clone();
  }
  
  // Model methods
  // You may need to add more methods here, depending on required functionality.
  // For instance, this sample makes to effort to discard fruit from the list.
  public void add(Fruit s) {
	  shapes.add(s);
  }
  
  public void set(ArrayList<Fruit> s2){
	  shapes = s2;
  }
  public ArrayList<Fruit> getShapes(){
	  return (ArrayList<Fruit>)shapes.clone();
  }
}
