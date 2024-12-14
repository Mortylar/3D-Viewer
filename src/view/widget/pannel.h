#ifndef SRC_VIEW_PANNEL_H_
#define SRC_VIEW_PANNEL_H_

#include <gtk/gtk.h>

#include <stdexcept>
#include <vector>

#include "pair_widget.h"
#include "widget.h"

namespace s21 {
class LabelPannel : public PairWidget {
 public:
  LabelPannel() : size_(1) { InitPannel(); }

  explicit LabelPannel(size_t size) : size_(size) { InitPannel(); }

  ~LabelPannel() {
    for (size_t i = 0; i < size_; ++i) {
      delete pair_[i];
    }
  };

  const char *GetValue(size_t pos = 0) {
    if (pos >= size_)
      throw std::out_of_range("s21::LabelPannel::GetValue Out of range");
    return pair_.at(pos)->GetValue();
  };

  void SetValue(const char *value) {
    for (size_t i = 0; i < size_; ++i) {
      pair_[i]->SetValue(value);
    }
  };

  void SetName(size_t pos, const char *name) {
    if (pos >= size_)
      throw std::out_of_range("s21::LabelPannel::SetNames Out of range");
    pair_[pos]->SetName(name);
  }

  void SetName(const char *name) override { s21::Widget::SetName(name); }

  void SetMother(s21::Widget *mother) override {
    for (size_t i = 0; i < size_; ++i) {
      pair_[i]->SetMother(mother);
    }
  }

  void CatchSignal() override {
    g_print(
        "\nWarning: s21::LabelPannel::CatchSignal() has no implementation!\n");
  }

  void SendSignal() override {
    g_print(
        "\nWarning: s21::LabelPannel::SendSignal() has no implementation!\n");
  }

 private:
  std::vector<LabelPair *> pair_;
  size_t size_;

  void InitPannel() {
    for (size_t i = 0; i < size_; ++i) {
      pair_.push_back(new LabelPair());
      gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
    }
  }
};

class DSpinButtonPannel : public PairWidget {
 public:
  DSpinButtonPannel() : size_(1) { InitPannel(); }

  explicit DSpinButtonPannel(size_t size) : size_(size) { InitPannel(); }

  explicit DSpinButtonPannel(
      std::initializer_list<GtkAdjustment *> const &items) {
    size_ = items.size();
    auto it = items.begin();
    for (size_t i = 0; i < size_; ++i) {
      pair_.push_back(new LabelDSpinButtonPair("", *it++));
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

  std::vector<float *> GetData() { return data_; }

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

  void SetName(size_t pos, const char *name) { pair_[pos]->SetName(name); }

  void SetName(const char *name) override { s21::Widget::SetName(name); }

  void SetMother(s21::Widget *mother) override {
    for (size_t i = 0; i < size_; ++i) {
      pair_[i]->SetMother(mother);
    }
  }

  void CatchSignal() override {
    g_print(
        "\nWarning: s21::DSpinButtonPannel::CatchSignal() has no "
        "implementation!\n");
  }

  void SendSignal() override {
    g_print(
        "\nWarning: s21::DSpinButtonPannel::SendSignal() has no "
        "implementation!\n");
  }

 private:
  std::vector<LabelDSpinButtonPair *> pair_;
  std::vector<float *> data_;
  size_t size_;

  void InitPannel() {
    for (size_t i = 0; i < size_; ++i) {
      pair_.push_back(new LabelDSpinButtonPair());
      data_.push_back(pair_[i]->GetData());
      gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
    }
  }
};

class DSliderPannel : public PairWidget {
 public:
  DSliderPannel() : size_(1) { InitPannel(); }

  explicit DSliderPannel(size_t n) : size_(n) { InitPannel(); }

  explicit DSliderPannel(std::initializer_list<GtkAdjustment *> const &items) {
    size_ = items.size();
    auto it = items.begin();
    for (size_t i = 0; i < size_; ++i) {
      pair_.push_back(new LabelDSliderPair(*it++));
      data_.push_back(pair_[i]->GetData());
      gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
    }
  }

  ~DSliderPannel() {
    for (size_t i = 0; i < size_; ++i) {
      delete pair_[i];
    }
  }

  float GetValue(size_t pos) {
    if (pos >= size_)
      throw std::out_of_range("s21::DSliderPannel::GetValue Out of range");
    return pair_.at(pos)->GetValue();
  }

  void SetValue(size_t pos, float value) {
    if (pos >= size_)
      throw std::out_of_range("s21::DSliderPannel::SetValue Out of range");
    pair_.at(pos)->SetValue(value);
  }

  void SetValue(float value) {
    for (size_t i = 0; i < size_; ++i) {
      pair_[i]->SetValue(value);
    }
  }

  std::vector<float *> GetData() { return data_; }

  void SetName(const char *name) override { s21::Widget::SetName(name); }

  void SetName(size_t pos, const char *name) {
    if (pos >= size_)
      throw std::out_of_range("s21::DSliderPannel::SetName Out of range");
    pair_[pos]->SetName(name);
  }

  void SetMother(s21::Widget *mother) override {
    for (size_t i = 0; i < size_; ++i) {
      pair_[i]->SetMother(mother);
    }
  }

  void CatchSignal() override {
    g_print(
        "\nWarning: s21::DSliderPannel::CatchSignal() has no "
        "implementation!\n");
  }

  void SendSignal() override {
    g_print(
        "\nWarning: s21::DSliderPannel::SendSignal() has no implementation!\n");
  }

 private:
  std::vector<LabelDSliderPair *> pair_;
  std::vector<float *> data_;
  size_t size_;

  void InitPannel() {
    for (size_t i = 0; i < size_; ++i) {
      pair_.push_back(new LabelDSliderPair());
      data_.push_back(pair_[i]->GetData());
      gtk_grid_attach(GTK_GRID(GetGrid()), pair_[i]->GetRoot(), 0, i, 1, 1);
    }
  }
};

}  // namespace s21
#endif
