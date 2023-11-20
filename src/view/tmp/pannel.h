#ifndef SRC_PANNEL_H_
#define SRC_PANNEL_H_

#include "mother_pannel.h"
#include "input_pannel.h"

#include <initializer_list>

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

    Pannel(std::initializer_list<const char*> const &names):Pannel(names.size()) {
      auto it = names.begin();
      for (size_t i = 0; i < size_; ++i) {
        SetLabel(i, *it++);
      }
    }

    ~Pannel() {
      delete[] pannels_;
    }


    size_t GetSize() {
      return size_;
    }

    void SetLabels(const char** name_arr);
    void SetLabel(size_t pos, const char* name);
    double GetValue(size_t pos);




  private:
    GtkWidget* grid_;
    size_t size_;
    InputPannel* pannels_;

    void PannelsAllocate();
    void InitGrid();
};

#endif
