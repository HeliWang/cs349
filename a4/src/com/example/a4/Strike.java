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
public class Strike extends Fruit{
	private int x,y;
	Strike(int x,int y){
		super(new Path());
		this.x = x;
		this.y = y;
		Path p = new Path();
		p.reset();
        p.moveTo(-40,-8);
        p.lineTo(-40,8);
        p.lineTo(40,8);
        p.lineTo(40,-8);
        p.moveTo(-40, -8);
        
        p.moveTo(-8,-40);
        p.lineTo(-8,40);
        p.lineTo(8,40);
        p.lineTo(8,-40);
        p.moveTo(-8, -40);
        
        this.path = p;
        this.setFillColor(Color.RED);
	    velocityY = 0;
		velocityX = 0;
		this.rotate((float) Math.toDegrees(Math.PI/4));
		this.translate(x,y);
		
		isStrike = true;
	}
	
	
	@Override
	public boolean intersects(PointF p1, PointF p2) {
		return false;
	}
}
