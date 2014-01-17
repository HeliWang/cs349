#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <string.h>

#include "XWindow.h"
#include "Logging.h"
#include "Timer.h"

using namespace std;

namespace cs349 {

  /**
   * Skeleton of a StopWatch class to complete and augment for A1
   */
  class StopWatch : public XWindow, TimerListener
  {
  private:
    /**
     * Timer used to periodically update the stopwatch's display
     */
    Timer* timer;

    /**
     * The time, in milliseconds, that the stopwatch started
     */
    unsigned long startTimeMS;

    /**
     * The time, in milliseconds, that the stopwatch has been paused
     * In particular, it keeps a running total of the amount of time needed to subtract from the current time less start time.
     */
    unsigned long pausedMS;
      
    /**
     * The time, in milliseconds, that the stop was last paused
     * In particular, it holds the value the time of the most recent pause.
     */
    unsigned long pausedLast;
      
    /**
     * Whether the stopwatch is currently running.
     */
    bool running;

    /**
     * Whether the stopwatch has been reset.
     */
    bool reset;
      
    /**
     * Returns the current time in milliseconds.
     */
    static unsigned long GetCurTime();
      
    /**
     * Holds the value of laps!
     */
      vector<string> laps;
      
    /**
     * Returns the string value of the given time
     */
      string TimeToString(unsigned long count);
  public:

    /**
     * StopWatch derives from XWindow and TimerListener. These classes
     * require the following information passed in.
     * @param eventQueue The XApplication's event queue
     * @param bounds The desired location and size of this StopWatch
     * window.
     */
    StopWatch(EventQueue* eventQueue, const Rectangle & bounds);
    virtual ~StopWatch();

    /**
     * Overrides Component's HandleMouseEvent method.
     */
    virtual bool HandleMouseEvent(const MouseEvent & e);

    /**
     * Overrides Component's Paint method.
     */
    virtual void Paint(Graphics* g);

    /**
     * Overrides TimerListener's HandleTimerEvent to be able to
     * routinely update the display.
     */
    virtual void HandleTimerEvent(const cs349::TimerEvent & e);

    /**
     * Start the stopwatch
     */
    void Start();

    /**
     * Resets the stopwatch
     */
      void Reset();
      
    /**
     * Lap functionality on stopwatch
     */
      void Lap();
      
    /**
     * Stop the stopwatch
     */
    void Stop();

    /**
     * Query whether the stopwatch is running or not.
     */
    bool IsRunning() const;
      
    /**
     * Query whether the stopwatch was reset or not.
     */
      bool IsReset() const;
      
    /**
     * Query to see how many laps are saved currently.
     */
      int NumOfLaps() const;
  };
}

#endif /* _STOPWATCH_H_ */
