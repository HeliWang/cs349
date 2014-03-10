// Author: Edward Yang
#ifndef _LABEL_H_
#define _LABEL_H_

#include "Component.h"
#include "Point.h"
#include <vector>

using namespace std;

namespace cs349 {

  class Label : public Component {
  private:
    string label, name;
  protected:
    /**
     * The method that does the actual painting of the component once
     * the Graphics context object has been set up by the Paint
     * method in Component.
     */
    virtual void PaintComponent(Graphics* g);

  public:
    /**
     * Creates a new instance of a label. For this class, name is a
     * unique name to uniquely identify this label in unit tests and
     * within the interactor tree. label is the text that is displayed
     * by this label.
     *
     * @param name A unique name to identify this label in debugging,
     * unit tests, and within the interactor tree
     * @param label The text shown in this label, if it is a
     * text-based label
     */
    Label(const string & name, const string & label);

    /**
     * Creates a new instance of a label. For this class, name is a
     * unique name to uniquely identify this label in unit tests and
     * within the interactor tree. label is the text that is displayed
     * by this label.
     *
     * @param name A unique name to identify this label in debugging,
     * unit tests, and within the interactor tree
     * @param label The text shown in this label, if it is a
     * text-based label
     */
    Label(const string & name, const string & label, const Point &p);

    /**
     * Returns the text label for this label
     */
    string GetLabel() const;

    /**
     * Sets the text label for this label
     */
    void SetLabel(const string & label);
    // TODO CS349: Add any other necessary methods or overrides here
// TODO CS349
  };
}


#endif /* _LABEL_H_ */
