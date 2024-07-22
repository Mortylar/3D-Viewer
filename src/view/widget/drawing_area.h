#ifndef SRC_VIEW_WIDGET_DRAWING_AREA_H_
#define SRC_VIEW_WIDGET_DRAWING_AREA_H_

#include <gtk/gtk.h>

#include "../../controller/controller.h"
#include "../../libs/data.h"
#include "widget.h"

namespace s21 {
class DrawingArea : public Widget {
 public:
  DrawingArea(s21::Data *data, s21::Controller *controller)
      : data_(data), controller_(controller) {
    InitArea();
  }

  ~DrawingArea(){};

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override { gtk_widget_queue_draw(area_); }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void SetBuffer();

 private:
  GtkWidget *area_ = nullptr;
  GdkGLContext *context_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::Controller *controller_ = nullptr;

  s21::Data *data_ = nullptr;

  void InitArea();

  static void Realize(GtkWidget *area, s21::DrawingArea *self) {
    gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
  }

  static void Render(GtkWidget *area, GdkGLContext *context,
                     s21::DrawingArea *self) {
    gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
    self->controller_->Draw();
  }
};
}  // namespace s21

#endif
