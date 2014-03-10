import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;


public class StartView extends JPanel{
	private JLabel label;
	private JButton startButton;
	
	StartView(){
		label = new JLabel("Shape Cutter");
		startButton = new JButton("Start");//The JButton name.
	    
		label.setFont(new Font("Serif", Font.PLAIN, 36));
	    label.setBounds(220,170,245,50);
	    
	    startButton.setPreferredSize(new Dimension(40,40));
	    startButton.setMaximumSize(new Dimension(40,40));
	    startButton.setBounds(270,230,150,50);
	    
	    this.setLayout(null);
	    this.add(label);
	    this.add(startButton);
	    this.setVisible(true);
	}
	
	public JButton getStartButton(){
		return startButton;
	}
	// Panel size
	  @Override
	  public Dimension getPreferredSize() {
		  return new Dimension(Settings.width,500);
	  }
}
