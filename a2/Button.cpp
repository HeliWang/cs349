// Author: Michael Terry
#include "Button.h"
#include "XWindow.h"
#include "Logging.h"

#include <algorithm>

using namespace cs349;

Button::Button(const string & name, const string & label)
  : Component(name)
{
  // Perform any initialization needed here
  this->label = label;

// TODO CS349
}

void Button::AddActionListener(ActionListener* l) {
// TODO CS349
}

void Button::RemoveActionListener(ActionListener* l) {
// TODO CS349
}

string Button::GetLabel() const {
  return label;
}

void Button::SetLabel(const string & label) {
  this->label = label;
}

void Button::PaintComponent(Graphics* g) {
// TODO CS349
}

// TODO CS349: Implement any other methods needed here
// TODO CS349
