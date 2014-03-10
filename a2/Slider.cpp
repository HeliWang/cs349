#include "Slider.h"
#include "XWindow.h"
#include "Logging.h"
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace cs349;
using namespace std;

Slider::Slider(const string & name, OrientationType orientation)
  : Component(name)
{
  lowerBound = 0;
  upperBound = 0;
  curValue = 0;
  lowerBoundLabel = "";
  upperBoundLabel = "";
  thumbLabel = "";
  this->orientation = orientation;
  SetLocation(Point(0,0));
  p = Point(0,0);
}

Slider::Slider(const string & name, OrientationType orientation, const Point &p)
  : Component(name)
{
  lowerBound = 0;
  upperBound = 0;
  curValue = 0;
  lowerBoundLabel = "";
  upperBoundLabel = "";
  thumbLabel = "";
  this->orientation = orientation;
  SetLocation(p);
  this->p = p;
}

void Slider::AddValueListener(ValueListener* l) {
  listeners.push_back(l);
}

void Slider::RemoveValueListener(ValueListener* l) {
  remove(listeners.begin(), listeners.end(), l);
}

int Slider::GetMinimum() const {
  return lowerBound;
}

int Slider::GetMaximum() const {
  return upperBound;
}

int Slider::GetCurValue() const {
  return curValue;
}

void Slider::SetMinimum(int minValue){
  if(this->lowerBoundLabel.compare("") == 0){
    ostringstream s;
    s << minValue;
    this->lowerBoundLabel = s.str();
  }
  
  this->lowerBound = minValue;
}

void Slider::SetMaximum(int maxValue) {
  if(this->upperBoundLabel.compare("") == 0){
    ostringstream s;
    s << maxValue;
    this->upperBoundLabel = s.str();
  }

  this->upperBound = maxValue;
}

void Slider::SetCurValue(int vvv) {
  this->curValue = vvv;
  
  stringstream ss;
  ss << vvv;
  this->thumbLabel = ss.str();

  this->Repaint();
}
void Slider::PP(){
  if(this->curValue < GetMaximum()) this->curValue++;

  ostringstream s;
  s << this->curValue;
  this->thumbLabel = s.str();

  this->Repaint();
}

Slider::OrientationType Slider::GetOrientation() const {
  return orientation;
}

void Slider::SetOrientation(OrientationType orientation) {
  this->orientation = orientation;
  this->Repaint();
}

void Slider::PaintComponent(Graphics* g) {
  double x = p.x;
  double y = p.y;
  std::ostringstream s;

  //get the weight of curValue ove rthe bounds  
  double tt = abs((double)curValue/((double)upperBound - (double)lowerBound)*100);

  const unsigned long bgc = g->GetBackgroundColor();
  const unsigned long fgc = g->GetForegroundColor();
  g->SetBackgroundColor(fgc);
  g->SetForegroundColor(bgc);
  g->FillRect(Rectangle(x-50,y,100,40));
  // g->FillRect(Rectangle(x-80,y,150,60));
  g->SetBackgroundColor(bgc);
  g->SetForegroundColor(fgc);

  
  g->DrawText(Point(x-70-lowerBoundLabel.length()*7/2,y+20),lowerBoundLabel);
  g->DrawText(Point(x+70-upperBoundLabel.length()*7/2,y+20),upperBoundLabel);
  g->DrawText(Point(x-(47-tt)-thumbLabel.length()*7/2,y+42),thumbLabel);


  //Actual sliding part
  g->FillRect(Rectangle(x-(50-tt),y+3,7,24));
  //Slider long part
  g->FillRect(Rectangle(x-50,y+14,100,2));


}

string Slider::GetLowerBoundLabel() const {
  return lowerBoundLabel;
}

string Slider::GetUpperBoundLabel() const {
  return upperBoundLabel;
}

string Slider::GetThumbLabel() const {
  return thumbLabel;
}

void Slider::SetLowerBoundLabel(const string & label) {
  this->lowerBoundLabel = label;
  this->Repaint();
}

void Slider::SetUpperBoundLabel(const string & label) {
  this->upperBoundLabel = label;
  this->Repaint();
}

void Slider::SetThumbLabel(const string & label) {
  this->thumbLabel = label;
  this->Repaint();
}

void Slider::SetLocation(const Point &p){
  this->p = p;
}

bool Slider::HandleMouseEvent(const MouseEvent &e){
  LOG_DEBUG << "SLIDER HANDLE MOUSE EVENT";
  return true;
}