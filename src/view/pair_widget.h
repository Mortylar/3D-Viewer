#ifndef SRC_VIEW_PAIR_WIDGET_H_
#define SRC_VIEW_PAIR_WIDGET_H_

#include "widget.h"

#include <gtk/gtk.h>

namespace s21 {
class PairWidget: public Widget {
  public:
    PairWidget() {
      InitGrid();
    };

    ~PairWidget() {};

    virtual GtkWidget* GetGrid() {
      return grid_;
    } 

  private:
    GtkWidget* grid_;

    void InitGrid() {
      grid_ = gtk_grid_new();
      gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    }
};

class LabelPair: public PairWidget {
  public:
    LabelPair() {
      InitLabels();
    };

    ~LabelPair() {
      delete first_;
      delete second_;
    };

    void SetName(const char* name) override {
      first_->SetName(name);
    }

    void SetValue(const char* value) override {
      second_->SetValue(value);
    }

    const char* GetValue(const char* str) override {
      return second_->GetValue(str);
    }

    void SetValue(const double value) override {
      second_->SetValue(value);
    }

    double GetValue(double x) override {
      return second_->GetValue(x);
    }

  private:
    Label* first_ = nullptr;
    Label* second_ = nullptr;

    void InitLabels() {
      first_ = new Label();
      second_ = new Label();
      gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
      gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
    }
};

class LabelDSpinButtonPair: public PairWidget {
  public:
    LabelDSpinButtonPair() {
      InitLabel();
      InitDSpinButton();
    };

    ~LabelDSpinButtonPair() {
      delete first_;
      delete second_;
    };

    void SetName(const char* name) override {
      first_->SetName(name);
    }

    void SetValue(const char* value) override {
      second_->SetValue(value);
    }

    const char* GetValue(const char* str) override {
      return second_->GetValue(str);
    }

    void SetValue(const double value) override {
      second_->SetValue(value);
    }

    double GetValue(double x) override {
      return second_->GetValue(x);
    }

  private:
    Label* first_ = nullptr;
    DSpinButton* second_ = nullptr;

    void InitLabel() {
      first_ = new Label();
      gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
    }

    void InitDSpinButton() {
      second_ = new DSpinButton();
      gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
    }

};


}


#endif
