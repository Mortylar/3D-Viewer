#ifndef SRC_VIEW_PANNEL_H_
#define SRC_VIEW_PANNEL_H_

#include <gtk/gtk.h>

#include "widget.h"
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

    const char* GetValue(size_t pos = 0) {
      if (pos >= size_)
        throw std::out_of_range("s21::LabelPannel::GetValue Out of range");
      return pair_.at(pos)->GetValue();
    };

    void SetValue(const char* value) {
      for (size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    };

    void SetName(size_t pos, const char* name){
      if (pos >= size_)
        throw std::out_of_range("s21::LabelPannel::SetNames Out of range");
      pair_[pos]->SetName(name);
    }

    void SetName(const char* name) override { //TODO override
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

    DSpinButtonPannel(std::initializer_list<GtkAdjustment*> const &items) {
      size_ = items.size();
      auto it = items.begin();
      for(size_t i = 0; i < size_; ++i) { 
        pair_.push_back(new LabelDSpinButtonPair(*it++));
	data_.push_back(pair_[i]->GetData());
	gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
      }
    }

    ~DSpinButtonPannel() {
      for (size_t i = 0; i < size_; ++i) {
        delete pair_[i];
      }
    };

    double GetValue(size_t pos) {
      if (pos >= size_)
        throw std::out_of_range("s21::DSpinButtonPannel::GetValue Out of range");
      return pair_.at(pos)->GetValue();
    };

    std::vector<double*> GetData() {
      return data_;
    }

    void SetValue(double value) { 
      for (size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    };

    void SetValue(size_t pos, double value) {
      if (pos >= size_)
        throw std::out_of_range("s21::DSpinButtonPannel::SetValue Out of range");
      return pair_.at(pos)->SetValue(value);
    };

    void SetName(size_t pos, const char* name){
      pair_[pos]->SetName(name);
    }

    void SetName(const char* name) override { //TODO override
      s21::Widget::SetName(name);
    }

  private:
    std::vector<LabelDSpinButtonPair*> pair_;
    std::vector<double*> data_;
    size_t size_;

    void InitPannel() {
      for (size_t i = 0; i < size_; ++i) {
        pair_.push_back(new LabelDSpinButtonPair());
	data_.push_back(pair_[i]->GetData());
	gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
      }
    }

};

class DSliderPannel: public PairWidget {
  public:
    DSliderPannel(): size_(1) {
      InitPannel();
    }

    DSliderPannel(size_t n): size_(n) {
      InitPannel();
    }

    DSliderPannel(std::initializer_list<GtkAdjustment*> const &items) {
      size_ = items.size();
      auto it = items.begin();
      for(size_t i = 0; i < size_; ++i) { 
        pair_.push_back(new LabelDSliderPair(*it++));
	data_.push_back(pair_[i]->GetData());
	gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
      }
    }


    ~DSliderPannel() {
      for(size_t i = 0; i < size_; ++i) {
        delete pair_[i];
      }
    }

    double GetValue(size_t pos) { 
      if (pos >= size_)
        throw std::out_of_range("s21::DSliderPannel::GetValue Out of range");
      return pair_.at(pos)->GetValue();
    }

    void SetValue(size_t pos, double value) { 
      if (pos >= size_)
        throw std::out_of_range("s21::DSliderPannel::SetValue Out of range");
      return pair_.at(pos)->SetValue(pos);
    }

    void SetValue(double value) {
      for(size_t i = 0; i < size_; ++i) {
        pair_[i]->SetValue(value);
      }
    }

    std::vector<double*> GetData() {
      return data_;
    }

    void SetName(const char* name) override {
      s21::Widget::SetName(name);
    }

    void SetName(size_t pos, const char* name) {
      if (pos >= size_)
        throw std::out_of_range("s21::DSliderPannel::SetName Out of range");
      pair_[pos]->SetName(name);
    }

  private:
    std::vector<LabelDSliderPair*> pair_;
    std::vector<double*> data_;
    size_t size_;

    void InitPannel() {
      for (size_t i = 0; i < size_; ++i) {
        pair_.push_back(new LabelDSliderPair());
	data_.push_back(pair_[i]->GetData());
	gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
      }
    }
};

}
#endif

