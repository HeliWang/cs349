#include "MainPanel.h"
#include "TurtleGraphics.h"
#include "TurtleListener.h"
#include "Button.h"
#include "Label.h"
#include "Slider.h"
#include "ButtonListener.h"
#include "A2WidgetIdentifiers.h"

using namespace cs349;

MainPanel::MainPanel()
  : Panel(MAIN_PANEL_ID)
{
  // TODO CS349: Create your entire interface here. You will need to
  // modify the provided code below to lay things out the way you like

  // Note the use of unique identifiers for each widget when they are
  // constructed. See A2WidgetIdentifiers.h and the assignment
  // specification for the identifiers you should use for each of the
  // components you create. These identifiers are used for unit tests
  // to easily identify components in the interactor tree.

  

  Component* turtleGraphicsPanel = new Panel(TURTLE_GRAPHICS_PANEL_ID);
  Label *turtleLabel = new Label(TURTLE_GRAPHICS_OUTPUT_LABEL_ID,"Turtle Graphics Output:",Point(100,100));
  TurtleGraphics* turtle = new TurtleGraphics(TURTLE_GRAPHICS_WIDGET_ID);
  TurtleListener* tl = new TurtleListener();



  Component *playbackPanel = new Panel(PLAYBACK_PANEL_ID);
  Label *playbackLabel = new Label(PLAYBACK_OUTPUT_LABEL_ID,"Playback Rate:",Point(200,25-10));
  Slider *playbackSlider = new Slider(PLAYBACK_SLIDER_ID,Slider::HORIZONTAL_SLIDER,Point(200,25));
  

  Component *currentStepPanel = new Panel(CURRENT_TURTLE_STEP_PANEL_ID);
  Label *currentLabel = new Label(CURRENT_TURTLE_STEP_LABEL_ID,"Current Turtle Step:",Point(200,90-10));
  Slider *currentSlider = new Slider(CURRENT_TURTLE_STEP_SLIDER_ID,Slider::HORIZONTAL_SLIDER,Point(200,90));

  tl->SetTurtleGraphics(turtle,currentSlider);

  Component *buttonPanel = new Panel(BUTTON_PANEL_ID);
  buttonPanel->SetBounds(Rectangle(0,110,100,140));
  Button *startButton = new Button(GO_TO_START_BUTTON_ID,"Go To Start",Point(1,110));
  Button *previousButton = new Button(PREVIOUS_FRAME_BUTTON_ID,"Previous Frame",Point(21,110));
  Button *playButton = new Button(PLAY_BUTTON_ID,"Play",Point(41,110));
  Button *nextButton = new Button(NEXT_FRAME_BUTTON_ID,"Next Frame",Point(61,110));
  Button *endButton = new Button(GO_TO_END_BUTTON_ID,"End Frame",Point(81,110));


  ButtonListener *bl = new ButtonListener();

  bl->SetSlider(currentSlider);
  startButton->AddActionListener(bl);
  previousButton->AddActionListener(bl);
  playButton->AddActionListener(bl);
  nextButton->AddActionListener(bl);
  endButton->AddActionListener(bl);
  bl->SetTurtleListener(tl);


  startButton->SetBounds(Rectangle(1,110,18,20));
  previousButton->SetBounds(Rectangle(21,110,18,20));
  playButton->SetBounds(Rectangle(41,110,18,20));
  nextButton->SetBounds(Rectangle(61,110,18,20));
  endButton->SetBounds(Rectangle(81,110,18,20));


  this->SetBounds(Rectangle(0, 0, 300, 150));
  
  turtleGraphicsPanel->SetBounds(Rectangle(0,0,100,100));
  turtle->SetBounds(Rectangle(0,0,100,100));

  playbackPanel->SetBounds(Rectangle(200-75,25,100+75,100));

  currentStepPanel->SetBounds(Rectangle(200-75,90,100+75,100));
  buttonPanel->SetBounds(Rectangle(0,0,200,300));


  
  playbackSlider->SetMinimum(1);
  playbackSlider->SetMaximum(100);
  playbackSlider->SetCurValue(50);
  playbackSlider->SetBounds(Rectangle(0,0,200,60));

  currentSlider->SetMinimum(1);
  
  currentSlider->SetCurValue(1);
  currentSlider->SetBounds(Rectangle(0,0,200,60));





  //add components to proper interactor tree
  turtleGraphicsPanel->AddComponent(turtleLabel);
  turtleGraphicsPanel->AddComponent(turtle);

  playbackPanel->AddComponent(playbackLabel);
  playbackPanel->AddComponent(playbackSlider);

  currentStepPanel->AddComponent(currentLabel);
  currentStepPanel->AddComponent(currentSlider);

  buttonPanel->AddComponent(startButton);
  buttonPanel->AddComponent(previousButton);
  buttonPanel->AddComponent(playButton);
  buttonPanel->AddComponent(nextButton);
  buttonPanel->AddComponent(endButton);

  this->AddComponent(turtleGraphicsPanel);
  this->AddComponent(playbackPanel);
  this->AddComponent(currentStepPanel);
  this->AddComponent(buttonPanel);

  //set visible to be true
  turtleLabel->SetVisible(true);
  turtle->SetVisible(true);

  playbackLabel->SetVisible(true);
  playbackSlider->SetVisible(true);

  currentLabel->SetVisible(true);
  currentSlider->SetVisible(true);

  startButton->SetVisible(true);
  previousButton->SetVisible(true);
  playButton->SetVisible(true);
  nextButton->SetVisible(true);
  endButton->SetVisible(true);

  turtleGraphicsPanel->SetVisible(true);
  playbackPanel->SetVisible(true);
  currentStepPanel->SetVisible(true);
  buttonPanel->SetVisible(true);

  


  // TODO CS349: Add other initialization code here
// TODO CS349

  // Some simple operations to show the turtle when starting up
  // This is an entirely random set of instructions
  // Once started up, try typing this into the console:
  // (turtle-star (find-turtle-graphics-widget) 300 23)
  // The 300 argument is the length of the edges of the star, in
  // pixels
  // The 23 argument is the number of points for the star
  turtle->RotateInDegrees(45);
  turtle->Forward(100, true);
  turtle->RotateInDegrees(135);
  turtle->Forward(65, true);
  turtle->RotateInDegrees(135);
  turtle->Forward(100, true);
  turtle->RotateInDegrees(150);
  turtle->Forward(30, true);

  currentSlider->SetMaximum(turtle->GetNumSteps());
  tl->SetMaximum(turtle->GetNumSteps());

  tl->Start();
}
