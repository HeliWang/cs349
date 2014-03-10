/**
 * CS349 Winter 2014
 * Assignment 3 Demo Code
 * Jeff Avery & Michael Terry
 */
import javax.imageio.ImageIO;
import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.logging.Logger;

public class Main {
	static private JFrame frame;
	
  static private Model model;
  static private View view;
  static private TitleView title;
  
  static private StartView sv;

  private final static Logger LOGGER = Logger.getLogger(Fruit.class.getName());
  /*
   * Main entry point for the application
   */
  public static void main(String[] args) {
    // instantiate your model and views
    // add any new views here
    model = new Model();
    title = new TitleView(model);
    view = new View(model,title);

    sv = new StartView();
    
    // customize the title and any other top-level settings
    frame = new JFrame("Shape Cutter");
    frame.setMinimumSize(new Dimension(Settings.width,Settings.height));
    frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    frame.setLayout(new BorderLayout());
    
	
    
    JLabel bgl = new JLabel(new ImageIcon("images/bgl.png"));
    bgl.setPreferredSize(new Dimension(57,500));
    final JLabel bgt = new JLabel(new ImageIcon("images/bgt.png"));
    bgt.setPreferredSize(new Dimension(800,30+30));
    JLabel bgb = new JLabel(new ImageIcon("images/bgb.png"));
    bgb.setPreferredSize(new Dimension(800,47));
    JLabel bgr = new JLabel(new ImageIcon("images/bgr.png"));
    bgr.setPreferredSize(new Dimension(48,500));
    

    frame.add(bgl,BorderLayout.WEST);
    frame.add(bgr,BorderLayout.EAST);
    frame.add(bgt,BorderLayout.NORTH);
    frame.add(bgb,BorderLayout.SOUTH);
    
    frame.add(sv,BorderLayout.CENTER);
    
    frame.pack();
    frame.setVisible(true);
    
    sv.getStartButton().addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
        	frame.remove(sv);
            frame.remove(bgt);
            
        	frame.add(view,BorderLayout.CENTER);
            frame.add(title,BorderLayout.NORTH);
            
            view.start();
            frame.pack();
            frame.repaint();
            frame.validate();
        }
    });
    
  }
}
