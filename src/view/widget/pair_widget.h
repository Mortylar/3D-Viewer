#ifndef SRC_VIEW_PAIR_WIDGET_H_
#define SRC_VIEW_PAIR_WIDGET_H_

#include <gtk/gtk.h>

#include "widget.h"

namespace s21 {
class PairWidget : public Widget {
 public:
  PairWidget() { InitGrid(); };

  virtual ~PairWidget(){};

  virtual GtkWidget *GetGrid() { return grid_; }

 private:
  GtkWidget *grid_;

  void InitGrid() {
    grid_ = gtk_grid_new();
    gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);
  }
};

class LabelPair : public PairWidget {
 public:
  LabelPair() { InitLabels(); };

  ~LabelPair() {
    delete first_;
    delete second_;
  };

  void SetName(const char *name) override { first_->SetName(name); }

  const char *GetName() override { return first_->GetValue(); }

  void SetValue(const char *value) { second_->SetValue(value); }

  const char *GetValue() { return second_->GetValue(); }

  void SetMother(s21::Widget *mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void CatchSignal() override {
    g_print(
        "\nWarning: s21::LabelPair::CatchSignal() has no implementation!\n");
  }

  void SendSignal() override {
    g_print("\nWarning: s21::LabelPair::SendSignal() has no implementation!\n");
  }

 private:
  Label *first_ = nullptr;
  Label *second_ = nullptr;

  void InitLabels() {
    first_ = new Label();
    second_ = new Label();
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }
};

class LabelDSpinButtonPair : public PairWidget {
 public:
  LabelDSpinButtonPair(const char *name = "") {
    InitLabel(name);
    InitDSpinButton();
  };

  LabelDSpinButtonPair(const char *name, GtkAdjustment *adjustment) {
    InitLabel(name);
    InitDSpinButton(adjustment);
  }

  ~LabelDSpinButtonPair() {
    delete first_;
    delete second_;
  };

  void SetName(const char *name) override { first_->SetName(name); }

  const char *GetName() override { return first_->GetValue(); }

  void SetValue(const float value) { second_->SetValue(value); }

  float GetValue() { return second_->GetValue(); }

  float *GetData() { return second_->GetData(); }

  void SetMother(s21::Widget *mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void CatchSignal() override {}

  void SendSignal() override {}

 private:
  Label *first_ = nullptr;
  DSpinButton *second_ = nullptr;

  void InitLabel(const char *name = "") {
    first_ = new Label(name);
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
  }

  void InitDSpinButton() {
    second_ = new DSpinButton();
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }

  void InitDSpinButton(GtkAdjustment *adjustment) {
    second_ = new DSpinButton(adjustment);
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }
};

class LabelDSliderPair : public PairWidget {
 public:
  LabelDSliderPair() {
    InitLabel();
    InitSlider();
  }

  explicit LabelDSliderPair(GtkAdjustment *adjustment) {
    InitLabel();
    InitSlider(adjustment);
  }

  ~LabelDSliderPair() {
    delete first_;
    delete second_;
  }

  void SetName(const char *name) override { first_->SetName(name); }

  const char *GetName() override { return first_->GetValue(); }

  void SetValue(const float value) { second_->SetValue(value); }

  float GetValue() { return second_->GetValue(); }

  float *GetData() { return second_->GetData(); }

  void SetMother(s21::Widget *mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void CatchSignal() override {
    g_print(
        "\nWarning: s21::LabelDSliderPair::CatchSignal() has no "
        "implementation!\n");
  }

  void SendSignal() override {
    g_print(
        "\nWarning: s21::LabelDSliderPair::SendSignal() has no "
        "implementation!\n");
  }

 private:
  Label *first_ = nullptr;
  DSlider *second_ = nullptr;

  void InitLabel() {
    first_ = new Label();
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
  }

  void InitSlider() {
    second_ = new DSlider();
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 3, 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(GetGrid()), true);
  }

  void InitSlider(GtkAdjustment *adjustment) {
    second_ = new DSlider(adjustment);
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 3, 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(GetGrid()), true);
  }
};

class LabelColorButtonPair : public PairWidget {
 public:
  LabelColorButtonPair() {
    InitLabel();
    InitColorButton();
  };

  explicit LabelColorButtonPair(const char *name) {
    InitLabel(name);
    InitColorButton();
  };

  ~LabelColorButtonPair(){};

  void SetName(const char *name) override { first_->SetName(name); }

  const char *GetName() override { return first_->GetName(); }

  void SetValue(const char *value) { second_->SetName(value); }

  void SetValue(GdkRGBA color) { second_->SetValue(color); }

  void SetMother(s21::Widget *mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void SendSignal() override {}
  void CatchSignal() override {}

  GdkRGBA GetColor() { return *(second_->GetColor()); }

 private:
  Label *first_ = nullptr;
  ColorButton *second_ = nullptr;

  void InitLabel(const char *name = "") {
    first_ = new Label(name);
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
  }

  void InitColorButton() {
    second_ = new ColorButton();
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }
};

class LabelDropDownButtonPair : public PairWidget {
 public:
  LabelDropDownButtonPair(const char *name = "",
                          const char *const *strings = nullptr) {
    InitLabel(name);
    InitDropDownButton(strings);
  }

  LabelDropDownButtonPair(const char *name = "", GListModel *model = nullptr,
                          GtkExpression *expression = nullptr) {
    InitLabel(name);
    InitDropDownButton(model, expression);
  }

  ~LabelDropDownButtonPair() {
    delete first_;
    delete second_;
  }

  void SetName(const char *name) override { first_->SetName(name); }

  const char *GetName() override { return first_->GetName(); }

  void SetValue(int value) { second_->SetValue(value); }

  int GetValue() { return second_->GetValue(); }

  void SetMother(s21::Widget *mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void CatchSignal() override {};
  void SendSignal() override {};

 private:
  Label *first_ = nullptr;
  DropDownButton *second_ = nullptr;

  void InitLabel(const char *name = "") {
    first_ = new Label(name);
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
  }

  void InitDropDownButton(const char *const *strings) {
    second_ = new DropDownButton(strings);
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }

  void InitDropDownButton(GListModel *model, GtkExpression *expression) {
    second_ = new DropDownButton(model, expression);
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }
};

class FileSaverDropDownButtonPair : public PairWidget {
 public:
  explicit FileSaverDropDownButtonPair(const char *const *strings) {
    InitFileSaver();
    InitDropDownButton(strings);
  }

  ~FileSaverDropDownButtonPair() {
    delete file_;
    delete drop_down_;
  }

  void SetName(const char *name) override { s21::Widget::SetName(name); }
  const char *GetName() override { return s21::Widget::GetName(); }

  const char *GetFileName() { return file_->GetValue(); }

  void SetMother(s21::Widget *mother) override {
    file_->SetMother(mother);
    drop_down_->SetMother(mother);
  }

  void CatchSignal() override {};
  void SendSignal() override {};

 private:
  FileSaver *file_ = nullptr;
  DropDownButton *drop_down_ = nullptr;

  void InitFileSaver() {
    file_ = new s21::FileSaver();
    gtk_grid_attach(GTK_GRID(GetGrid()), file_->GetRoot(), 0, 0, 1, 1);
  }

  void InitDropDownButton(const char *const *strings) {
    drop_down_ = new s21::DropDownButton(strings);
    gtk_grid_attach(GTK_GRID(GetGrid()), drop_down_->GetRoot(), 1, 0, 1, 1);
  }
};

class FileSaverDSpinButtonPair : public PairWidget {
 public:
  FileSaverDSpinButtonPair() {
    InitFileSaver();
    InitDSpinButton();
  };

  explicit FileSaverDSpinButtonPair(GtkAdjustment *adjustment) {
    InitFileSaver();
    InitDSpinButton(adjustment);
  }

  ~FileSaverDSpinButtonPair() {
    delete first_;
    delete second_;
  };

  void SetName(const char *name) override { s21::Widget::SetName(name); }

  const char *GetName() override { return s21::Widget::GetName(); }

  void SetValue(const float value) { second_->SetValue(value); }

  float GetValue() { return second_->GetValue(); }

  float *GetData() { return second_->GetData(); }

  void SetMother(s21::Widget *mother) override {
    first_->SetMother(mother);
    second_->SetMother(mother);
  }

  void CatchSignal() override {}

  void SendSignal() override {}

  const char *GetFileName() { return first_->GetFileName(); }

 private:
  FileSaver *first_ = nullptr;
  DSpinButton *second_ = nullptr;

  void InitFileSaver() {
    first_ = new FileSaver();
    gtk_grid_attach(GTK_GRID(GetGrid()), first_->GetRoot(), 0, 0, 1, 1);
  }

  void InitDSpinButton() {
    second_ = new DSpinButton();
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }

  void InitDSpinButton(GtkAdjustment *adjustment) {
    second_ = new DSpinButton(adjustment);
    gtk_grid_attach(GTK_GRID(GetGrid()), second_->GetRoot(), 1, 0, 1, 1);
  }
};

}  // namespace s21

#endif
