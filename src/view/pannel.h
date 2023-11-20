#ifndef SRC_VIEW_PANNEL_H_
#define SRC_VIEW_PANNEL_H_

#include <gtk/gtk.h>

#include "pair_widget.h"

#include <vector>

namespace s21 {
class LabelPannel: public PairWidget {
  public:
    LabelPannel(): size_(1) {
      InitPannel();
    }

    LabelPannel(size_t size): size_(size) {
      InitPannel();
    }

    ~LabelPannel() {
     for (size_t i = 0; i < size_; ++i) {
       delete pair_[i];
     } 
    };

    const char* GetValue(const char* str) { 
      return pair_.at(0)->GetValue(str);
    };

    double GetValue(double x) {  
      return pair_.at(0)->GetValue(x);
    };

    void SetValue(const char* value) {
      for (size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    };

    void SetValue(double value) { 
      for (size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    };

    void SetNames(size_t pos, const char* name){
      if (pos >= size_)
        throw std::out_of_range("s21::LabelPannel::SetNames Out of range");
      pair_[pos]->SetName(name);
    }

    void SetName(const char* name) override {
      s21::Widget::SetName(name);
    }

  private:
    std::vector<LabelPair*> pair_;
    size_t size_;

    void InitPannel() {
      for (size_t i = 0; i < size_; ++i) {
        pair_.push_back(new LabelPair());
	gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
      }
    }

};

class DSpinButtonPannel: public PairWidget {
  public:
    DSpinButtonPannel(): size_(1) {
      InitPannel();
    }

    DSpinButtonPannel(size_t size): size_(size) {
      InitPannel();
    }

    ~DSpinButtonPannel() {
      for (size_t i = 0; i < size_; ++i) {
        delete pair_[i];
      }
    };

    const char* GetValue(const char* str) { 
      return pair_.at(0)->GetValue(str);
    };

    double GetValue(double x) {  
      return pair_.at(0)->GetValue(x);
    };

    void SetValue(const char* value) {
      for (size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    };

    void SetValue(double value) { 
      for (size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    };

    void SetNames(size_t pos, const char* name){
      pair_[pos]->SetName(name);
    }

    void SetName(const char* name) override {
      s21::Widget::SetName(name);
    }

  private:
    std::vector<LabelDSpinButtonPair*> pair_;
    size_t size_;

    void InitPannel() {
      for (size_t i = 0; i < size_; ++i) {
        pair_.push_back(new LabelDSpinButtonPair());
	gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
      }
    }

};

}
#endif

