#ifndef SRC_VIEW_WIDGET_MAIN_WIDGET_H_
#define SRC_VIEW_WIDGET_MAIN_WIDGET_H_

#include "../../controller/controller.h"
#include "combo_widget.h"
#include "drawing_area.h"
#include "pair_widget.h"
#include "pannel.h"
#include "widget.h"

#include "../../libs/data.h"

#include <iostream> //TODO remove


namespace s21 {
class MainWidget : public Widget {
public:
  MainWidget(GtkApplication* app, GtkWidget* window, Data *data, s21::Controller *controller)
      : application_(app), window_(window), data_(data), controller_(controller) {
    InitGrid();
  };

  ~MainWidget(){};

  void SetName(const char *name) override { s21::Widget::SetName(name); }

  const char *GetName() override { return s21::Widget::GetName(); }

  void SetMother(s21::Widget *mother) override {}

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
  s21::Data *data_ = nullptr;
  GtkWidget *grid_ = nullptr;
  GtkApplication* application_ = nullptr;
  GtkWidget* window_ = nullptr;
  s21::Controller *controller_ = nullptr;

  GtkWidget *start_button_ = nullptr;
  GtkWidget *start_button_frame_ = nullptr;
  s21::FileChooser *file_ = nullptr;
  s21::AffinePannel *affine_pannel_ = nullptr;
  s21::InfoPannel* info_pannel_ = nullptr;
  GtkWidget* info_button_ = nullptr;
  s21::LinePannel *line_pannel_ = nullptr;
  s21::PointPannel *point_pannel_ = nullptr;
  s21::ProjectionPannel* projection_ = nullptr;

  s21::DrawingArea *area_ = nullptr;
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
    gtk_grid_attach(GTK_GRID(grid_), affine_pannel_->GetRoot(), 0, 1, 5, 9);

    //gtk_grid_attach(GTK_GRID(grid_), info_pannel_->GetRoot(), 5, 1, 5, 3);
    gtk_grid_attach(GTK_GRID(grid_), info_button_, 5, 1, 5, 1);
    gtk_grid_attach(GTK_GRID(grid_), line_pannel_->GetRoot(), 5, 2, 5, 3);
    gtk_grid_attach(GTK_GRID(grid_), point_pannel_->GetRoot(), 5, 5, 5, 3);
    gtk_grid_attach(GTK_GRID(grid_), projection_->GetRoot(), 5, 8, 5, 1); 
    gtk_grid_attach(GTK_GRID(grid_), media_button_, 5, 9, 5, 1);


    gtk_grid_attach(GTK_GRID(grid_), area_->GetRoot(), 10, 0, 10, 10);
  }

  void RemovePannel() {
    delete affine_pannel_;
    delete info_pannel_;
    delete point_pannel_;
    delete line_pannel_;
    delete area_;
    delete file_;
    delete projection_;
  }

  void CreateAffinePannel() {
    affine_pannel_ = new s21::AffinePannel(data_->GetAffineData());
    affine_pannel_->BuildWidget();
    affine_pannel_->SetMother(this);
  }

  void CreateInfoPannel() {
    info_button_ = gtk_button_new_with_label("_INFO_");
    //info_pannel_ = new s21::InfoPannel(application_);
    //info_pannel_->BuildWidget();
    //info_pannel_->SetMother(this);
    g_signal_connect(GTK_BUTTON(info_button_), "clicked", G_CALLBACK(OpenInfo), this);
  }

  static void OpenInfo(GtkWidget* button, s21::MainWidget* self) {
    if (self->info_pannel_) delete self->info_pannel_;
    self->info_pannel_ = new s21::InfoPannel(self->application_);
    self->info_pannel_->BuildWidget();
    self->SetInfo();
    gtk_widget_show(self->info_pannel_->GetWindow());
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

  void CreateProjectionPannel() {
    projection_ = new s21::ProjectionPannel();
  }

  void CreateDrawingArea() {
    area_ = new s21::DrawingArea(data_, controller_);
    area_->SetMother(this);
  }

  void CreateMediaButton() {
    media_button_ = gtk_button_new_with_label("Media");
    g_signal_connect(GTK_BUTTON(media_button_), "clicked", G_CALLBACK(OpenMedia), this);
  }

  static void OpenMedia(GtkWidget* button, s21::MainWidget* self) {
    size_t scale = gtk_widget_get_scale_factor(self->GetFrame());
    g_warning("\nscale = %li\n", scale);
    size_t width = gtk_widget_get_width(self->GetFrame());
    size_t height = gtk_widget_get_height(self->GetFrame());
    self->controller_->SavePicture(width*scale, height*scale);
  }

  void Update() {
    UpdateData();
    //SetInfo();
  }

  void UpdateData() {
    affine_pannel_->Update();
    line_pannel_->Update();
    point_pannel_->Update();
    data_->SetProjection(projection_->GetValue());
  }

  void SetInfo() {
    info_pannel_->SetFileName(file_->GetFileName());
    info_pannel_->SetVertexCount(controller_->GetVertexCount());
    info_pannel_->SetEdgesCount(controller_->GetSurfacesCount()); // TODO
  }

  static void LoadFile(GtkWidget *button, s21::MainWidget *self) {
    const char *file_name = self->file_->GetValue();
    if (file_name) {
      self->data_->SetFileName(file_name);
      self->controller_->ReadFile(file_name);
      self->area_->SetBuffer();
      self->area_->CatchSignal();
    }
  }
};
} // namespace s21

#endif
