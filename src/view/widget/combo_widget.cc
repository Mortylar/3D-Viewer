#include "combo_widget.h"

void s21::AffinePannel::BuildWidget() {
  CreateTranslationPannel();
  CreateRotationPannel();
  CreateScalingPannel();
  InitCommonScalingButton();
  InitResetButton();
  SetMother(this);
}

void s21::AffinePannel::CollectData() {
  CollectTranslation();
  CollectRotation();
  CollectScaling();
}

void s21::AffinePannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::AffinePannel::InitResetButton() {
  reset_button_ = gtk_button_new_with_label("RESET");
  g_signal_connect(reset_button_, "clicked", G_CALLBACK(Reset), this);
  gtk_grid_attach(GTK_GRID(grid_), reset_button_, 0, 11, 1, 1);
}

void s21::AffinePannel::InitCommonScalingButton() {
  label_ = new s21::Label("ALL_AXIS");

  adjustment_ = gtk_adjustment_new(0.0, -1.0, 1.0, 0.01, 12, 0);
  scale_button_ = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment_);
  g_signal_connect(adjustment_, "value_changed",
                   G_CALLBACK(CommonScalingChanged), this);
  common_button_grid_ = gtk_grid_new();
  common_button_frame_ = gtk_frame_new(nullptr);
  gtk_frame_set_child(GTK_FRAME(common_button_frame_), common_button_grid_);

  gtk_grid_attach(GTK_GRID(common_button_grid_), label_->GetRoot(), 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(common_button_grid_), scale_button_, 1, 0, 3, 1);
  gtk_grid_attach(GTK_GRID(grid_), common_button_frame_, 0, 10, 1, 1);
  gtk_grid_set_column_homogeneous(GTK_GRID(common_button_grid_), true);
}

void s21::AffinePannel::CollectTranslation() {
  std::vector<float *> translation_data = translation_pannel_->GetData();
  data_->SetTranslation(*translation_data[0], *translation_data[1],
                        *translation_data[2]);
}

void s21::AffinePannel::CollectRotation() {
  std::vector<float *> rotation_data = rotation_pannel_->GetData();
  data_->SetRotation(*rotation_data[0], *rotation_data[1], *rotation_data[2]);
}

void s21::AffinePannel::CollectScaling() {
  std::vector<float *> scaling_data = scaling_pannel_->GetData();
  double scaling_vector[scaling_data.size()] = {0.0, 0.0, 0.0};
  const int k_scaling_factor = 20;
  for (size_t i = 0; i < scaling_data.size(); ++i) {
    if (*scaling_data[i] >= 0.0) {
      scaling_vector[i] = 1.0 + *scaling_data[i] * k_scaling_factor;
    } else {
      scaling_vector[i] = 1.0 / (1.0 + -*scaling_data[i] * k_scaling_factor);
    }
  }
  data_->SetScaling(scaling_vector[0], scaling_vector[1], scaling_vector[2]);
}

void s21::AffinePannel::CreateTranslationPannel() {
  s21::TranslationPannelFactory factory;
  translation_pannel_ =
      static_cast<s21::DSliderPannel *>(factory.CreateWidget());
  translation_pannel_->SetValue(0, data_->GetTranslation()[0]);
  translation_pannel_->SetValue(1, data_->GetTranslation()[1]);
  translation_pannel_->SetValue(2, data_->GetTranslation()[2]);
  translation_pannel_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), translation_pannel_->GetRoot(), 0, 0, 1, 3);
}

void s21::AffinePannel::CreateRotationPannel() {
  s21::RotationPannelFactory factory;
  rotation_pannel_ = static_cast<s21::DSliderPannel *>(factory.CreateWidget());
  rotation_pannel_->SetValue(0, data_->GetRotation()[0]);
  rotation_pannel_->SetValue(1, data_->GetRotation()[1]);
  rotation_pannel_->SetValue(2, data_->GetRotation()[2]);
  rotation_pannel_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), rotation_pannel_->GetRoot(), 0, 4, 1, 3);
}

void s21::AffinePannel::CreateScalingPannel() {
  s21::ScalingPannelFactory factory;
  scaling_pannel_ = static_cast<s21::DSliderPannel *>(factory.CreateWidget());
  float scaling_data[3]{0};
  const int k_scaling_factor = 20;
  for (int i = 0; i < 3; ++i) {
    float this_axis = data_->GetScaling()[i];
    if (this_axis < 1) {
      scaling_data[i] = (this_axis - 1) / (k_scaling_factor * this_axis);
    } else {
      scaling_data[i] = (this_axis - 1) / k_scaling_factor;
    }
    scaling_pannel_->SetValue(i, scaling_data[i]);
  }
  scaling_pannel_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), scaling_pannel_->GetRoot(), 0, 7, 1, 3);
}

void s21::LinePannel::BuildWidget() {
  CreateSizePannel();
  CreateColorPannel();
  CreateTypePannel();
}

void s21::LinePannel::Update() {
  data_->SetType(type_->GetValue());
  data_->SetColor(color_->GetColor());
  data_->SetSize(size_->GetValue());
}

void s21::LinePannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::LinePannel::CreateSizePannel() {
  s21::LineSizeFactory factory;
  size_ = static_cast<s21::LabelDSpinButtonPair *>(factory.CreateWidget());
  size_->SetValue(data_->GetSize());
  size_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0, 0, 1, 1);
}

void s21::LinePannel::CreateColorPannel() {
  s21::LineColorFactory factory;
  color_ = static_cast<s21::LabelColorButtonPair *>(factory.CreateWidget());
  color_->SetValue(*(data_->GetColor()));
  color_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
}

void s21::LinePannel::CreateTypePannel() {
  s21::LineTypeFactory factory;
  type_ = static_cast<s21::LabelDropDownButtonPair *>(factory.CreateWidget());
  type_->SetValue(data_->GetType());
  type_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0, 2, 1, 1);
}

void s21::PointPannel::BuildWidget() {
  CreateSizePannel();
  CreateColorPannel();
  CreateTypePannel();
}

void s21::PointPannel::Update() {
  data_->SetType(type_->GetValue());
  data_->SetColor(color_->GetColor());
  data_->SetSize(size_->GetValue());
}

void s21::PointPannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::PointPannel::CreateSizePannel() {
  s21::PointSizeFactory factory;
  size_ = static_cast<s21::LabelDSpinButtonPair *>(factory.CreateWidget());
  size_->SetValue(data_->GetSize());
  size_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0, 0, 1, 1);
}

void s21::PointPannel::CreateColorPannel() {
  s21::PointColorFactory factory;
  color_ = static_cast<s21::LabelColorButtonPair *>(factory.CreateWidget());
  color_->SetValue(*(data_->GetColor()));
  color_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
}

void s21::PointPannel::CreateTypePannel() {
  s21::PointTypeFactory factory;
  type_ = static_cast<s21::LabelDropDownButtonPair *>(factory.CreateWidget());
  type_->SetValue(data_->GetType());
  type_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0, 2, 1, 1);
}

void s21::InfoPannel::BuildWidget() {
  CreateFileNamePannel();
  CreateVertexInfoPannel();
  CreateEdgesInfoPannel();
}

void s21::InfoPannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::InfoPannel::CreateFileNamePannel() {
  s21::FileNamePannelFactory factory;
  file_name_ = static_cast<s21::LabelPair *>(factory.CreateWidget());
  file_name_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), file_name_->GetRoot(), 0, 0, 1, 1);
}

void s21::InfoPannel::CreateVertexInfoPannel() {
  s21::VertexInfoPannelFactory factory;
  vertex_count_ = static_cast<s21::LabelPair *>(factory.CreateWidget());
  vertex_count_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), vertex_count_->GetRoot(), 0, 1, 1, 1);
}

void s21::InfoPannel::CreateEdgesInfoPannel() {
  s21::EdgesInfoPannelFactory factory;
  edges_count_ = static_cast<s21::LabelPair *>(factory.CreateWidget());
  edges_count_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), edges_count_->GetRoot(), 0, 2, 1, 1);
}

void s21::MediaPannel::BuildWidget() {
  CreateCapturePannel();
  CreateGifPannel();
  InitCaptureButton();
  InitGifButton();
}

void s21::MediaPannel::InitWindow() {
  app_ = gtk_window_get_application(GTK_WINDOW(main_window_));
  window_ = gtk_window_new();
  gtk_window_set_modal(GTK_WINDOW(window_), true);
  gtk_window_set_title(GTK_WINDOW(window_), "_MEDIA_");
  gtk_window_set_child(GTK_WINDOW(window_), GTK_WIDGET(GetRoot()));
}

void s21::MediaPannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::MediaPannel::CreateCapturePannel() {
  CapturePannelFactory factory;
  capture_pannel_ =
      static_cast<FileSaverDropDownButtonPair *>(factory.CreateWidget());
  capture_pannel_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), capture_pannel_->GetRoot(), 0, 0, 1, 1);
}

void s21::MediaPannel::CreateGifPannel() {
  GifPannelFactory factory;
  gif_pannel_ = static_cast<FileSaverDSpinButtonPair *>(factory.CreateWidget());
  gif_pannel_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), gif_pannel_->GetRoot(), 0, 2, 1, 1);
}

void s21::MediaPannel::InitCaptureButton() {
  capture_button_ = gtk_button_new_with_label("Create Capture");
  g_signal_connect(capture_button_, "clicked", G_CALLBACK(CreateCapture), this);
  gtk_grid_attach(GTK_GRID(grid_), capture_button_, 0, 1, 1, 1);
}

void s21::MediaPannel::InitGifButton() {
  gif_button_ = gtk_button_new_with_label("Create Gif");
  gtk_grid_attach(GTK_GRID(grid_), gif_button_, 0, 3, 1, 1);
}

void s21::ProjectionPannel::BuildWidget() {}

void s21::ProjectionPannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::ProjectionPannel::CreateDropDownButtonPannel() {
  const char *name = "Projection";
  const char *types[3] = {"PARALEL", "CENTRAL", nullptr};
  projection_ = new s21::LabelDropDownButtonPair(name, types);
  projection_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), projection_->GetRoot(), 0, 0, 1, 1);
}

void s21::AreaColorPannel::BuildWidget() { CreateColorPannel(); }

void s21::AreaColorPannel::InitGrid() {
  grid_ = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
}

void s21::AreaColorPannel::CreateColorPannel() {
  s21::AreaColorFactory factory;
  color_ = static_cast<s21::LabelColorButtonPair *>(factory.CreateWidget());
  color_->SetValue(*(data_->GetAreaColor()));
  color_->SetMother(this);
  gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
}
