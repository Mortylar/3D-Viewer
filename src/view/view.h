#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <gtk/gtk.h>

#include "../controller/controller.h"

#include "../libs/data.h"
#include "widget/main_widget.h"
#include "widget/widget.h"

#ifdef __APPLE__
#define APPLICATION_NONE_FLAG G_APPLICATION_DEFAULT_FLAGS
#else
#define APPLICATION_NONE_FLAG G_APPLICATION_FLAGS_NONE
#endif

namespace s21 {
class View {
 public:
  explicit View( s21::Controller* controller):controller_(controller){}

  ~View(){};


  void RunWindow() {
    application_ = gtk_application_new("org.gtk.example",APPLICATION_NONE_FLAG);
    g_signal_connect(application_, "activate", G_CALLBACK(Activate), this);
    g_application_run(G_APPLICATION(application_), 0, nullptr);
    g_object_unref(application_);
  }

 private:
   GtkApplication* application_ = nullptr;
   GtkWidget* window_ = nullptr;
   GtkWidget* grid_ = nullptr;
   s21::Data* data_ = nullptr;
   s21::MainWidget* main_widget_ = nullptr;
   s21::Controller* controller_ = nullptr;

   static void Activate(GtkApplication* app, s21::View* self) {
     self->InitWindow();
     self->InitGrid();
     self->InitData();
     self->InitMainWidget();
     gtk_widget_set_visible(self->window_, true);
    }

    void InitWindow() {
      window_ = gtk_application_window_new(application_);
      gtk_window_set_title(GTK_WINDOW(window_), "3DViewer");
      gtk_window_set_default_size(GTK_WINDOW(window_), 90, 10); //TODO
    }

    void InitGrid() {
      grid_ = gtk_grid_new();
      gtk_window_set_child(GTK_WINDOW(window_), grid_);
    }

    void InitData() {
      data_ = new s21::Data();
          //TODO
    }

    void InitMainWidget() {
      main_widget_ = new s21::MainWidget(application_, window_, data_, controller_);
      main_widget_->BuildWidget();
      gtk_grid_attach(GTK_GRID(grid_), main_widget_->GetRoot(), 0,0,1,1);
    }

};
}  // namespace s21
#endif
