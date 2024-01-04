#ifndef SRC_VIEW_WIDGET_OBSERVER_H_
#define SRC_VIEW_WIDGET_OBSERVER_H_

#include "affine_data.h"
#include "widget.h"

namespace s21 {
class Observer {
  public:
    virtual void Update()=0;
  private:
};
}
#endif
