// Author: Edward Yang
#include "Label.h"
#include "XWindow.h"
#include "Logging.h"

using namespace cs349;

Label::Label(const string & name, const string & label)
  : Component(name)
{
  this->label = label;
  this->name = name;
  SetLocation(Point(0,0));
}

Label::Label(const string & name, const string & label, const Point &p)
  : Component(name)
{
  this->label = label;
  this->name = name;
  SetLocation(p);
}

string Label::GetLabel() const {
  return label;
}

void Label::SetLabel(const string & label) {
  this->label = label;
}

void Label::PaintComponent(Graphics* g) {
  double x = this->GetBounds().x;
  double y = this->GetBounds().y;
	g->DrawText(Point(x-label.length()*7/2,y+11/2),label);
}
