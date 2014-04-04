package com.example.a4;

import android.graphics.Color;
import android.graphics.Path;
import android.graphics.RectF;

public class Watermelon extends Fruit {
	Watermelon(){
		super();
		int z = rand(0,MainActivity.displaySize.x);
		Path pp = new Path();
		pp.reset();
		if(z%2 == 0){
			pp.moveTo(z-35,MainActivity.displaySize.y-100);
			pp.lineTo(z+35,MainActivity.displaySize.y-100);
			pp.lineTo(z,MainActivity.displaySize.y-70-100);
			pp.moveTo(z-35,MainActivity.displaySize.y-100);
		}else{
			pp.moveTo(z-35,MainActivity.displaySize.y-70-100);
			pp.lineTo(z,MainActivity.displaySize.y-100);
			pp.lineTo(z+35,MainActivity.displaySize.y-70-100);
			pp.moveTo(z-35,MainActivity.displaySize.y-70-100);
		}
		this.path = pp;
		this.setFillColor(Color.YELLOW);
		velocityY = -1 * Fruit.rand(250,350)/MainView.fps;
		velocityX = (MainActivity.displaySize.x/2 - z)/4/MainView.fps;
	}
}
