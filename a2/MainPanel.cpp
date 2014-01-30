#include "MainPanel.h"
#include "TurtleGraphics.h"
#include "Button.h"
#include "Slider.h"
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
  TurtleGraphics* turtle = new TurtleGraphics(TURTLE_GRAPHICS_WIDGET_ID);

  this->SetBounds(Rectangle(0, 0, 500, 400));
  turtleGraphicsPanel->SetBounds(Rectangle(0, 0, 300, 330));
  turtle->SetBounds(Rectangle(0, 30, 300, 300));

  turtleGraphicsPanel->AddComponent(turtle);
  this->AddComponent(turtleGraphicsPanel);

  turtle->SetVisible(true);
  turtleGraphicsPanel->SetVisible(true);

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
}
