#ifndef _BUTTONLISTENER_H_
#define _BUTTONLISTENER_H_

#include "Component.h"
#include "Slider.h"
#include "ActionListener.h"
#include "TurtleListener.h"
#include "TurtleGraphics.h"

namespace cs349{
	class ButtonListener;
}
using namespace std;
using namespace cs349;

namespace cs349 {

  class ButtonListener : public ActionListener {
  private:
  	Slider *s;
    TurtleListener *tl;
    
  public:
    ButtonListener();
    ~ButtonListener();
  	void SetSlider(Slider *s);
    void SetTurtleListener(TurtleListener *tl);
    

    /**
     * This method is called when an action is performed.
     * @param source The Component that is the source of this event
     */
    virtual void ActionPerformed(Component* source);
  };
}

#endif /* _BUTTONLISTENER_H_ */
