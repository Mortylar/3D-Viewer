#include "view.h"

void s21::View::RunWindow(char* exe_name) {
  exe_name_ = exe_name;
  application_ = gtk_application_new("_3D.Viewer", APPLICATION_NONE_FLAG);
  g_signal_connect(application_, "activate", G_CALLBACK(Activate), this);
  g_application_run(G_APPLICATION(application_), 0, nullptr);
  g_object_unref(application_);
}

void s21::View::InitWindow() {
  window_ = gtk_application_window_new(application_);
  gtk_window_set_title(GTK_WINDOW(window_), "3DViewer");
  gtk_window_set_default_size(GTK_WINDOW(window_), 90, 10);  // TODO
}

void s21::View::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window_), grid_);
}

void s21::View::InitData() {
  data_ = new s21::Data();
  DataSaver ds(data_);
  ds.LoadData();
  data_->SetExecutionName(exe_name_);
}

void s21::View::InitMainWidget() {
  main_widget_ = new s21::MainWidget(application_, window_, data_, controller_);
  main_widget_->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid_), main_widget_->GetRoot(), 0, 0, 1, 1);
}
