/**
 * CS349 Winter 2014
 * Assignment 4 Demo Code
 * Jeff Avery & Michael Terry
 */
package com.example.a4;

import android.content.Context;
import android.graphics.*;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;

import com.example.a4complete.R;

/*
 * View of the main game area.
 * Displays pieces of fruit, and allows players to slice them.
 */

public class MainView extends View implements Observer {
    private final Model model;
    private final MouseDrag drag = new MouseDrag();
    
    public static final int fps = 10;
    private double fruitps = .5;
    
    
    private boolean isRunning = false;
    private int missed = 0;
    private TopLayout topLayout;

    // Constructor
    MainView(Context context, Model m, TopLayout topLayout) {
    	super(context);
    	
        // register this view with the model
        model = m;
        model.addObserver(this);
        
        this.start();
        this.topLayout = topLayout;
        // TODO BEGIN CS349
        // test fruit, take this out before handing in!
        /*Fruit f1 = new Apple();
        model.add(f1);

        Fruit f2 = new Fruit(new float[] {0, 20, 20, 0, 40, 0, 60, 20, 60, 40, 40, 60, 20, 60, 0, 40});
        f2.translate(200, 200);
        model.add(f2);
        
        Fruit f3 = new Fruit(new float[] {0, 20, 20, 0, 40, 0, 60, 20, 60, 40, 40, 60, 20, 60, 0, 40});
        f3.translate(300, 300);
        model.add(f3);
        
        Fruit f4 = new Fruit(new float[] {0, 20, 20, 0, 40, 0, 60, 20, 60, 40, 40, 60, 20, 60, 0, 40});
        f4.translate(400, 400);
        model.add(f4);
        */
        // TODO END CS349
        
        // add controller
        // capture touch movement, and determine if we intersect a shape
        setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        // Log.d(getResources().getString(R.string.app_name), "Touch down");
                        drag.start(event.getX(), event.getY());
                        break;
                       
                    //detect DRAG
                    case MotionEvent.ACTION_MOVE:
                    	// Log.d(getResources().getString(R.string.app_name), "Touch move");
                    	drag.stop(event.getX(), event.getY());
                    	if(isRunning) model.addSlice(new Slice(drag.getStart(),drag.getEnd(),true));
                    	break;

                    case MotionEvent.ACTION_UP:
                    	// Log.d(getResources().getString(R.string.app_name), "Touch release");
                    	if(isRunning){
	                        drag.stop(event.getX(), event.getY());
	                        model.addSlice(new Slice(drag.getStart(),drag.getEnd(),true));
	
	                        // find intersected shapes
	                        ArrayList<Fruit> al = new ArrayList<Fruit>();
	                        Iterator<Fruit> i = model.getShapes().iterator();
	                        while(i.hasNext()) {
	                            Fruit s = i.next();
	                            if (s.intersects(drag.getStart(), drag.getEnd())) {
	                            	model.pp();
	                                try {
	                                    Fruit[] newFruits = s.split(drag.getStart(), drag.getEnd());
	                                    newFruits[0].setFillColor(Color.GRAY);
	                                    newFruits[1].setFillColor(Color.GRAY);
	                                    al.add(newFruits[0]);
	                                    al.add(newFruits[1]);
	
	                                    // TODO BEGIN CS349
	                                    // delete original fruit from model
	                                    // TODO END CS349
	                                } catch (Exception ex) {
	                                    Log.e("fruit_ninja", "Error: " + ex.getMessage());
	                                }
	                            } else {
	                            	al.add(s);
	                            }
	                            invalidate();
	                        }
	                        model.setShapes(al);
	                        break;
                    	}
                }
                return true;
            }
        });
    }
    
    public void start(){
    	timerHandler.postDelayed(timerRunnable, 0);
    	isRunning = true;
    }
    public void stop(){
    	timerHandler.removeCallbacks(timerRunnable);
    	isRunning = false;
    }
    public void missed(){
    	
    }
    
    
    Handler timerHandler = new Handler();
    Runnable timerRunnable = new Runnable() {
    	private int counter = 0;
    	private int missed = 0;
    	
        @Override
        public void run() {
        	if(++counter%(int)(fps/fruitps) == 0){
        		int z = Fruit.rand(0,4);
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
        		//model.add(new Strike((tt-1)*60 + 110,60));
        	}
        	
        	if((int)counter/(fps/fruitps) == 10){
        		fruitps*=1.5;
        	}
        	if((int)(counter/(fps/fruitps)) == 20){
        		fruitps*=1.3;
        	}
        	if((int)(counter/(fps/fruitps)) == 30){
        		fruitps*=1.9;
        	}
        	
        	ArrayList<Fruit> shapes = model.getShapes();
        	ArrayList<Fruit> new_shapes = new ArrayList<Fruit>();
        	for(int i=0;i<shapes.size();++i){
        		Fruit f = shapes.get(i);
        		if(f.getIsStrike()) new_shapes.add(f);
        		else{
        			float[] values = new float[9];
        			f.getTransform().getValues(values);
        			float tx = values[2];
        			float ty = values[5];
	        		f.setVelocityX(f.getVelocityX()-f.getAccelX()/fps);
	        		f.setVelocityY(f.getVelocityY()-f.getAccelY()/fps);
	        		f.translate((float) f.getVelocityX(),(float) f.getVelocityY());
	        		// TODO micro optimizations
	        		if((f.getSlices() == 0 && ty <= 0
	        				&& tx >= -1 * MainActivity.displaySize.x
	        				&& tx <= MainActivity.displaySize.x)
	        				||
	        			(f.getSlices() > 0 && ty <= 260)
	        				) new_shapes.add(f);
	        		else{
	        			if(f.getSlices() == 0){
		        			++missed;
		        			if(missed > 5){
		        				Log.d("Timer", "Timer stopped, missed more than 5");
		        				timerHandler.removeCallbacks(timerRunnable);
		        				isRunning = false;
		        				topLayout.clickButton.setVisibility(View.VISIBLE);
		        				model.setSlices(new ArrayList<Slice>());
		        				
		        				topLayout.clickButton.setOnClickListener( new OnClickListener() {
		        			        @Override
		        			        public void onClick(View v) {
		        			        	fruitps = .5;
				        				missed = 0;
				        				model.score = 0;
		        			        	model.setShapes(new ArrayList<Fruit>());
		        			        	
		        			        	topLayout.clickButton.setVisibility(View.GONE);
		        			        	
		        			        	//timerHandler.postDelayed(timerRunnable, 1000/fps);
		        			        	isRunning = true;
		        			        	timerHandler.postDelayed(timerRunnable, 0);
		        			        }
		        			    });
		        			}else{
		        				new_shapes.add(new Strike((missed-1)*100 + 40,40));
		        			}
	        			}else{
	        				Log.d("ty",":" + ty);
	        			}
	        		}
        		}
        	}
        	model.setShapes(new_shapes);
        	if(counter == 0) model.notifyObservers();
        	//view.update();
        	if(isRunning) timerHandler.postDelayed(this, 1000/fps);
        }
    };
    
    
    

    // inner class to track mouse drag
    // a better solution *might* be to dynamically track touch movement
    // in the controller above
    class MouseDrag {
        private float startx, starty;
        private float endx, endy;

        protected PointF getStart() { return new PointF(startx, starty); }
        protected PointF getEnd() { return new PointF(endx, endy); }

        protected void start(float x, float y) {
            this.startx = x;
            this.starty = y;
        }

        protected void stop(float x, float y) {
            this.endx = x;
            this.endy = y;
        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        // draw background
        setBackgroundColor(Color.WHITE);

        // draw all pieces of fruit
        for (Fruit s : model.getShapes()) {
            s.draw(canvas);
        }
        
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
	        		s.draw(canvas);
	        	}
        	}
        	if(isDrag) isFirst = false;
        }
    }

    @Override
    public void update(Observable observable, Object data) {
        invalidate();
    }
}
