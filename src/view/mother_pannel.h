#ifndef SRC_MOTHER_PANNEL_H_
#define SRC_MOTHER_PANNEL_H_

#include <gtk/gtk.h>

class MotherPannel {
  public:
    MotherPannel() {
      grid_ = gtk_grid_new();
      frame_ = gtk_frame_new(nullptr);
      gtk_grid_attach(GTK_GRID(grid_), frame_, 0, 0, 1, 1);
    }

    ~MotherPannel(){};

    GtkWidget* GetRoot() {
      return grid_;
    }

    GtkWidget* GetFrame() {
      return frame_;
    }

    void SetName(const char* name) {
      gtk_frame_set_label(GTK_FRAME(frame_), name);
      gtk_frame_set_label_align(GTK_FRAME(frame_), 0.5);
    }


  private:
    GtkWidget* grid_;
    GtkWidget* frame_;
};

#endif

