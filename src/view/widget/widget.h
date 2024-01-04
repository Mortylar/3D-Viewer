#ifndef SRC_VIEW_WIDGET_WIDGET_H_
#define SRC_VIEW_WIDGET_WIDGET_H_

#include <gtk/gtk.h>
#include "observer.h"


namespace s21 {
class Widget {
  public:
    Widget() {
      frame_ = gtk_frame_new(nullptr);
    }

    virtual ~Widget(){};

    virtual GtkWidget* GetFrame() {//TODO virtual
      return frame_;
    }

    virtual GtkWidget* GetRoot() { //TODO virtual
      return frame_;
    }

    virtual void SetName(const char* name) { //TODO virual
      gtk_frame_set_label(GTK_FRAME(frame_), name);
      gtk_frame_set_label_align(GTK_FRAME(frame_), 0.5);
    }

  private:
    GtkWidget* frame_ = nullptr;
};


class Label: public Widget {
  public:
    Label() {
      InitLabel();
    }

    Label(const char* text) {
      InitLabel();
      SetName(text);
    }

    ~Label(){};

    void SetName(const char* name) override { //TODO override
      gtk_label_set_text(GTK_LABEL(label_), name);
    }

    const char* GetValue() {
      return (gtk_label_get_text(GTK_LABEL(label_)));
    };

    void SetValue(const char* value) {
      gtk_label_set_text(GTK_LABEL(label_), value);
    }

  private:
    GtkWidget* label_ = nullptr;
    //TODO value_;

    void InitLabel() {
      label_ = gtk_label_new(nullptr);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), label_);
    }

};

class DSpinButton: public Widget {
  public:
    DSpinButton() {
      adjustment_ = gtk_adjustment_new(0.0, -1e100, 1e100, 1, 0, 0);
      InitSpinButton();
    }

    DSpinButton(GtkAdjustment* adjustment): adjustment_(adjustment) {
      InitSpinButton();
    }

    ~DSpinButton(){};

    double GetValue() {
      return value_;
    }

    double* GetData() {
      return &value_;
    }

    void SetValue(const double value) {
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_), value);
    };

    void PrintPtr() {
      g_print("\nptr = %p\n", spin_button_);
    }

  private:
    GtkWidget* spin_button_ = nullptr;
    GtkAdjustment* adjustment_ = nullptr;
    double value_ = 0.0;

    DSpinButton(DSpinButton&);
    DSpinButton(DSpinButton&&);

    static void ValueReboot(GtkAdjustment* adjustment, DSpinButton* self) {
      self->value_ = gtk_adjustment_get_value(self->adjustment_);
    }

    void InitSpinButton() {
      spin_button_ = gtk_spin_button_new(adjustment_, 100, 20);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), spin_button_);
      g_signal_connect(spin_button_, "value_changed", G_CALLBACK(ValueReboot), this);
    }

};

class DSlider: public Widget {
  public:
    DSlider() {
      adjustment_ = gtk_adjustment_new(0.0, -100.0, 100.0, 1, 12, 0);
      InitSlider();
    }

    DSlider(GtkAdjustment* adjustment): adjustment_(adjustment) {
      InitSlider();
    }

    ~DSlider(){};

     double GetValue() {
       return value_;
     }

    double* GetData() {
      return &value_;
    }

     void SetValue(double x) {
       gtk_adjustment_set_value(adjustment_, x);
     }

  private:
    GtkWidget* scale_button_ = nullptr;
    GtkAdjustment* adjustment_ = nullptr;
    double value_ = 0.0;

    static void ValueReboot(GtkAdjustment* adjustment, DSlider* self) {
      self->value_ = gtk_adjustment_get_value(self->adjustment_);
    }

    void InitSlider() {
      scale_button_ = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment_);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), scale_button_);
      g_signal_connect(adjustment_, "value_changed", G_CALLBACK(ValueReboot), this);
    }
};

}


#endif

