#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <gtk/gtk.h>

#include "../controller/controller.h"
#include "../libs/data.h"
#include "../libs/data_saver.h"
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
  explicit View(s21::Controller* controller) : controller_(controller) {}

  ~View() {
    DataSaver ds(data_);
    ds.SaveData();
    delete main_widget_;
    delete data_;
  };

  void RunWindow();

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

  void InitWindow();
  void InitGrid();
  void InitData();
  void InitMainWidget();
};
}  // namespace s21
#endif
