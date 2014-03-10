// Author: Edward Yang

#include "ButtonListener.h"
#include "A2WidgetIdentifiers.h"

namespace cs349
{

ButtonListener::ButtonListener()
{
}

ButtonListener::~ButtonListener()
{
}

void ButtonListener::SetSlider(Slider *s){
	this->s = s;
}

void ButtonListener::SetTurtleListener(TurtleListener *tl){
	this->tl = tl;
}

void ButtonListener::ActionPerformed(Component* source){
	if(source->GetName().compare(GO_TO_START_BUTTON_ID) == 0){
		s->SetCurValue(s->GetMinimum());
	}else if(source->GetName().compare(PREVIOUS_FRAME_BUTTON_ID) == 0){
		if(s->GetCurValue() > 1) s->SetCurValue(s->GetCurValue()-1);
	}
	else if(source->GetName().compare(PLAY_BUTTON_ID) == 0){
		if(tl->IsRunning()) tl->Stop();
		else tl->Start();
	}
	else if(source->GetName().compare(NEXT_FRAME_BUTTON_ID) == 0){
		if(s->GetCurValue() < s->GetMaximum()) s->SetCurValue(s->GetCurValue()+1);
	}
	else if(source->GetName().compare(GO_TO_END_BUTTON_ID) == 0){
		s->SetCurValue(s->GetMaximum());
	}
	this->s->Repaint();
	this->tl->Edward(s->GetCurValue());
}



}