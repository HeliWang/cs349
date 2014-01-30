#include "Slider.h"
#include "XWindow.h"
#include "Logging.h"
#include <algorithm>

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

// TODO CS349
}

void Slider::AddValueListener(ValueListener* l) {
// TODO CS349
}

void Slider::RemoveValueListener(ValueListener* l) {
// TODO CS349
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

void Slider::SetMinimum(int minValue) {
// TODO CS349
}

void Slider::SetMaximum(int maxValue) {
// TODO CS349
}

void Slider::SetCurValue(int value) {
// TODO CS349
}

Slider::OrientationType Slider::GetOrientation() const {
  return orientation;
}

void Slider::SetOrientation(OrientationType orientation) {
  this->orientation = orientation;
  this->Repaint();
}

void Slider::PaintComponent(Graphics* g) {
// TODO CS349
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

// TODO CS349: Implement any other methods needed here
// TODO CS349
