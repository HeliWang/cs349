/**
 * CS349 Winter 2014
 */
import javax.swing.*;

import java.awt.*;
import java.awt.geom.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.logging.*;

/*
 * View of the main play area.
 * Displays pieces of fruit, and allows players to slice them.
 */
public class View extends JPanel implements ModelListener{
    private Model model;
    private final MouseDrag drag;
    private Timer timer;
    
    private boolean isRunning = false;
    private int missed = 0;
    
    
    private TitleView tv;
    private final static Logger LOGGER = Logger.getLogger(Fruit.class.getName());

    // Constructor
    View (Model m,TitleView tv) {
    	this.tv = tv;
        model = m;
        model.addObserver(this);
        setBackground(new Color(245,244,240));
        
        // drag represents the last drag performed, which we will need to calculate the angle of the slice
        drag = new MouseDrag();
        // add mouse listener
        addMouseListener(mouseListener);
        addMouseMotionListener(mouseListener);
        
        timer = new Timer(1000/Settings.fps,new TimerListener(this));
//    	timer.start();
    }
    
    
    public void missed(){
    	timer.stop();
    	//do stuff
    	isRunning = false;
    	
    	model.set(new ArrayList<Fruit>());
    	
    	
    	JLabel label = new JLabel("Game Over");
    	label.setFont(new Font("Serif", Font.PLAIN, 36));
	    label.setBounds(240,170,245,50);
	    
	    JLabel score = new JLabel("Score: " + tv.getScore());
	    score.setFont(new Font("Serif", Font.PLAIN, 18));
	    score.setBounds(270,240,245,30);
	    
	    JLabel time = new JLabel("Time: " + tv.getTime());
	    time.setFont(new Font("Serif", Font.PLAIN, 18));
	    time.setBounds(270,270,245,30);
	    
    	JButton reset = new JButton("New Game!");
    	this.setLayout(null);
    	reset.setBounds(250,315,150,50);
    	
    	reset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
            	restart();
            }
        });
    	this.add(label);
    	this.add(score);
    	this.add(time);
    	this.add(reset);
    	this.setVisible(true);
    	repaint();
    	validate();
    	
    	tv.reset();
    }
    
    public void restart(){
    	this.removeAll();
    	repaint();
    	validate();
    	model.set(new ArrayList<Fruit>());
    	timer = new Timer(1000/Settings.fps,new TimerListener(this));
    	timer.start();
    	isRunning = true;
    }

    // Update fired from model
    @Override
    public void update() {
        this.repaint();
    }

    // Panel size
    @Override
    public Dimension getPreferredSize() {
        return new Dimension(Settings.width,500);
    }

    // Paint this panel
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;

        // draw all pieces of fruit
        // note that fruit is responsible for figuring out where and how to draw itself
        for (Fruit s : model.getShapes()) {
            s.draw(g2);
        }
        
        // Draw the slices on the screen
        // if slices are drags (currently live), then only show one of them
        Slice s;
        boolean isDrag;
        boolean isFirst = true;
        
        ArrayList<Slice> slices = model.getSlices();
        for(int i=slices.size()-1;i>=0;--i){
        	s = slices.get(i);
        	isDrag = s.getIsDrag();
        	
        	if(isDrag && !isFirst){
        		slices.remove(i);
        		--i;
        	}else{
        	if((s.isHide() || (!isFirst && isDrag)) && !(isDrag && i == slices.size()-1)){
        		slices.remove(i);
        		--i;
        	}else{
        		s.draw(g2);
        	}
        	}
        	if(isDrag) isFirst = false;
        }
    }

    // Mouse handler
    // This does most of the work: capturing mouse movement, and determining if we intersect a shape
    // Fruit is responsible for determining if it's been sliced and drawing itself, but we still
    // need to figure out what fruit we've intersected.
    private MouseAdapter mouseListener = new MouseAdapter() {
    	
    	
        @Override
        public void mouseDragged(MouseEvent e){
        	super.mouseDragged(e);
        	model.addSlice(new Slice(drag.getStart(),e.getPoint(),true));
        }
        
        @Override
        public void mousePressed(MouseEvent e) {
            super.mousePressed(e);
            drag.start(e.getPoint());
        }

        

        @Override
        public void mouseReleased(MouseEvent e) {
            super.mouseReleased(e);
            if(isRunning){
            drag.stop(e.getPoint());

            // you could do something like this to draw a line for testing
            // not a perfect implementation, but works for 99% of the angles drawn

            model.addSlice(new Slice(drag.getStart(),drag.getEnd()));
//            Area line = Fruit.getLineArea(p1,p2);
//            model.add(new Fruit(line));
            
        	
//            int[] x = { (int) drag.getStart().getX(), (int) drag.getEnd().getX(), (int) drag.getEnd().getX(), (int) drag.getStart().getX()};
//            int[] y = { (int) drag.getStart().getY()-1, (int) drag.getEnd().getY()-1, (int) drag.getEnd().getY()+1, (int) drag.getStart().getY()+1};
//            Fruit fr = new Fruit(new Area(new Polygon(x, y, x.length)));
//            fr.setTest(true);
//            model.add(fr);

            // find intersected shapes
            Fruit s;
            ArrayList<Fruit> shapes = model.getShapes();
            ArrayList<Fruit> new_shapes = new ArrayList<Fruit>();
            for(int i=0;i<shapes.size();++i){
            	s = shapes.get(i);
                if(s.intersects(drag.getStart(), drag.getEnd())){
                	model.notifyObservers();
                    try {
                        Fruit[] newFruits = s.split(drag.getStart(), drag.getEnd());
                        
                        for (Fruit f : newFruits) {
                        	new_shapes.add(f);
                        }
                    } catch (Exception ex) {
                        System.err.println("Caught error: " + ex.getMessage());
                    }
                    shapes.remove(i);
                    --i;
                }
            }
            for(Fruit f : new_shapes){
            	shapes.add(f);
            }
            model.set(shapes);
        }
        }
    };

    class TimerListener implements ActionListener{
    	private int counter = 0;
    	private int missed = 0;
    	private View view;
    	
    	TimerListener(View v){
    		view = v;
    	}
    	
    	private int rand(int min,int max){
    		return min + (int)(Math.random() * ((max - min) + 1));
    	}
    	
        @Override
        public void actionPerformed(ActionEvent e){
        	if(++counter%(int)(Settings.fps/Settings.fruitps) == 0){
        		int z = rand(0,3);
        		Fruit ff;
		        if(z == 0){
		        	ff = new Apple();
		        }else if(z == 1){
		        	ff = new Orange();
		        }else if(z == 2){
		        	ff = new Grape();
		        }else{
		        	ff = new Watermelon();
		        }
		        model.add(ff);
        	}
        	if(missed > 0){
        		model.add(new Strike(missed*100+50,70));
        	}
        	
        	if((int)counter/(Settings.fps/Settings.fruitps) == 5){
        		Settings.fruitps*=1.5;
        	}
        	if((int)(counter/(Settings.fps/Settings.fruitps)) == 15){
        		Settings.fruitps*=1.3;
        	}
        	if((int)(counter/(Settings.fps/Settings.fruitps)) == 30){
        		Settings.fruitps*=1.9;
        	}
          
          
        	ArrayList<Fruit> shapes = model.getShapes();
        	ArrayList<Fruit> new_shapes = new ArrayList<Fruit>();
        	for(int i=0;i<shapes.size();++i){
        		Fruit f = shapes.get(i);
        		if(f.getIsStrike()) new_shapes.add(f);
        		else{
	        		f.setVelocityX(f.getVelocityX()-f.getAccelX()/Settings.fps*30);
	        		f.setVelocityY(f.getVelocityY()-f.getAccelY()/Settings.fps*30);
	        		f.translate(f.getVelocityX(),f.getVelocityY());
	        		// TODO micro optimizations
	        		if((f.getSlices() == 0 && f.getTransform().getTranslateY() <= 0
	        				&& f.getTransform().getTranslateX() >= -1 * Settings.width
	        				&& f.getTransform().getTranslateX() <= Settings.width)
	        				||
	        			(f.getSlices() > 0 && f.getTransform().getTranslateY() <= Settings.height
	        				&& f.getTransform().getTranslateX() >= -1 * Settings.width
	        				&& f.getTransform().getTranslateX() <= Settings.width)
	        				) new_shapes.add(f);
	        		else{
	        			if(f.getSlices() == 0){
		        			++missed;
		        			if(missed > Settings.nummissed) view.missed();
	        			}
	        		}
        		}
        	}
        	model.set(new_shapes);
        	if(counter%Settings.fps == 0) model.notifyTimers();
        	view.update();
        }
    }
    
    /*
     * Track starting and ending positions for the drag operation
     * Needed to calculate angle of the slice
     */
    private class MouseDrag {
        private Point2D start;
        private Point2D end;

        MouseDrag() { }

        protected void start(Point2D start) { this.start = start; }
        protected void stop(Point2D end) { this.end = end; }

        protected Point2D getStart() { return start; }
        protected Point2D getEnd() { return end; }

    }

	@Override
	public void timer() {
		// TODO Auto-generated method stub
		
	}
}
