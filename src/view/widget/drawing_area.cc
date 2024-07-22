#include "drawing_area.h"

void s21::DrawingArea::SetBuffer() {
  gtk_gl_area_make_current(GTK_GL_AREA(area_));
  context_ = gtk_gl_area_get_context(GTK_GL_AREA(area_));
  controller_->SetBuffer();
}

void s21::DrawingArea::InitArea() {
  area_ = gtk_gl_area_new();
  gtk_widget_set_hexpand(area_, true);
  gtk_widget_set_vexpand(area_, true);
  gtk_frame_set_child(GTK_FRAME(GetFrame()), area_);
  g_signal_connect(area_, "realize", G_CALLBACK(Realize), this);
  g_signal_connect(area_, "render", G_CALLBACK(Render), this);
  controller_->ConnectData(data_);
}
