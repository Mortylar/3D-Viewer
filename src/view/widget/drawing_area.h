#ifndef SRC_VIEW_WIDGET_DRAWING_AREA_H_
#define SRC_VIEW_WIDGET_DRAWING_AREA_H_

#include <gtk/gtk.h>

#include "../../controller/controller.h"
#include "../../libs/data.h"
#include "widget.h"
#include <epoxy/gl.h>

namespace s21 {
class DrawingArea : public Widget {
public:
  DrawingArea(s21::Data *data, s21::Controller *controller)
      : data_(data), controller_(controller) {
    InitArea();
  }

  ~DrawingArea() {
  };

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override { gtk_widget_queue_draw(area_); } // TODO

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  } // TODO

  void SetBuffer() {
    gtk_gl_area_make_current(GTK_GL_AREA(area_));
    context_ = gtk_gl_area_get_context(GTK_GL_AREA(area_));
    controller_->SetBuffer();
  }

  static void Realize(GtkWidget *area, s21::DrawingArea *self) {
    gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
  }

  static void Render(GtkWidget *area, GdkGLContext *context,
                     s21::DrawingArea *self) { // TODO private
    gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
    self->controller_->Draw(); // TODO
  }

private:
  GtkWidget *area_ = nullptr;
  GdkGLContext *context_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::Controller *controller_ = nullptr;

  s21::Data *data_ = nullptr;

  void InitArea() {
    area_ = gtk_gl_area_new();
    gtk_widget_set_hexpand(area_, true);
    gtk_widget_set_vexpand(area_, true);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), area_);
    g_signal_connect(area_, "realize", G_CALLBACK(Realize), this);
    g_signal_connect(area_, "render", G_CALLBACK(Render), this);
    controller_->SetGLArea(GTK_GL_AREA(area_));
    controller_->ConnectData(data_);
  }
};
} // namespace s21

#endif
