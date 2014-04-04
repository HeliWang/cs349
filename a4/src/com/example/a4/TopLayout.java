package com.example.a4;

import java.util.Observable;
import java.util.Observer;

import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class TopLayout extends LinearLayout implements Observer {
	private Model model;
	private TextView tv;
	public Button clickButton;
	
	public TopLayout(Context context, Model model) {
		super(context);
		this.model = model;
		/*RelativeLayout.LayoutParams rlp = new RelativeLayout.LayoutParams(
        RelativeLayout.LayoutParams.FILL_PARENT,
        RelativeLayout.LayoutParams.FILL_PARENT);*/
		
		
		tv = new TextView(context);
		tv.setBackgroundColor(Color.BLACK);
		tv.setPadding(30,30,30,30);
        tv.setTextSize(16);
        tv.setText("Score: " + model.score + " (High: "+ model.high +")");
        
		clickButton = new Button(context);
		clickButton.setText("New Game");
		LayoutParams params = new LayoutParams(
		        LayoutParams.WRAP_CONTENT,      
		        LayoutParams.WRAP_CONTENT
		);
		params.setMargins(30,30,30,30);
		clickButton.setLayoutParams(params);
		clickButton.setOnClickListener( new OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	clickButton.setVisibility(View.GONE);
	        	
	        }
	    });
		clickButton.setVisibility(View.GONE);
		
		this.setOrientation(LinearLayout.HORIZONTAL);
		this.setGravity(Gravity.CENTER);
	    
	    this.addView(tv);
	    this.addView(clickButton);
	    
	    model.addObserver(this);
	}
	@Override
    public void update(Observable observable, Object data) {
		tv.setText("Score: " + model.score + " (High: "+ model.high +")");
        invalidate();
    }
}
