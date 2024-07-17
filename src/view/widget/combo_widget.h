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

  void BuildWidget();

  ~AffinePannel() {
    RemoveTranslationPannel();
    RemoveRotationPannel();
    RemoveScalingPannel();
  };

  void Update() { CollectData(); }

  void CollectData();

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
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

  void InitGrid();

  void InitResetButton();

  static void Reset(GtkWidget *button, s21::AffinePannel *self) {
    self->translation_pannel_->SetValue(0);
    self->rotation_pannel_->SetValue(0);
    self->scaling_pannel_->SetValue(0);
    gtk_adjustment_set_value(GTK_ADJUSTMENT(self->adjustment_), 0);
  }

  void InitCommonScalingButton();

  static void CommonScalingChanged(GtkAdjustment *adjustment,
                                   s21::AffinePannel *self) {
    float value = gtk_adjustment_get_value(GTK_ADJUSTMENT(self->adjustment_));
    self->scaling_pannel_->SetValue(value);
  }

  void CollectTranslation();
  void CollectRotation();
  void CollectScaling();
  void CreateTranslationPannel();
  void CreateRotationPannel();
  void CreateScalingPannel();

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
  LinePannel(s21::FormatData *data) : data_(data) {
    InitGrid();
    s21::Widget::SetName("_LINE_PANNEL_");
  }

  ~LinePannel() {
    delete type_;
    delete color_;
    delete size_;
  }

  void BuildWidget();

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void Update();

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelDropDownButtonPair *type_ = nullptr;
  s21::LabelColorButtonPair *color_ = nullptr;
  s21::LabelDSpinButtonPair *size_ = nullptr;
  s21::FormatData *data_ = nullptr;

  void InitGrid();
  void CreateSizePannel();
  void CreateColorPannel();
  void CreateTypePannel();
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

  void BuildWidget();

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
    Update();
    SendSignal();
  }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  void Update();

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelDropDownButtonPair *type_ = nullptr;
  s21::LabelColorButtonPair *color_ = nullptr;
  s21::LabelDSpinButtonPair *size_ = nullptr;
  s21::FormatData *data_ = nullptr;

  void InitGrid();
  void CreateSizePannel();
  void CreateColorPannel();
  void CreateTypePannel();
};

class InfoPannel : public Widget {
 public:
  InfoPannel() {
    InitGrid();
    s21::Widget::SetName("_INFORMATION_PANNEL_");
  }

  ~InfoPannel(){};

  void BuildWidget();

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

  void InitGrid();
  void CreateFileNamePannel();
  void CreateVertexInfoPannel();
  void CreateEdgesInfoPannel();
};

class MediaPannel : public Widget {
 public:
  MediaPannel(GtkWidget *window, s21::Controller *controller)
      : main_window_(window), controller_(controller) {
    InitGrid();
  };

  ~MediaPannel(){};

  void BuildWidget();

  GtkWidget *GetWindow() { return window_; }

  void SetMother(s21::Widget *mother) override { mother_ = mother; };

  void CatchSignal() override{};
  void SendSignal() override{};

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

  void InitWindow();
  void InitGrid();
  void CreateCapturePannel();
  void CreateGifPannel();
  void InitCaptureButton();
  void InitGifButton();

  static void CreateCapture(GtkWidget *button_, s21::MediaPannel *self) {
    std::string file_name = self->capture_pannel_->GetFileName();
    if (file_name != "") {
      int extension = self->capture_pannel_->GetExtension();
      std::string ext_string =
          ((extension == 2) ? "bmp" : ((extension == 1) ? "jpg" : "png"));
      size_t width = gtk_widget_get_width(self->main_window_);
      size_t height = gtk_widget_get_height(self->main_window_);
      file_name = file_name + "." + ext_string;
    }
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

  void BuildWidget();

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override { SendSignal(); }

  void SendSignal() override {
    if (mother_) mother_->CatchSignal();
  }

  int GetValue() { return projection_->GetValue(); }
  void SetValue(int value) { projection_->SetValue(value); }

 private:
  GtkWidget *grid_ = nullptr;
  s21::Widget *mother_ = nullptr;
  s21::LabelDropDownButtonPair *projection_ = nullptr;

  void InitGrid();

  void CreateDropDownButtonPannel();
};

class AreaColorPannel : public Widget {
 public:
  AreaColorPannel(s21::Data *data) : data_(data) {
    InitGrid();
    s21::Widget::SetName("_AREA_PANNEL_");
  }

  ~AreaColorPannel() { delete color_; }

  void BuildWidget();

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

  void InitGrid();
  void CreateColorPannel();
};

}  // namespace s21

#endif
