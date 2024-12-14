#ifndef SRC_VIEW_WIDGET_MAIN_WIDGET_H_
#define SRC_VIEW_WIDGET_MAIN_WIDGET_H_

#include "../../controller/controller.h"
#include "../../libs/data.h"
#include "combo_widget.h"
#include "drawing_area.h"
#include "pair_widget.h"
#include "pannel.h"
#include "widget.h"

namespace s21 {
class MainWidget : public Widget {
 public:
  MainWidget(GtkApplication* app, GtkWidget* window, Data* data,
             s21::Controller* controller)
      : application_(app),
        window_(window),
        data_(data),
        controller_(controller) {
    InitGrid();
  };

  ~MainWidget() { RemoveWidget(); };

  void SetName(const char* name) override { s21::Widget::SetName(name); }

  const char* GetName() override { return s21::Widget::GetName(); }

  void SetMother(s21::Widget* mother) override {}

  void CatchSignal() override {
    Update();
    area_->CatchSignal();
  }

  void SendSignal() override {}

  void BuildWidget();

  void RemoveWidget() { RemovePannel(); }

 private:
  s21::Data* data_ = nullptr;
  GtkWidget* grid_ = nullptr;
  GtkApplication* application_ = nullptr;
  GtkWidget* window_ = nullptr;
  s21::Controller* controller_ = nullptr;

  GtkWidget* start_button_ = nullptr;
  GtkWidget* start_button_frame_ = nullptr;
  s21::FileChooser* file_ = nullptr;
  s21::AffinePannel* affine_pannel_ = nullptr;
  s21::InfoPannel* info_pannel_ = nullptr;
  s21::LinePannel* line_pannel_ = nullptr;
  s21::PointPannel* point_pannel_ = nullptr;
  s21::MediaPannel* media_pannel_ = nullptr;
  s21::ProjectionPannel* projection_ = nullptr;
  s21::AreaColorPannel* area_color_pannel_ = nullptr;

  s21::DrawingArea* area_ = nullptr;
  GtkWidget* media_button_ = nullptr;

  void CreatePannel();
  void InitGrid();
  void GridPlacement();
  void RemovePannel();
  void CreateAffinePannel();
  void CreateInfoPannel();
  void CreateLinePannel();
  void CreatePointPannel();
  void CreateFileChooser();
  void CreateProjectionPannel();
  void CreateAreaColorPannel();
  void CreateDrawingArea();
  void CreateMediaButton();

  static void OpenMedia(GtkWidget* button, s21::MainWidget* self) {
    if (self->media_pannel_) delete self->media_pannel_;
    self->media_pannel_ =
        new s21::MediaPannel(self->window_, self->controller_);
    self->media_pannel_->BuildWidget();
    gtk_widget_set_visible(self->media_pannel_->GetWindow(), true);
  }

  void Update();
  void UpdateData();
  void SetInfo();

  static void LoadFile(GtkWidget* button, s21::MainWidget* self) {
    const char* file_name = self->file_->GetValue();
    if (file_name) {
      self->data_->SetFileName(file_name);
      try {
        self->ReadAndDrawFile(file_name);
      } catch (std::exception& err) {
        std::string err_message(err.what());
        self->ErrorMessage(err_message);
      }
    }
  }

  void ReadAndDrawFile(const char* file_name);
  void ErrorMessage(std::string& error_message);
};
}  // namespace s21

#endif
