package com.example.a4;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.PointF;

public class Slice{
	private int displayCounter = 0;
	private PointF p1 = null;
	private PointF p2 = null;
	private boolean isDrag;
	protected Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);
	
	
	public Slice(){
		p1 = new PointF();
		p2 = new PointF();
		isDrag = false;
	}
	
	public Slice(PointF s, PointF e){
		p1 = s;
		p2 = e;
		isDrag = false;
	}
	public Slice(PointF s, PointF e,boolean i){
		p1 = s;
		p2 = e;
		isDrag = i;
	}
	public boolean getIsDrag(){
		return isDrag;
	}
	
	public void setPoints(PointF s, PointF e){
		p1 = s;
		p2 = e;
	}
	
    public void draw(Canvas canvas){
    	++displayCounter;
    	
    	Path temp = new Path();
    	int a = 1;
    	if(p1.y <= p2.y) a = -1;
    	temp.reset();
    	temp.moveTo(p1.x, p1.y);
    	temp.lineTo(p1.x, p1.y - a);
    	temp.lineTo(p2.x, p2.y - a);
    	temp.moveTo(p1.x, p1.y);
    	
    	canvas.drawPath(temp, this.paint);
    }
    
    public boolean isHide(){
    	return (!(displayCounter < 6));
    }
}