/**
 * CS349 Winter 2014
 * Assignment 3 Demo Code
 * Jeff Avery & Michael Terry
 */
import javax.imageio.ImageIO;
import javax.swing.*;

import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.logging.Logger;

/*
 * View to display the Title, and Score
 * Score currently just increments every time we get an update
 * from the model (i.e. a new fruit is added).
 */
public class TitleView extends JPanel implements ModelListener {
  private Model model;
  private JLabel timeLabel, scoreLabel;
  private int count = 0;
  private int time = 0;
  

  private final static Logger LOGGER = Logger.getLogger(Fruit.class.getName());
  
  // Constructor requires model reference
  TitleView (Model model) {
	  this.model = model;
	  this.model.addObserver(this);
	  
	  this.setLayout(new GridBagLayout());
	  GridBagConstraints gbc = new GridBagConstraints();
	  
	  JLabel bgImage = new JLabel(new ImageIcon("images/bgt2.png"));
	  bgImage.setPreferredSize(new Dimension(800,30));
	  
	  timeLabel = new JLabel("time");
	  timeLabel.setPreferredSize(new Dimension(200,30));
	  JLabel timeImage = new JLabel(new ImageIcon("images/time.png"));
	  timeImage.setPreferredSize(new Dimension(100,30));
	  
	  JLabel divider = new JLabel();
	  divider.setPreferredSize(new Dimension(300,30));
	  
	  scoreLabel = new JLabel();
	  scoreLabel.setPreferredSize(new Dimension(100,30));
	  JLabel scoreImage = new JLabel(new ImageIcon("images/score.png"));
	  scoreImage.setPreferredSize(new Dimension(100,30));
	  
	  
	  gbc.gridx = 0;
      gbc.gridy = 0;
	  this.add(timeImage,gbc);
	  gbc.gridx = 1;
	  this.add(timeLabel,gbc);
	  
	  gbc.gridx = 2;
	  this.add(divider,gbc);
	  
	  gbc.gridx = 3;
	  this.add(scoreImage,gbc);
	  gbc.gridx = 4;
	  this.add(scoreLabel,gbc);
	  
	  gbc.gridx = 0;
      gbc.gridy = 1;
      gbc.gridwidth=5;
      this.add(bgImage,gbc);
	  
	  
	  
	  
//    time = new JLabel();
//
//    // use border layout so that we can position labels on the left and right
//    this.setLayout(new BorderLayout());
//    
//    
//    this.add(time, BorderLayout.WEST);
//    this.add(score, BorderLayout.EAST);
//    this.add(bg,BorderLayout.NORTH);
  }

  // Panel size
  @Override
  public Dimension getPreferredSize() {
    return new Dimension(800,30+30);
  }

  // Update from model
  // This is ONLY really useful for testing that the view notifications work
  // You likely want something more meaningful here.
  @Override
  public void update(){
    count++;
    paint(getGraphics());
  }
  
  public void timer(){
	  ++time;
	  paint(getGraphics());
  }

  public void reset(){
	  time = 0;
	  count = 0;
  }
  // Paint method
  @Override
  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    String hour = new String(((int)(time/60) >= 10?"":"0") + (int)(time/60));
    String minute = new String((time%60 >= 10?"":"0") + time%60);
    
    
    scoreLabel.setText(String.valueOf(count));
    timeLabel.setText(hour + ":" + minute);
  }
  
  public String getScore(){
	  return String.valueOf(count);
  }
  public String getTime(){
	  String hour = new String(((int)(time/60) >= 10?"":"0") + (int)(time/60));
	    String minute = new String((time%60 >= 10?"":"0") + time%60);
	  return hour + ":" + minute;
  }
}
