#include "XApplication.h"
#include "StopWatch.h"
#include <sstream>
#include <time.h>
#include <iomanip>

using namespace std;

namespace cs349 {

  StopWatch::StopWatch(EventQueue* eventQueue, const Rectangle & bounds) : XWindow(string("Stop Watch!"), bounds) {
    this->running = false;
    this->reset = true;
      pausedMS = 0;
      pausedLast = 0;
      
    this->timer = new Timer(eventQueue,10,true,this);
    timer->Start();
    startTimeMS = 0;
  }

  StopWatch::~StopWatch() {
    timer->Stop();
    delete timer;
    timer = NULL;
  }

  unsigned long StopWatch::GetCurTime() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
  }
    
    string StopWatch::TimeToString(unsigned long count){
        //initialize
        stringstream ss;
        
        //value of minutes/seconds/ms
        int t_minutes = (count/60000)%60;//# of minutes - mod 60 value
        int t_seconds = (count/1000)%60;//# of seconds - mod 60 value
        int t_mseconds = count%1000;//# of ms - mod 1000 value
        
        //Generate the Text for time, ensure there are leading 0s
        ss << setfill('0') << setw(2) << t_minutes;
        ss << ":";
        ss << setfill('0') << setw(2) << t_seconds;
        ss << ":";
        ss << setfill('0') << setw(3) << t_mseconds;
        return ss.str();
    }
	
  void StopWatch::Paint(Graphics* g) {
      //set foreground/background colours
      g->SetForegroundColor(XApplication::GetInstance()->GetBlackColor());
      g->SetBackgroundColor(XApplication::GetInstance()->GetBlackColor());
      
      //blank the screen, TODO: figure out how to do this properly
      g->FillRect(Rectangle(0,0,390,270));
      
      //reset the foreground color
      g->SetForegroundColor(XApplication::GetInstance()->GetWhiteColor());
      
      
      //title + name
      g->DrawText(Point(235,50),string("Visual Stop 1.0"));
      g->DrawText(Point(225,70),string("Edward Yang (CS349)"));
      
      //Generate the rectangles (buttons) for stop/start/reset/lap
      g->DrawRect(Rectangle(232,190,50,30));
      if(this->running || !this->reset )g->DrawRect(Rectangle(292,190,50,30));
      
      //Generate the rectangles to visually show time
      g->DrawRect(Rectangle(40,40,40,180));
      g->DrawRect(Rectangle(90,40,40,180));
      g->DrawRect(Rectangle(140,40,40,180));
      
      std::string time;
      if(reset){//show 0
          time = string("00:00:000");
      }else{
          //initialize
          stringstream ss;
          unsigned long count = GetCurTime()-startTimeMS-pausedMS; //current exact time of stopwatch
          time = TimeToString(count);
          
          //SHOW LAPS
          //iterate through laps
          
          int laps_index = 107;//where to show the y
          int offset = 13;//how much to offset each lap on the y axis by
          if(laps.size()>=6){
              g->DrawText(Point(276,laps_index-14),string("..."));
          }
          for(vector<string>::iterator l=laps.begin();l != laps.end();++l){
              if(laps.size()>=6 && l == laps.begin());
              else{
                  g->DrawText(Point(260,laps_index),(*l));
                  laps_index+=offset;//yay...
              }
          }
          
          //remainder - this feature was added in to ensure the minutes/seconds graphics grow at the proper rate (not just at exact interger units). ie. at 130ms, it should show .130s worth on the seconds graphic, etc.
          double t_minutes_remainder = ((double)count/60000) - (int)count/60000;
          double t_seconds_remainder = ((double)count/1000) - (int)count/1000;

        //for visual representation of time
          //generate the height and starting point of fillrectangle, since Graphics uses top left corner as starting point
          double height;
          
          //value of minutes/seconds/ms
          int t_minutes = (count/60000)%60;//# of minutes - mod 60 value
          int t_seconds = (count/1000)%60;//# of seconds - mod 60 value
          int t_mseconds = count%1000;//# of ms - mod 1000 value
          
          //for minutes
          height = (long)t_minutes + t_minutes_remainder;
          height = height*180/10;
          g->FillRect(Rectangle(40,40+180-height,40,height));
          
          //for seconds
          height = (long)t_seconds + t_seconds_remainder;
          height = height*180/60;
          g->FillRect(Rectangle(90,40+180-height,40,height));
          
          //for mill seconds
          height = (long)t_mseconds;
          height = height*180/1000;
          g->FillRect(Rectangle(140,40+180-height,40,height));
      }
      //draw the text for time on screen
      g->DrawText(Point(85,247),time);

      
      //draw the start/stop/reset/pause text
      if(this->running){
          g->DrawText(Point(244,210),string("Stop"));
          g->DrawText(Point(307,210),string("Lap"));//x:300-330
      }else{
          g->DrawText(Point(241,210),string("Start"));//x:400-430,y:170-180
          if(!this->reset) g->DrawText(Point(302,210),string("Reset"));//x:300-330
      }
  }
	
  bool StopWatch::HandleMouseEvent(const MouseEvent & e) {
      if(e.GetType() == MouseEvent::mouseDrag){
          Component::Repaint();
      }
      else{
    // TODO: Remove the following code and add your own event handling
    // code to handle mouse events
//    LOG_DEBUG << "Received HandleMouseEvent in StopWatch" << e;
      
      //get where mouse was clicked
      Point p = e.GetWhere();
      
      //button click checks
      if(p.y>=190 && p.y<=220){
          if(p.x >=232 && p.x <=282){//start/stop button
              //if stopwatch is running, stop
              if(this->running){
                  Stop();
              }
              else Start();//else start it
              
              //repaint to ensure when stopped, it is updated right after.
              Component::Repaint();
          }else if(p.x >=292 && p.x <= 342){//reset/lap button
              if(this->running){//lap button
                  Lap();
              }else if(!this->reset){//reset button
                  Reset();
                  //repaint to ensure that it is updated even while timer is paused
                  Component::Repaint();
              }
          }
      }
      }
    return true;
  }
  void StopWatch::HandleTimerEvent(const cs349::TimerEvent & e) {
    if (this->running) {
      Component::Repaint();
    
    }
  }

  void StopWatch::Start(){
      this->running = true;
      if(this->reset){//if the watch has been reset, it is a fresh start (not a pause/resume)
          startTimeMS = GetCurTime();
          this->reset = false;
      }else{
          //if not been reset, then it is a pause/resume. hence add to the variable holding data about total paused time
          pausedMS+= GetCurTime()-pausedLast;
      }
  }
   
    //resets the stop watch
    void StopWatch::Reset(){
        //reset the paused times
        pausedMS = 0;
        pausedLast = 0;
        this->reset = true;
        laps.clear();
    }
    
    //lap functionality.
    void StopWatch::Lap(){
        //to prevent information overflow on the screen, only save the most recent 6 (and show the recent 5)
        if(laps.size()>=6){
            laps.erase(laps.begin());
        }
        unsigned long count = GetCurTime()-startTimeMS-pausedMS; //current exact time of stopwatch
        
        laps.push_back(TimeToString(count));
    }

  void StopWatch::Stop() {
      //update lastpaused, stop -> pause.
      pausedLast = GetCurTime();
    this->running = false;
  }

  bool StopWatch::IsRunning() const {
    return this->running;
  }
    
    bool StopWatch::IsReset() const{
        return this->reset;
    }
    
    int StopWatch::NumOfLaps() const{
        return laps.size();
    }
}
