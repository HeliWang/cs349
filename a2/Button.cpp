// Author: Michael Terry
#include "Button.h"
#include "XWindow.h"
#include "Logging.h"
#include "MouseEvent.h"
#include "A2WidgetIdentifiers.h"

#include <algorithm>

using namespace cs349;

Button::Button(const string & name, const string & label)
  : Component(name)
{
  this->label = label;
  this->name = name;
  this->SetLocation(Point(0,0));

  width = 18;
  height = 18;
  status = true;
}

Button::Button(const string & name, const string & label,const Point &p)
  : Component(name)
{
  this->label = label;
  this->name = name;
  this->SetLocation(p);
  width = 18;
  height = 18;
  this->SetBounds(Rectangle(p.x,p.y,p.x+width,p.y+height));
  status = true;
}

void Button::AddActionListener(ActionListener* l) {
	listeners.push_back(l);
}

void Button::RemoveActionListener(ActionListener* l) {
	remove(listeners.begin(), listeners.end(), l);
}

string Button::GetLabel() const {
  return label;
}

void Button::SetLabel(const string & label) {
  this->label = label;
}

void Button::PaintComponent(Graphics* g) {
	double x = this->GetBounds().x;
	double y = this->GetBounds().y;
	g->DrawRect(Rectangle(x,y,width,height));
	// g->DrawText(Point(x+15,y+20),label);
  vector<Point> va;
  if(name.compare(GO_TO_START_BUTTON_ID) == 0){
    //1/110 19/128
    va.push_back(Point(17,126));
    va.push_back(Point(17,112));
    va.push_back(Point(6,119));
    g->FillPolygon(va);
    va.clear();
    va.push_back(Point(3,112));
    va.push_back(Point(4,112));
    va.push_back(Point(4,127));
    va.push_back(Point(3,127));
    g->FillPolygon(va);
  }else if(name.compare(PREVIOUS_FRAME_BUTTON_ID) == 0){
    va.push_back(Point(36,126));
    va.push_back(Point(36,112));
    va.push_back(Point(25,119));
    g->FillPolygon(va);
  }
  else if(name.compare(PLAY_BUTTON_ID) == 0){
    if(!status){
      va.push_back(Point(44,126));
      va.push_back(Point(44,112));
      va.push_back(Point(56,119));
      va.push_back(Point(44,126));
      g->DrawPolygon(va);
    }else{
      va.push_back(Point(45,113));
      va.push_back(Point(49,113));
      va.push_back(Point(49,125));
      va.push_back(Point(45,125));
      g->FillPolygon(va);
      va.clear();
      va.push_back(Point(55,113));
      va.push_back(Point(51,113));
      va.push_back(Point(51,125));
      va.push_back(Point(55,125));
      g->FillPolygon(va);
    }
    
  }
  else if(name.compare(NEXT_FRAME_BUTTON_ID) == 0){
    va.push_back(Point(64,126));
    va.push_back(Point(64,112));
    va.push_back(Point(76,119));
    g->FillPolygon(va);
  }
  else if(name.compare(GO_TO_END_BUTTON_ID) == 0){
    va.push_back(Point(83,126));
    va.push_back(Point(83,112));
    va.push_back(Point(94,119));
    g->FillPolygon(va);
    va.clear();
    va.push_back(Point(97,112));
    va.push_back(Point(96,112));
    va.push_back(Point(96,127));
    va.push_back(Point(97,127));
    g->FillPolygon(va);
  }
}

void Button::SetSize(int w,int h){
	this->width = w;
	this->height = h;
}

bool Button::HandleMouseEvent(const MouseEvent &e){
  

    if(e.GetType() == MouseEvent::mouseMove){}
    else{
      if(name.compare(PLAY_BUTTON_ID) == 0){
        status = !status;
        this->Repaint();
      }

      for(std::vector<ActionListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        (*it)->ActionPerformed(this);
    }

  }
  return true;
}