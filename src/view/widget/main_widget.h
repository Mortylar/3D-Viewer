#ifndef SRC_VIEW_WIDGET_MAIN_WIDGET_H_
#define SRC_VIEW_WIDGET_MAIN_WIDGET_H_

#include <iostream>  //TODO remove

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

  ~MainWidget(){};

  void SetName(const char* name) override { s21::Widget::SetName(name); }

  const char* GetName() override { return s21::Widget::GetName(); }

  void SetMother(s21::Widget* mother) override {}

  void CatchSignal() override {
    Update();
    area_->CatchSignal();
  }

  void SendSignal() override {}

  void BuildWidget() {
    CreatePannel();
    GridPlacement();
  }

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
  // GtkWidget* info_button_ = nullptr;
  s21::LinePannel* line_pannel_ = nullptr;
  s21::PointPannel* point_pannel_ = nullptr;
  s21::MediaPannel* media_pannel_ = nullptr;
  s21::ProjectionPannel* projection_ = nullptr;
  s21::AreaColorPannel* area_color_pannel_ = nullptr;

  s21::DrawingArea* area_ = nullptr;
  GtkWidget* media_button_ = nullptr;

  void CreatePannel() {
    CreateAffinePannel();
    CreateInfoPannel();
    CreateLinePannel();
    CreatePointPannel();
    CreateDrawingArea();
    CreateFileChooser();
    CreateProjectionPannel();
    CreateMediaButton();
    CreateAreaColorPannel();
  }

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    // gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    // gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void GridPlacement() {
    gtk_grid_attach(GTK_GRID(grid_), file_->GetRoot(), 0, 0, 9, 1);
    gtk_grid_attach(GTK_GRID(grid_), start_button_frame_, 9, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid_), affine_pannel_->GetRoot(), 0, 1, 5, 11);

    gtk_grid_attach(GTK_GRID(grid_), info_pannel_->GetRoot(), 5, 1, 5, 3);
    gtk_grid_attach(GTK_GRID(grid_), line_pannel_->GetRoot(), 5, 4, 5, 3);
    gtk_grid_attach(GTK_GRID(grid_), point_pannel_->GetRoot(), 5, 7, 5, 3);
    gtk_grid_attach(GTK_GRID(grid_), projection_->GetRoot(), 5, 10, 5, 1);
    gtk_grid_attach(GTK_GRID(grid_), area_color_pannel_->GetFrame(), 5, 11, 5,
                    1);

    gtk_grid_attach(GTK_GRID(grid_), area_->GetRoot(), 10, 0, 10, 12);
  }

  void RemovePannel() {
    delete affine_pannel_;
    delete info_pannel_;
    delete point_pannel_;
    delete line_pannel_;
    delete area_;
    delete file_;
    delete projection_;
    delete area_color_pannel_;
  }

  void CreateAffinePannel() {
    affine_pannel_ = new s21::AffinePannel(data_->GetAffineData());
    affine_pannel_->BuildWidget();
    affine_pannel_->SetMother(this);
  }

  void CreateInfoPannel() {
    info_pannel_ = new s21::InfoPannel();
    info_pannel_->BuildWidget();
    info_pannel_->SetMother(this);
  }

  void CreateLinePannel() {
    line_pannel_ = new s21::LinePannel(data_->GetLineData());
    line_pannel_->BuildWidget();
    line_pannel_->SetMother(this);
  }

  void CreatePointPannel() {
    point_pannel_ = new s21::PointPannel(data_->GetPointData());
    point_pannel_->BuildWidget();
    point_pannel_->SetMother(this);
  }

  void CreateFileChooser() {
    file_ = new s21::FileChooser();
    start_button_ = gtk_button_new_with_label("Load File");
    start_button_frame_ = gtk_frame_new(nullptr);
    gtk_frame_set_child(GTK_FRAME(start_button_frame_), start_button_);
    g_signal_connect(start_button_, "clicked", G_CALLBACK(LoadFile), this);
  }

  void CreateMediaPannel() {
    media_pannel_ = new s21::MediaPannel(window_, controller_);
    media_pannel_->BuildWidget();
    media_pannel_->SetMother(this);
  }

  void CreateProjectionPannel() { projection_ = new s21::ProjectionPannel(); }

  void CreateAreaColorPannel() {
    area_color_pannel_ = new s21::AreaColorPannel(data_);
    area_color_pannel_->BuildWidget();
    area_color_pannel_->SetMother(this);
  }

  void CreateDrawingArea() {
    area_ = new s21::DrawingArea(data_, controller_);
    area_->SetMother(this);
  }

  void CreateMediaButton() {
    media_button_ = gtk_button_new_with_label("Media");
    g_signal_connect(GTK_BUTTON(media_button_), "clicked",
                     G_CALLBACK(OpenMedia), this);
  }

  static void OpenMedia(GtkWidget* button, s21::MainWidget* self) {
    size_t scale = gtk_widget_get_scale_factor(self->GetFrame());
    size_t width = gtk_widget_get_width(self->GetFrame());
    size_t height = gtk_widget_get_height(self->GetFrame());
    if (self->media_pannel_) delete self->media_pannel_;
    self->media_pannel_ =
        new s21::MediaPannel(self->window_, self->controller_);
    self->media_pannel_->BuildWidget();
    gtk_widget_set_visible(self->media_pannel_->GetWindow(), true);
  }

  static void CloseMediaPannel(GtkWidget* media_window, s21::MainWidget* self) {
    delete self->media_pannel_;
    self->media_pannel_ = nullptr;
  }

  void Update() {
    UpdateData();
    SetInfo();
  }

  void UpdateData() {
    affine_pannel_->Update();
    line_pannel_->Update();
    point_pannel_->Update();
    area_color_pannel_->Update();
    data_->SetProjection(projection_->GetValue());
  }

  void SetInfo() {
    info_pannel_->SetFileName(file_->GetFileName());
    info_pannel_->SetVertexCount(controller_->GetVertexCount());
    info_pannel_->SetEdgesCount(controller_->GetSurfacesCount());  // TODO
  }

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

  void ReadAndDrawFile(const char* file_name) {
    controller_->ReadFile(file_name);
    area_->SetBuffer();
    area_->CatchSignal();
    SetInfo();
  }

  void ErrorMessage(std::string& error_message) {
    GtkWidget* error_window = gtk_dialog_new_with_buttons(
        "_ERROR_", GTK_WINDOW(window_), GTK_DIALOG_DESTROY_WITH_PARENT, "LADNO",
        GTK_RESPONSE_NONE, nullptr);

    GtkWidget* content_area =
        gtk_dialog_get_content_area(GTK_DIALOG(error_window));
    GtkWidget* label = gtk_label_new(error_message.data());

    g_signal_connect_swapped(error_window, "response",
                             G_CALLBACK(gtk_window_destroy), error_window);
    gtk_box_append(GTK_BOX(content_area), label);
    gtk_widget_set_visible(error_window, true);
  }
};
}  // namespace s21

#endif
