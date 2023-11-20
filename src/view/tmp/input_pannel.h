#ifndef INPUT_PANNEL_H_
#define INPUT_PANNEL_H_

#include<gtk/gtk.h>

#include "mother_pannel.h"

class InputPannel: public MotherPannel{

  public:
    InputPannel() {
      InitPannel();
    };
    
    ~InputPannel(){};

    void InitPannel() {
      InitGrid();
      InitLabel();
      InitButton();
    }

    void SetLabelText(const char* text) {
      gtk_label_set_text(GTK_LABEL(label_), text);
    }

    double GetValue() {
      return gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_));
    }

  private:
    GtkWidget* grid_ = nullptr;

    GtkWidget* label_ = nullptr;
    GtkWidget* frame_label_ = nullptr;

    GtkWidget* spin_button_ = nullptr;
    GtkWidget* frame_spin_button_ = nullptr;
    GtkAdjustment* adjustment_ = nullptr;

    void InitGrid() {
      grid_ = gtk_grid_new();
      gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    }

    void InitLabel() { 
      label_ = gtk_label_new("");
      frame_label_ = gtk_frame_new(nullptr);
      gtk_frame_set_child(GTK_FRAME(frame_label_), label_);
      gtk_grid_attach(GTK_GRID(grid_), frame_label_, 0, 0, 1, 1);
    }

    void InitButton() {
      adjustment_ = gtk_adjustment_new(0.0, -1e100, 1e100, 1, 0, 0);
      spin_button_ = gtk_spin_button_new(adjustment_, 100, 20);
      frame_spin_button_ = gtk_frame_new(nullptr);
      gtk_frame_set_child(GTK_FRAME(frame_spin_button_), spin_button_);
      gtk_grid_attach(GTK_GRID(grid_), frame_spin_button_, 1, 0, 1, 1);
    }

};

#endif
