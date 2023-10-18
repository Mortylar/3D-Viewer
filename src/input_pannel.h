#ifndef INPUT_PANNEL_H_
#define INPUT_PANNEL_H_

#include<gtk/gtk.h>

#include "common_pannel.h"

class InputPannel: private CommonPannel{

  public:
    InputPannel() {
      InitPannel();
    };
    ~InputPannel(){};

    void InitPannel() {
      base_grid_ = gtk_grid_new();
      x_label_ = gtk_label_new("x_label");
      x_line_ = gtk_text_new();

      label_frame_ = gtk_frame_new(nullptr);
      gtk_frame_set_child(GTK_FRAME(label_frame_), x_label_);

      line_frame_ = gtk_frame_new(nullptr); 
      gtk_frame_set_child(GTK_FRAME(line_frame_), x_line_);

      gtk_grid_attach(GTK_GRID(base_grid_), label_frame_, 0, 0, 1, 1);
      gtk_grid_attach(GTK_GRID(base_grid_), line_frame_, 1, 0, 1, 1);

      gtk_frame_set_child(GTK_FRAME(frame_), base_grid_);
      //common_frame_ = gtk_frame_new(NULL);
      //gtk_frame_set_child(GTK_FRAME(common_frame_), base_grid_);
      //common_grid_ = gtk_grid_new();
      //gtk_grid_attach(GTK_GRID(common_grid_), common_frame_, 0,0,1,1);
    }

    GtkWidget* GetRoot() {
     // return common_grid_;
    return grid_;
    }

  private:
    GtkWidget* base_grid_ = nullptr;
    GtkWidget* x_label_ = nullptr;
    GtkWidget* x_line_ = nullptr;
    GtkWidget* label_frame_ = nullptr;
    GtkWidget* line_frame_ = nullptr;

    //GtkWidget* common_frame_;
    //GtkWidget* common_grid_;
};

#endif
