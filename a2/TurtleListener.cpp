#include "TurtleListener.h"
#include "Logging.h"

#include "XApplication.h"
#include "XWindow.h"
#include <sstream>
#include <time.h>

using namespace std;
using namespace cs349;

namespace cs349 {

  TurtleListener::TurtleListener() {
    this->running = false;
    this->timer = new Timer(XApplication::GetInstance()->GetEventQueue(), 100, true, this);
    step = 1;
    maxsteps = 100;
  }

  TurtleListener::~TurtleListener() {
    timer->Stop();
    delete timer;
    timer = NULL;
  }
  void TurtleListener::SetTurtleGraphics(TurtleGraphics *tg, Slider *s){
    this->tg = tg;
    this->s = s;
    
  }

  void TurtleListener::SetFPS(int fps){
    timer->Stop();
    delete timer;
    timer = NULL;
    timer = new Timer(XApplication::GetInstance()->GetEventQueue(), fps*10, true, this);
  }
  void TurtleListener::HandleTimerEvent(const TimerEvent & e) {
    if (running) {
      //redraw screen
      
      tg->GoToStep(this->step);
      s->SetCurValue(this->step);
      if(this->step < maxsteps) this->step++;
      else Stop();
    }
  }

  void TurtleListener::Edward(int sss){
    step = sss;
    tg->GoToStep(sss);
    tg->Repaint();
  }

  void TurtleListener::Start() {
    this->running = true;
    timer->Start();
  }

  void TurtleListener::Stop() {
    this->running = false;
    timer->Stop();
  }

  void TurtleListener::Restart(){
    timer->Stop();
    delete timer;
    timer = new Timer(XApplication::GetInstance()->GetEventQueue(), 100, true, this);
    this->running = true;
    step = 1;
    timer->Start();
  }

  void TurtleListener::SetMaximum(int maxsteps){
    this->maxsteps = maxsteps;
  }

  bool TurtleListener::IsRunning() const {
    return running;
  }
}
