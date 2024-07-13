#ifndef SRC_VIEW_WIDGET_COMBO_WIDGET_H_
#define SRC_VIEW_WIDGET_COMBO_WIDGET_H_

#include <gtk/gtk.h>

#include "../../controller/controller.h"
#include "../../libs/data.h"
#include "factory.h"
#include "widget.h"

namespace s21 {
class AffinePannel : public Widget {
 public:
  AffinePannel(s21::AffineData *data) : data_(data) {
    InitGrid();
    s21::Widget::SetName("_AFFINE_PANNEL_");
  }

  void BuildWidget() {
    CreateTranslationPannel();
    CreateRotationPannel();
    CreateScalingPannel();
    InitCommonScalingButton();
    InitResetButton();
    SetMother(this);
  }

  ~AffinePannel() {
    RemoveTranslationPannel();
    RemoveRotationPannel();
    RemoveScalingPannel();
  };

  void Update() { CollectData(); }

  void CollectData() {
    CollectTranslation();
    CollectRotation();
    CollectScaling();
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {  // TODO
    CollectData();
    if (mother_) SendSignal();
  }

  void SendSignal() override { mother_->CatchSignal(); }

  s21::AffineData *GetData() { return data_; }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::DSliderPannel *translation_pannel_ = nullptr;
  s21::DSliderPannel *rotation_pannel_ = nullptr;
  s21::DSliderPannel *scaling_pannel_ = nullptr;
  s21::Label *label_ = nullptr;
  GtkWidget *scale_button_ = nullptr;
  GtkAdjustment *adjustment_ = nullptr;
  GtkWidget *common_button_grid_ = nullptr;
  GtkWidget *common_button_frame_ = nullptr;
  GtkWidget *reset_button_ = nullptr;

  s21::AffineData *data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void InitResetButton() {
    reset_button_ = gtk_button_new_with_label("RESET");
    g_signal_connect(reset_button_, "clicked", G_CALLBACK(Reset), this);
    gtk_grid_attach(GTK_GRID(grid_), reset_button_, 0, 11, 1, 1);
  }

  static void Reset(GtkWidget *button, s21::AffinePannel *self) {
    self->translation_pannel_->SetValue(0);
    self->rotation_pannel_->SetValue(0);
    self->scaling_pannel_->SetValue(0);
    gtk_adjustment_set_value(GTK_ADJUSTMENT(self->adjustment_), 0);
  }

  void InitCommonScalingButton() {
    label_ = new s21::Label("ALL_AXIS");

    adjustment_ = gtk_adjustment_new(0.0, -1.0, 1.0, 0.01, 12, 0);
    scale_button_ = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment_);
    g_signal_connect(adjustment_, "value_changed",
                     G_CALLBACK(CommonScalingChanged), this);
    common_button_grid_ = gtk_grid_new();
    common_button_frame_ = gtk_frame_new(nullptr);
    gtk_frame_set_child(GTK_FRAME(common_button_frame_), common_button_grid_);

    gtk_grid_attach(GTK_GRID(common_button_grid_), label_->GetRoot(), 0, 0, 1,
                    1);
    gtk_grid_attach(GTK_GRID(common_button_grid_), scale_button_, 1, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid_), common_button_frame_, 0, 10, 1, 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(common_button_grid_), true);
  }

  static void CommonScalingChanged(GtkAdjustment *adjustment,
                                   s21::AffinePannel *self) {
    float value = gtk_adjustment_get_value(GTK_ADJUSTMENT(self->adjustment_));
    self->scaling_pannel_->SetValue(value);
  }

  void CollectTranslation() {
    std::vector<float *> translation_data = translation_pannel_->GetData();
    data_->SetTranslation(*translation_data[0], *translation_data[1],
                          *translation_data[2]);
  }

  void CollectRotation() {
    std::vector<float *> rotation_data = rotation_pannel_->GetData();
    data_->SetRotation(*rotation_data[0], *rotation_data[1], *rotation_data[2]);
  }

  void CollectScaling() {
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

  void CreateTranslationPannel() {
    s21::TranslationPannelFactory factory;
    translation_pannel_ =
        static_cast<s21::DSliderPannel *>(factory.CreateWidget());
    translation_pannel_->SetValue(0, data_->GetTranslation()[0]);
    translation_pannel_->SetValue(1, data_->GetTranslation()[1]);
    translation_pannel_->SetValue(2, data_->GetTranslation()[2]);
    translation_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), translation_pannel_->GetRoot(), 0, 0, 1,
                    3);
  }

  void CreateRotationPannel() {
    s21::RotationPannelFactory factory;
    rotation_pannel_ =
        static_cast<s21::DSliderPannel *>(factory.CreateWidget());
    rotation_pannel_->SetValue(0, data_->GetRotation()[0]);
    rotation_pannel_->SetValue(1, data_->GetRotation()[1]);
    rotation_pannel_->SetValue(2, data_->GetRotation()[2]);
    rotation_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), rotation_pannel_->GetRoot(), 0, 4, 1, 3);
  }

  void CreateScalingPannel() {
    s21::ScalingPannelFactory factory;
    scaling_pannel_ = static_cast<s21::DSliderPannel *>(factory.CreateWidget());
    // TODO anti Scaling function
    scaling_pannel_->SetValue(0, data_->GetScaling()[0]);
    scaling_pannel_->SetValue(1, data_->GetScaling()[1]);
    scaling_pannel_->SetValue(2, data_->GetScaling()[2]);
    scaling_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), scaling_pannel_->GetRoot(), 0, 7, 1, 3);
  }

  void RemoveTranslationPannel() { delete translation_pannel_; }

  void RemoveRotationPannel() { delete rotation_pannel_; }

  void RemoveScalingPannel() { delete scaling_pannel_; }
};

enum class LineType {
  k_ErrorType = -1,
  k_NoLineType = 0,
  k_SolidLineType,
  k_DottedLineType
};

class LinePannel : public Widget {
 public:
  LinePannel(s21::FormatData *data)
      : data_(data) {  // connect with exterdal data
    InitGrid();
    s21::Widget::SetName("_LINE_PANNEL_");
  }

  ~LinePannel() {
    delete type_;
    delete color_;
    delete size_;
  }

  void BuildWidget() {
    CreateSizePannel();
    CreateColorPannel();
    CreateTypePannel();
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void Update() {
    data_->SetType(type_->GetValue());
    data_->SetColor(color_->GetColor());
    data_->SetSize(size_->GetValue());
  }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelDropDownButtonPair *type_ = nullptr;
  s21::LabelColorButtonPair *color_ = nullptr;
  s21::LabelDSpinButtonPair *size_ = nullptr;
  s21::FormatData *data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateSizePannel() {
    s21::LineSizeFactory factory;
    size_ = static_cast<s21::LabelDSpinButtonPair *>(factory.CreateWidget());
    size_->SetValue(data_->GetSize());
    size_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateColorPannel() {
    s21::LineColorFactory factory;
    color_ = static_cast<s21::LabelColorButtonPair *>(factory.CreateWidget());
    color_->SetValue(*(data_->GetColor()));
    color_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
  }

  void CreateTypePannel() {
    s21::LineTypeFactory factory;
    type_ = static_cast<s21::LabelDropDownButtonPair *>(factory.CreateWidget());
    type_->SetValue(data_->GetType());
    type_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0, 2, 1, 1);
  }
};

enum class PointType {
  k_ErrorType = -1,
  k_NoPointType = 0,
  k_RoundPointType,
  k_TrianglePointType,
  k_SquarePointType
};

class PointPannel : public Widget {
 public:
  PointPannel(s21::FormatData *data) : data_(data) {
    InitGrid();
    s21::Widget::SetName("_POINT_PANNEL_");
  }

  ~PointPannel() {
    delete type_;
    delete color_;
    delete size_;
  }

  void BuildWidget() {
    CreateSizePannel();
    CreateColorPannel();
    CreateTypePannel();
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void Update() {
    data_->SetType(type_->GetValue());
    data_->SetColor(color_->GetColor());
    data_->SetSize(size_->GetValue());
  }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelDropDownButtonPair *type_ = nullptr;
  s21::LabelColorButtonPair *color_ = nullptr;
  s21::LabelDSpinButtonPair *size_ = nullptr;
  s21::FormatData *data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateSizePannel() {
    s21::PointSizeFactory factory;
    size_ = static_cast<s21::LabelDSpinButtonPair *>(factory.CreateWidget());
    size_->SetValue(data_->GetSize());
    size_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateColorPannel() {
    s21::PointColorFactory factory;
    color_ = static_cast<s21::LabelColorButtonPair *>(factory.CreateWidget());
    color_->SetValue(*(data_->GetColor()));
    color_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
  }

  void CreateTypePannel() {
    s21::PointTypeFactory factory;
    type_ = static_cast<s21::LabelDropDownButtonPair *>(factory.CreateWidget());
    type_->SetValue(data_->GetType());
    type_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0, 2, 1, 1);
  }
};

class InfoPannel : public Widget {
 public:
  InfoPannel() {
    InitGrid();
    s21::Widget::SetName("_INFORMATION_PANNEL_");
  }

  ~InfoPannel(){};

  void BuildWidget() {
    CreateFileNamePannel();
    CreateVertexInfoPannel();
    CreateEdgesInfoPannel();
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override { SendSignal(); }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void SetFileName(const char *file_name) { file_name_->SetValue(file_name); }

  void SetVertexCount(size_t v_count) {
    vertex_count_->SetValue(std::to_string(v_count).data());
  }

  void SetEdgesCount(size_t edges_count) {
    edges_count_->SetValue(std::to_string(edges_count).data());  // TODO
  }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelPair *file_name_ = nullptr;
  s21::LabelPair *vertex_count_ = nullptr;
  s21::LabelPair *edges_count_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateFileNamePannel() {
    s21::FileNamePannelFactory factory;
    file_name_ = static_cast<s21::LabelPair *>(factory.CreateWidget());
    file_name_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), file_name_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateVertexInfoPannel() {
    s21::VertexInfoPannelFactory factory;
    vertex_count_ = static_cast<s21::LabelPair *>(factory.CreateWidget());
    vertex_count_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), vertex_count_->GetRoot(), 0, 1, 1, 1);
  }

  void CreateEdgesInfoPannel() {
    s21::EdgesInfoPannelFactory factory;
    edges_count_ = static_cast<s21::LabelPair *>(factory.CreateWidget());
    edges_count_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), edges_count_->GetRoot(), 0, 2, 1, 1);
  }
};

class MediaPannel : public Widget {
 public:
  MediaPannel(GtkWidget *window, s21::Controller *controller)
      : main_window_(window), controller_(controller) {
    // InitWindow();
    InitGrid();
  };

  ~MediaPannel(){};

  void BuildWidget() {
    CreateCapturePannel();
    CreateGifPannel();
    InitCaptureButton();
    InitGifButton();
  }

  GtkWidget *GetWindow() { return window_; }

  void SetMother(s21::Widget *mother) override { mother_ = mother; };

  void CatchSignal() override{};
  void SendSignal() override{};
  // gtk_window_get_application(GTK_WINDOW(window_));

 private:
  GtkApplication *app_ = nullptr;
  GtkWidget *main_window_ = nullptr;
  s21::Controller *controller_ = nullptr;
  GtkWidget *window_ = nullptr;
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::FileSaverDropDownButtonPair *capture_pannel_ = nullptr;
  s21::FileSaverDSpinButtonPair *gif_pannel_ = nullptr;
  GtkWidget *capture_button_ = nullptr;
  GtkWidget *gif_button_ = nullptr;

  void InitWindow() {
    app_ = gtk_window_get_application(GTK_WINDOW(main_window_));
    window_ = gtk_window_new();  // gtk_application_window_new(app_);
    gtk_window_set_modal(GTK_WINDOW(window_), true);
    gtk_window_set_title(GTK_WINDOW(window_), "_MEDIA_");
    gtk_window_set_child(GTK_WINDOW(window_), GTK_WIDGET(GetRoot()));
  }

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateCapturePannel() {
    CapturePannelFactory factory;
    capture_pannel_ =
        static_cast<FileSaverDropDownButtonPair *>(factory.CreateWidget());
    capture_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), capture_pannel_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateGifPannel() {
    GifPannelFactory factory;
    gif_pannel_ =
        static_cast<FileSaverDSpinButtonPair *>(factory.CreateWidget());
    gif_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), gif_pannel_->GetRoot(), 0, 2, 1, 1);
  }

  void InitCaptureButton() {
    capture_button_ = gtk_button_new_with_label("Create Capture");
    g_signal_connect(capture_button_, "clicked", G_CALLBACK(CreateCapture),
                     this);
    gtk_grid_attach(GTK_GRID(grid_), capture_button_, 0, 1, 1, 1);
  }

  void InitGifButton() {
    gif_button_ = gtk_button_new_with_label("Create Gif");
    g_signal_connect(gif_button_, "clicked", G_CALLBACK(CreateGif), this);
    gtk_grid_attach(GTK_GRID(grid_), gif_button_, 0, 3, 1, 1);
  }

  static void CreateCapture(GtkWidget *button_, s21::MediaPannel *self) {
    std::string file_name = self->capture_pannel_->GetFileName();
    if (file_name != "") {
      int extension = self->capture_pannel_->GetExtension();
      std::string ext_string =
          ((extension == 2) ? "bmp" : ((extension == 1) ? "jpg" : "png"));
      size_t width = gtk_widget_get_width(self->main_window_);
      size_t height = gtk_widget_get_height(self->main_window_);
      file_name = file_name + "." + ext_string;
      self->controller_->SavePicture(width, height, file_name.data(),
                                     ext_string.data());
      // gtk_window_destroy(GTK_WINDOW(self->window_));
    }
    // TODO close window  gtk_window_destroy
  }

  static void CreateGif(GtkWidget *button, s21::MediaPannel *self) {
    // TODO
  }
};

class ProjectionPannel : public Widget {
 public:
  ProjectionPannel() {
    InitGrid();
    CreateDropDownButtonPannel();
    s21::Widget::SetName("_PROJECTION_PANNEL_");
  }

  ~ProjectionPannel() { delete projection_; };

  void BuildWidget() {
    // CreateFileNamePannel();
    // CreateVertexInfoPannel();
    // CreateEdgesInfoPannel();
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override { SendSignal(); }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  int GetValue() { return projection_->GetValue(); }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelDropDownButtonPair *projection_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateDropDownButtonPannel() {
    const char *name = "Projection";
    const char *types[3] = {"PARALEL", "CENTRAL", nullptr};
    projection_ = new s21::LabelDropDownButtonPair(name, types);
    projection_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), projection_->GetRoot(), 0, 0, 1, 1);
  }
};

class AreaColorPannel : public Widget {
 public:
  AreaColorPannel(s21::Data *data) : data_(data) {
    InitGrid();
    s21::Widget::SetName("_AREA_PANNEL_");
  }

  ~AreaColorPannel() { delete color_; }

  void BuildWidget() { CreateColorPannel(); }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void Update() { data_->SetAreaColor(color_->GetColor()); }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelColorButtonPair *color_ = nullptr;
  s21::Data *data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateColorPannel() {
    s21::AreaColorFactory factory;
    color_ = static_cast<s21::LabelColorButtonPair *>(factory.CreateWidget());
    color_->SetValue(*(data_->GetAreaColor()));
    color_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
  }
};

}  // namespace s21

#endif
