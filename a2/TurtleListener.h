#ifndef _TURTLELISTENER_H_
#define _TURTLELISTENER_H_

#include "Timer.h"
#include "TurtleGraphics.h"
#include "Slider.h"

namespace cs349 {
  class TurtleListener;
}

using namespace std;
using namespace cs349;


namespace cs349 {

  /**
   * 
   */
  class TurtleListener : public TimerListener
  {
  private:
    /**
     * Timer used to periodically update the turtle graphics
     */
    Timer* timer;

    /**
     * Whether the turtle graphics is currently running.
     */
    bool running;

    TurtleGraphics *tg;
    Slider *s;
    int step;
    int maxsteps;


  public:

    TurtleListener();
    virtual ~TurtleListener();

    /**
     * Overrides TimerListener's HandleTimerEvent to be able to
     * routinely update the display.
     */
    virtual void HandleTimerEvent(const TimerEvent & e);

    /**
     * Start the turtle graphics
     */
    void Start();

    void SetFPS(int fps);

    /**
     * Stop the turtle graphics
     */
    void Stop();

    void Restart();

    /**
     * Query whether the turtle graphics is running or not.
     */
    bool IsRunning() const;

    void SetTurtleGraphics(TurtleGraphics *tg, Slider *s);

    void SetMaximum(int maxsteps);

    void Edward(int sss);

  };
}

#endif /* _TURTLELISTENER_H_ */
