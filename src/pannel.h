#ifndef SRC_PANNEL_H_
#define SRC_PANNEL_H_

#include "mother_pannel.h"
#include "input_pannel.h"

class Pannel: public MotherPannel {
  public:
    Pannel():size_(1) {
      PannelsAllocate();
      InitGrid();
    }

    Pannel(size_t n):size_(n) {
      PannelsAllocate();
      InitGrid();
    }

    ~Pannel() {
      delete[] pannels_;
    }

    void SetLabels(const char** name_arr);



  private:
    GtkWidget* grid_;
    size_t size_;
    InputPannel* pannels_;

    void PannelsAllocate();
    void InitGrid();
};

#endif
