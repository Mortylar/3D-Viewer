#ifndef SRC_VIEW_WIDGET_COMBO_WIDGET_H_
#define SRC_VIEW_WIDGET_COMBO_WIDGET_H_

#include <gtk/gtk.h>

#include "data/data.h"
#include "factory.h"
#include "widget.h"

namespace s21 {
class AffinePannel : public Widget {
 public:
  AffinePannel(s21::AffineData* data) : data_(data) {
    InitGrid();
    s21::Widget::SetName("_AFFINE_PANNEL_");
  }

  void BuildWidget() {
    CreateTranslationPannel();
    CreateRotationPannel();
    CreateScalingPannel();
	InitCommonScalingButton();
    SetMother(this);
  }

  ~AffinePannel() {
    RemoveTranslationPannel();
    RemoveRotationPannel();
    RemoveScalingPannel();
  };

  void CollectData() {
    CollectTranslation();
    CollectRotation();
    CollectScaling();
  }

  void SetMother(s21::Widget* mother) override { mother_ = mother; }

  void CatchSignal() override {  // TODO
    CollectData();
    if (mother_) SendSignal();
  }

  void SendSignal() override {
    mother_->CatchSignal();
  }

  s21::AffineData* GetData() { return data_; }

 private:
  GtkWidget* grid_ = nullptr;
  s21::Widget* mother_ = nullptr;
  s21::DSliderPannel* translation_pannel_ = nullptr;
  s21::DSliderPannel* rotation_pannel_ = nullptr;
  s21::DSliderPannel* scaling_pannel_ = nullptr;
  s21::Label* label_ = nullptr;
  GtkWidget* scale_button_ = nullptr;
  GtkAdjustment* adjustment_ = nullptr;
  GtkWidget* common_button_grid_ = nullptr;
  GtkWidget* common_button_frame_ = nullptr;

  s21::AffineData* data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void InitCommonScalingButton() {
    label_ = new s21::Label("ALL_AXIS");

	adjustment_ = gtk_adjustment_new(0.0, -1.0, 1.0, 0.01, 12, 0);
	scale_button_ = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment_);
	g_signal_connect(adjustment_, "value_changed", G_CALLBACK(CommonScalingChanged), this);
    common_button_grid_ = gtk_grid_new();
	common_button_frame_ = gtk_frame_new(nullptr);
	gtk_frame_set_child(GTK_FRAME(common_button_frame_), common_button_grid_);

	gtk_grid_attach(GTK_GRID(common_button_grid_), label_->GetRoot(), 0,0,1,1); 
	gtk_grid_attach(GTK_GRID(common_button_grid_), scale_button_, 1,0,3,1);
	gtk_grid_attach(GTK_GRID(grid_), common_button_frame_, 0,10,1,1);
	gtk_grid_set_column_homogeneous(GTK_GRID(common_button_grid_), true);
  }

  static void CommonScalingChanged(GtkAdjustment* adjustment, s21::AffinePannel* self) {
    float value = gtk_adjustment_get_value(GTK_ADJUSTMENT(self->adjustment_));
    self->scaling_pannel_->SetValue(value);
    
  }

  void CollectTranslation() {
    std::vector<float*> translation_data = translation_pannel_->GetData();
    data_->SetTranslation(*translation_data[0], *translation_data[1],
                          *translation_data[2]);
  }

  void CollectRotation() {
    std::vector<float*> rotation_data = rotation_pannel_->GetData();
    data_->SetRotation(*rotation_data[0], *rotation_data[1], *rotation_data[2]);
  }

  void CollectScaling() {
    std::vector<float*> scaling_data = scaling_pannel_->GetData();
    double scaling_vector[scaling_data.size()] = {0.0, 0.0, 0.0};
    const int k_scaling_factor = 5;
	for (size_t i = 0; i < scaling_data.size(); ++i) {
      if (*scaling_data[i] >= 0.0) {
       // scaling_vector[i] = 1.0 / (1.0 - *scaling_data[i]);
	   scaling_vector[i] = 1.0 + *scaling_data[i] * k_scaling_factor;
      } else {
       // scaling_vector[i] = 1.0 + *scaling_data[i];
	   scaling_vector[i] = 1.0 / (1.0 + -*scaling_data[i] * k_scaling_factor);
      }
    }
    data_->SetScaling(scaling_vector[0], scaling_vector[1], scaling_vector[2]);
  }

  void CreateTranslationPannel() {
    s21::TranslationPannelFactory factory;
    translation_pannel_ =
        static_cast<s21::DSliderPannel*>(factory.CreateWidget());
    translation_pannel_->SetValue(0, data_->GetTranslation()[0]);
    translation_pannel_->SetValue(1, data_->GetTranslation()[1]);
    translation_pannel_->SetValue(2, data_->GetTranslation()[2]);
    translation_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), translation_pannel_->GetRoot(), 0, 0, 1,
                    3);
    // gtk_widget_set_hexpand(translation_pannel_->GetRoot(), true);
    // gtk_widget_set_vexpand(translation_pannel_->GetRoot(), true);
  }

  void CreateRotationPannel() {
    s21::RotationPannelFactory factory;
    rotation_pannel_ = static_cast<s21::DSliderPannel*>(factory.CreateWidget());
    rotation_pannel_->SetValue(0, data_->GetRotation()[0]);
    rotation_pannel_->SetValue(1, data_->GetRotation()[1]);
    rotation_pannel_->SetValue(2, data_->GetRotation()[2]);
    rotation_pannel_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), rotation_pannel_->GetRoot(), 0, 4, 1, 3);
  }

  void CreateScalingPannel() {
    s21::ScalingPannelFactory factory;
    scaling_pannel_ = static_cast<s21::DSliderPannel*>(factory.CreateWidget());
	//TODO anti Scaling function
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
  LinePannel(s21::FormatData* data)
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

  void SetMother(s21::Widget* mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

 private:
  GtkWidget* grid_ = nullptr;
  s21::Widget* mother_ = nullptr;
  s21::LabelDropDownButtonPair* type_ = nullptr;
  s21::LabelColorButtonPair* color_ = nullptr;
  s21::LabelDSpinButtonPair* size_ = nullptr;
  s21::FormatData* data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateSizePannel() {
    s21::LineSizeFactory factory;
    size_ = static_cast<s21::LabelDSpinButtonPair*>(factory.CreateWidget());
    size_->SetValue(data_->GetSize());
    size_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateColorPannel() {
    s21::LineColorFactory factory;
    color_ = static_cast<s21::LabelColorButtonPair*>(factory.CreateWidget());
    color_->SetValue(*(data_->GetColor()));
    color_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
  }

  void CreateTypePannel() {
    s21::LineTypeFactory factory;
    type_ = static_cast<s21::LabelDropDownButtonPair*>(factory.CreateWidget());
    type_->SetValue(data_->GetType());
    type_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0, 2, 1, 1);
  }

  void Update() {
    data_->SetType(type_->GetValue());
    data_->SetColor(color_->GetColor());
    data_->SetSize(size_->GetValue());
  }
};

enum class PointType {
  k_ErrorType = -1,
  k_NoPointType = 0,
  k_RoundPointType,
  k_SquarePointType
};

class PointPannel : public Widget {
 public:
  PointPannel(s21::FormatData* data) : data_(data) {
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

  void SetMother(s21::Widget* mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

 private:
  GtkWidget* grid_ = nullptr;
  s21::Widget* mother_ = nullptr;
  s21::LabelDropDownButtonPair* type_ = nullptr;
  s21::LabelColorButtonPair* color_ = nullptr;
  s21::LabelDSpinButtonPair* size_ = nullptr;
  s21::FormatData* data_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateSizePannel() {
    s21::PointSizeFactory factory;
    size_ = static_cast<s21::LabelDSpinButtonPair*>(factory.CreateWidget());
    size_->SetValue(data_->GetSize());
    size_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateColorPannel() {
    s21::PointColorFactory factory;
    color_ = static_cast<s21::LabelColorButtonPair*>(factory.CreateWidget());
    color_->SetValue(*(data_->GetColor()));
    color_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0, 1, 1, 1);
  }

  void CreateTypePannel() {
    s21::PointTypeFactory factory;
    type_ = static_cast<s21::LabelDropDownButtonPair*>(factory.CreateWidget());
    type_->SetValue(data_->GetType());
    type_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0, 2, 1, 1);
  }

  void Update() {
    data_->SetType(type_->GetValue());
    data_->SetColor(color_->GetColor());
    data_->SetSize(size_->GetValue());
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

  void SetMother(s21::Widget* mother) override { mother_ = mother; }

  void CatchSignal() override { SendSignal(); }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

 private:
  GtkWidget* grid_ = nullptr;
  s21::Widget* mother_ = nullptr;
  s21::LabelPair* file_name_ = nullptr;
  s21::LabelPair* vertex_count_ = nullptr;
  s21::LabelPair* edges_count_ = nullptr;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }

  void CreateFileNamePannel() {
    s21::FileNamePannelFactory factory;
    file_name_ = static_cast<s21::LabelPair*>(factory.CreateWidget());
    file_name_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), file_name_->GetRoot(), 0, 0, 1, 1);
  }

  void CreateVertexInfoPannel() {
    s21::VertexInfoPannelFactory factory;
    vertex_count_ = static_cast<s21::LabelPair*>(factory.CreateWidget());
    vertex_count_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), vertex_count_->GetRoot(), 0, 1, 1, 1);
  }

  void CreateEdgesInfoPannel() {
    s21::EdgesInfoPannelFactory factory;
    edges_count_ = static_cast<s21::LabelPair*>(factory.CreateWidget());
    edges_count_->SetMother(this);
    gtk_grid_attach(GTK_GRID(grid_), edges_count_->GetRoot(), 0, 2, 1, 1);
  }
};
}  // namespace s21

#endif
