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

    void SetName(const char* name) override { //TODO override
      first_->SetName(name);
    }

    const char* GetName() {
      return first_->GetValue();
    }

    void SetValue(const char* value) {
      second_->SetValue(value);
    }

    const char* GetValue() {
      return second_->GetValue();
    }

	void SetMother(s21::Widget* mother) override {
	  first_->SetMother(mother);
	  second_->SetMother(mother);
	}
    
    void CatchSignal() override {
	  g_print("\nWarning: s21::LabelPair::CatchSignal() has no implementation!\n");
	}

	void SendSignal() override {
	  g_print("\nWarning: s21::LabelPair::SendSignal() has no implementation!\n");
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

    LabelDSpinButtonPair(GtkAdjustment* adjustment) {
      InitLabel();
      InitDSpinButton(adjustment);
    }

    ~LabelDSpinButtonPair() {
      delete first_;
      delete second_;
    };

    void SetName(const char* name) override { //TODO override
      first_->SetName(name);
    }

    const char* GetName() {
      return first_->GetValue();
    }

    void SetValue(const double value) {
      second_->SetValue(value);
    }

    double GetValue() {
      return second_->GetValue();
    }

    double* GetData() {
      return second_->GetData();
    }

	void SetMother(s21::Widget* mother) override {
	  first_->SetMother(mother);
	  second_->SetMother(mother);
	}

    void CatchSignal() override {
	  g_print("\nWarning: s21::LabeliDSpinButtonPair::CatchSignal() has no implementation!\n");
	}

	void SendSignal() override {
	  g_print("\nWarning: s21::LabelDSpinButtonPair::SendSignal() has no implementation!\n");
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

    void InitDSpinButton(GtkAdjustment* adjustment) { 
      second_ = new DSpinButton(adjustment);
      gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
    }

};

class LabelDSliderPair: public PairWidget {
  public:
    LabelDSliderPair() {
      InitLabel();
      InitSlider();
    }

    LabelDSliderPair(GtkAdjustment* adjustment) {
      InitLabel();
      InitSlider(adjustment);
    }

    ~LabelDSliderPair() {
      delete first_;
      delete second_;
    }

    void SetName(const char* name) override { //TODO override
      first_->SetName(name);
    }

    const char* GetName() {
      return first_->GetValue();
    }

    void SetValue(const double value) {
      second_->SetValue(value);
    }

    double GetValue() {
      return second_->GetValue();
    }

    double* GetData() {
      return second_->GetData();
    }

	void SetMother(s21::Widget* mother) override {
	  first_->SetMother(mother);
	  second_->SetMother(mother);
	}

    void CatchSignal() override {
	  g_print("\nWarning: s21::LabelDSliderPair::CatchSignal() has no implementation!\n");
	}

	void SendSignal() override {
	  g_print("\nWarning: s21::LabelDSliderPair::SendSignal() has no implementation!\n");
	}

  private:
    Label* first_ = nullptr;
    DSlider* second_ = nullptr;

    void InitLabel() { 
      first_ = new Label();
      gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
    }

    void InitSlider() {
      second_ = new DSlider();
      gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1,0,3,1);
      gtk_grid_set_column_homogeneous(GTK_GRID(GetGrid()), true);
    }

    void InitSlider(GtkAdjustment* adjustment) { 
      second_ = new DSlider(adjustment);
      gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1,0,3,1);
      gtk_grid_set_column_homogeneous(GTK_GRID(GetGrid()), true);
    }
};

class LabelColorButtonPair: public PairWidget {
 public:
  LabelColorButtonPair() {
    InitLabel();
    InitColorButton();
  };


  LabelColorButtonPair(const char* name) {
    InitLabel(name);
    InitColorButton();
  };

  ~LabelColorButtonPair() {};

  void SetName(const char* name) override {
    first_->SetName(name);
  }

  void SetValue(const char* value) {
    second_->SetName(value);
  }

  void SetMother(s21::Widget* mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void SendSignal() override {} //TODO
  void CatchSignal() override {} //TODO
 
  GdkRGBA GetColor() {
    return second_->GetColor();
  }

 private:
  Label* first_ = nullptr;
  ColorButton* second_ = nullptr;

  void InitLabel(const char* name = "") {
    first_ = new Label(name);
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0,0,1,1);
  }

  void InitColorButton() {
    second_ = new ColorButton();
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1,0,1,1);
  }

};

}


#endif
