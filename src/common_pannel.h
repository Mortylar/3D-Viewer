#ifndef SRC_COMMON_PANNEL_H_
#define SRC_COMMON_PANNEL_H_

#include <gtk/gtk.h>

class CommonPannel {
  public:
    CommonPannel() {
      grid_ = gtk_grid_new();
      frame_ = gtk_frame_new(nullptr);
      gtk_grid_attach(GTK_GRID(grid_), frame_, 0, 0, 1, 1);
    }

    ~CommonPannel(){};

    virtual GtkWidget* GetRoot() = 0;


  protected:
    GtkWidget* grid_;
    GtkWidget* frame_;
};

#endif

