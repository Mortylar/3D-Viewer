#include "main_widget.h"

void s21::MainWidget::BuildWidget() {
  CreatePannel();
  GridPlacement();
}

void s21::MainWidget::CreatePannel() {
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

void s21::MainWidget::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
}

void s21::MainWidget::GridPlacement() {
  gtk_grid_attach(GTK_GRID(grid_), file_->GetRoot(), 0, 0, 9, 1);
  gtk_grid_attach(GTK_GRID(grid_), start_button_frame_, 9, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid_), affine_pannel_->GetRoot(), 0, 1, 5, 11);

  gtk_grid_attach(GTK_GRID(grid_), info_pannel_->GetRoot(), 5, 1, 5, 3);
  gtk_grid_attach(GTK_GRID(grid_), line_pannel_->GetRoot(), 5, 4, 5, 3);
  gtk_grid_attach(GTK_GRID(grid_), point_pannel_->GetRoot(), 5, 7, 5, 3);
  gtk_grid_attach(GTK_GRID(grid_), projection_->GetRoot(), 5, 10, 5, 1);
  gtk_grid_attach(GTK_GRID(grid_), area_color_pannel_->GetFrame(), 5, 11, 5, 1);

  gtk_grid_attach(GTK_GRID(grid_), area_->GetRoot(), 10, 0, 10, 12);
}

void s21::MainWidget::RemovePannel() {
  delete affine_pannel_;
  delete info_pannel_;
  delete point_pannel_;
  delete line_pannel_;
  delete area_;
  delete file_;
  delete projection_;
  delete area_color_pannel_;
}

void s21::MainWidget::CreateAffinePannel() {
  affine_pannel_ = new s21::AffinePannel(data_->GetAffineData());
  affine_pannel_->BuildWidget();
  affine_pannel_->SetMother(this);
}

void s21::MainWidget::CreateInfoPannel() {
  info_pannel_ = new s21::InfoPannel();
  info_pannel_->BuildWidget();
  info_pannel_->SetMother(this);
}

void s21::MainWidget::CreateLinePannel() {
  line_pannel_ = new s21::LinePannel(data_->GetLineData());
  line_pannel_->BuildWidget();
  line_pannel_->SetMother(this);
}

void s21::MainWidget::CreatePointPannel() {
  point_pannel_ = new s21::PointPannel(data_->GetPointData());
  point_pannel_->BuildWidget();
  point_pannel_->SetMother(this);
}

void s21::MainWidget::CreateFileChooser() {
  file_ = new s21::FileChooser();
  start_button_ = gtk_button_new_with_label("Load File");
  start_button_frame_ = gtk_frame_new(nullptr);
  gtk_frame_set_child(GTK_FRAME(start_button_frame_), start_button_);
  g_signal_connect(start_button_, "clicked", G_CALLBACK(LoadFile), this);
}

void s21::MainWidget::CreateProjectionPannel() {
  projection_ = new s21::ProjectionPannel();
  projection_->SetValue(data_->GetProjection());
}

void s21::MainWidget::CreateAreaColorPannel() {
  area_color_pannel_ = new s21::AreaColorPannel(data_);
  area_color_pannel_->BuildWidget();
  area_color_pannel_->SetMother(this);
}

void s21::MainWidget::CreateDrawingArea() {
  area_ = new s21::DrawingArea(data_, controller_);
  area_->SetMother(this);
}

void s21::MainWidget::CreateMediaButton() {
  media_button_ = gtk_button_new_with_label("Media");
  g_signal_connect(GTK_BUTTON(media_button_), "clicked", G_CALLBACK(OpenMedia),
                   this);
}

void s21::MainWidget::Update() {
  UpdateData();
  SetInfo();
}

void s21::MainWidget::UpdateData() {
  affine_pannel_->Update();
  line_pannel_->Update();
  point_pannel_->Update();
  area_color_pannel_->Update();
  data_->SetProjection(projection_->GetValue());
}

void s21::MainWidget::SetInfo() {
  info_pannel_->SetFileName(file_->GetFileName());
  info_pannel_->SetVertexCount(controller_->GetVertexCount());
  info_pannel_->SetEdgesCount(controller_->GetSurfacesCount());
}

void s21::MainWidget::ReadAndDrawFile(const char* file_name) {
  controller_->ReadFile(file_name);
  area_->SetBuffer();
  area_->CatchSignal();
  SetInfo();
}

void s21::MainWidget::ErrorMessage(std::string& error_message) {
  GtkDialogFlags flags = static_cast<GtkDialogFlags>(
      GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL);
  GtkWidget* error_window =
      gtk_dialog_new_with_buttons("_ERROR_", GTK_WINDOW(window_), flags,
                                  "LADNO", GTK_RESPONSE_NONE, nullptr);

  GtkWidget* content_area =
      gtk_dialog_get_content_area(GTK_DIALOG(error_window));
  GtkWidget* label = gtk_label_new(error_message.data());

  g_signal_connect_swapped(error_window, "response",
                           G_CALLBACK(gtk_window_destroy), error_window);
  gtk_box_append(GTK_BOX(content_area), label);
  gtk_widget_set_visible(error_window, true);
}
