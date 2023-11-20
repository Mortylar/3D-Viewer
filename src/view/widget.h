#ifndef SRC_VIEW_WIDGET_H_
#define SRC_VIEW_WIDGET_H_

#include <gtk/gtk.h>

namespace s21 {
class Widget {
  public:
    Widget() {
      frame_ = gtk_frame_new(nullptr);
    }

    ~Widget() {};

    virtual GtkWidget* GetFrame() {
      return frame_;
    }

    virtual GtkWidget* GetRoot() {
      return frame_;
    }

    virtual void SetName(const char* name) {
      gtk_frame_set_label(GTK_FRAME(frame_), name);
      gtk_frame_set_label_align(GTK_FRAME(frame_), 0.5);
    }

    virtual const char* GetValue(const char* str) = 0;
    virtual double GetValue(double x) = 0;
    virtual void SetValue(const char* value) = 0;
    virtual void SetValue(const double value) = 0;

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

    void SetName(const char* name) override {
      gtk_label_set_text(GTK_LABEL(label_), name);
    }

    const char* GetValue(const char* str = nullptr) override {
      return (gtk_label_get_text(GTK_LABEL(label_)));
    };

    void SetValue(const char* value) override {
      gtk_label_set_text(GTK_LABEL(label_), value);
    }

    double GetValue(double x = 0.0) {return x;};

    void SetValue(const double value) override {};

  private:
    GtkWidget* label_ = nullptr;

    void InitLabel() {
      label_ = gtk_label_new(nullptr);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), label_);
    }

};

class DSpinButton: public Widget {
  public:
    DSpinButton() {
      adjustment_ = gtk_adjustment_new(0.0, -1e100, 1e100, 1, 0, 0);
      spin_button_ = gtk_spin_button_new(adjustment_, 100, 20);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), spin_button_);
    }

    DSpinButton(GtkAdjustment* adjustment) {
      spin_button_ = gtk_spin_button_new(adjustment, 100, 20);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), spin_button_);
    }

    ~DSpinButton(){};

    const char* GetValue(const char* str = nullptr) override {return str;};

    double GetValue(double x = 0) override {
      return gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_));
    }

    void SetValue(const char* value) override {};

    //void SetName(const char* name){};

    void SetValue(const double value) override {
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_), value);
    };

  private:
    GtkWidget* spin_button_ = nullptr;
    GtkAdjustment* adjustment_ = nullptr;

};

}


#endif

