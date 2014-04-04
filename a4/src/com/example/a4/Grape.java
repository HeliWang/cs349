package com.example.a4;

import android.graphics.Color;
import android.graphics.Path;
import android.graphics.RectF;

public class Grape extends Fruit {
	Grape(){
		super();
		int z = rand(0,MainActivity.displaySize.x);
		Path pp = new Path();
		pp.addOval(new RectF(z,MainActivity.displaySize.y-50-100,z+100,MainActivity.displaySize.y-100),Path.Direction.CCW);
		//pp.addOval(new RectF(50,50,125,125),Path.Direction.CCW);
		this.path = pp;
		this.setFillColor(Color.CYAN);
		velocityY = -1 * Fruit.rand(250,350)/MainView.fps;
		velocityX = (MainActivity.displaySize.x/2 - z)/4/MainView.fps;
	}
}
