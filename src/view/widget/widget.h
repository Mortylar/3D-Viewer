#ifndef SRC_VIEW_WIDGET_WIDGET_H_
#define SRC_VIEW_WIDGET_WIDGET_H_

#include <gtk/gtk.h>

namespace s21 {
class Widget {
public:
  Widget() { frame_ = gtk_frame_new(nullptr); }

  virtual ~Widget(){};

  virtual GtkWidget *GetFrame() { // TODO virtual
    return frame_;
  }

  virtual GtkWidget *GetRoot() { // TODO virtual
    return frame_;
  }

  virtual void SetName(const char *name) { // TODO virual
    gtk_frame_set_label(GTK_FRAME(frame_), name);
    gtk_frame_set_label_align(GTK_FRAME(frame_), 0.5);
  }

  virtual const char *GetName() {
    return gtk_frame_get_label(GTK_FRAME(frame_));
  }

  virtual void SetMother(s21::Widget *mother) = 0;
  virtual void CatchSignal() = 0;
  // void CatchSignal(void* message);
  virtual void SendSignal() = 0;

private:
  GtkWidget *frame_ = nullptr;
};

class Label : public Widget {
public:
  Label() { InitLabel(); }

  Label(const char *text) {
    InitLabel();
    SetName(text);
  }

  ~Label(){};

  void SetName(const char *name) override { // TODO override
    gtk_label_set_text(GTK_LABEL(label_), name);
  }

  const char *GetValue() { return (gtk_label_get_text(GTK_LABEL(label_))); };

  void SetValue(const char *value) {
    gtk_label_set_text(GTK_LABEL(label_), value);
  }

  void SendSignal() override{};

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void CatchSignal() override {
    g_print("\nWarning: s21::Label::CatchSignal() has no implementation!\n");
  }

private:
  GtkWidget *label_ = nullptr;
  s21::Widget *mother_ = nullptr;
  // TODO value_;

  void InitLabel() {
    label_ = gtk_label_new(nullptr);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), label_);
  }
};

class DSpinButton : public Widget {
public:
  DSpinButton() {
    adjustment_ = gtk_adjustment_new(0.0, -1e100, 1e100, 1, 0, 0);
    InitSpinButton();
  }

  DSpinButton(GtkAdjustment *adjustment) : adjustment_(adjustment) {
    InitSpinButton();
  }

  ~DSpinButton(){};

  float GetValue() { return value_; }

  float *GetData() { return &value_; }

  void SetValue(const float value) {
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_), value);
  };

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override {
    g_print(
        "\nWarning: s21::DSpinButton::CatchSignal() has no implementation!\n");
  }

private:
  GtkWidget *spin_button_ = nullptr;
  GtkAdjustment *adjustment_ = nullptr;
  s21::Widget *mother_ = nullptr;
  float value_ = 0.0;

  DSpinButton(DSpinButton &);
  DSpinButton(DSpinButton &&);

  static void ValueReboot(GtkAdjustment *adjustment, DSpinButton *self) {
    self->value_ = gtk_adjustment_get_value(self->adjustment_);
    self->SendSignal();
  }

  void InitSpinButton() {
    spin_button_ = gtk_spin_button_new(adjustment_, 100, 20);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), spin_button_);
    g_signal_connect(spin_button_, "value_changed", G_CALLBACK(ValueReboot),
                     this);
  }
};

class DSlider : public Widget {
public:
  DSlider() {
    adjustment_ = gtk_adjustment_new(0.0, -100.0, 100.0, 1, 12, 0);
    InitSlider();
  }

  DSlider(GtkAdjustment *adjustment) : adjustment_(adjustment) { InitSlider(); }

  ~DSlider(){};

  float GetValue() { return value_; }

  float *GetData() { return &value_; }

  void SetValue(float x) { gtk_adjustment_set_value(adjustment_, x); }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override {
    g_print("\nWarning: s21::DSlider::CatchSignal() has no implementation!\n");
  }

private:
  GtkWidget *scale_button_ = nullptr;
  GtkAdjustment *adjustment_ = nullptr;
  s21::Widget *mother_ = nullptr;
  float value_ = 0.0;

  static void ValueReboot(GtkAdjustment *adjustment, DSlider *self) {
    self->value_ = gtk_adjustment_get_value(self->adjustment_);
    self->SendSignal();
  }

  void InitSlider() {
    scale_button_ = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment_);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), scale_button_);
    // gtk_widget_set_hexpand(scale_button_, true);
    // gtk_widget_set_vexpand(scale_button_, true);
    g_signal_connect(adjustment_, "value_changed", G_CALLBACK(ValueReboot),
                     this);
  }
};

#ifndef GTK_TYPE_FILE_DIALOG

class FileChooser : public Widget {
public:
  FileChooser() { InitButton(); }

  FileChooser(const char *name) { InitButton(name); }

  ~FileChooser() { ClearFile(); };

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override{};

  void SetName(const char *name) override {
    gtk_button_set_label(GTK_BUTTON(button_), name);
  }

  const char *GetValue() { return file_name_; }
  const char *GetFileName() { return little_file_; }

private:
  GtkWidget *button_ = nullptr;
  char *file_name_ = nullptr;
  char *little_file_ = nullptr;
  s21::Widget *mother_ = nullptr;

  void ClearFile() {
    if (file_name_)
      delete file_name_;
  }

  void InitButton(const char *name = "File_Button") {
    button_ = gtk_button_new_with_label(name);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), button_);
    g_signal_connect(button_, "clicked", G_CALLBACK(OpenFileDialog), this);
  }

  static void OpenFileDialog(GtkWidget *button, FileChooser *self) {
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(button));
    GtkFileChooserNative *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog = gtk_file_chooser_native_new("Open file", parent, action, "Load",
                                         "Cancel");

    g_signal_connect(dialog, "response", G_CALLBACK(GetFile), self);
    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
  }

  static void GetFile(GtkNativeDialog *dialog, int response, void *self) {
    GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
    if (file) {
      static_cast<s21::FileChooser *>(self)->ClearFile();
      static_cast<s21::FileChooser *>(self)->file_name_ = g_file_get_path(file);
      static_cast<s21::FileChooser *>(self)->little_file_ =
          g_file_get_basename(file);
      static_cast<s21::FileChooser *>(self)->SendSignal();
    }
  }
};


class FileSaver : public Widget {
public:
  FileSaver() { InitButton(); }

  FileSaver(const char *name) { InitButton(name); }

  ~FileSaver() { ClearFile(); };

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override{};

  void SetName(const char *name) override {
    gtk_button_set_label(GTK_BUTTON(button_), name);
  }

  const char *GetValue() { return file_name_; }
  const char *GetFileName() { return little_file_; }

private:
  GtkWidget *button_ = nullptr;
  char *file_name_ = nullptr;
  char *little_file_ = nullptr;
  s21::Widget *mother_ = nullptr;

  void ClearFile() {
    if (file_name_)
      delete file_name_;
  }

  void InitButton(const char *name = "File_Button") {
    button_ = gtk_button_new_with_label(name);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), button_);
    g_signal_connect(button_, "clicked", G_CALLBACK(OpenFileDialog), this);
  }

  static void OpenFileDialog(GtkWidget *button, FileSaver *self) {
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(button));
    GtkFileChooserNative *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    dialog = gtk_file_chooser_native_new("Open file", parent, action, "Save",
                                         "Cancel");

    g_signal_connect(dialog, "response", G_CALLBACK(GetFile), self);
    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
  }

  static void GetFile(GtkNativeDialog *dialog, int response, void *self) {
    GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
    if (file) {
      static_cast<s21::FileSaver *>(self)->ClearFile();
      static_cast<s21::FileSaver *>(self)->file_name_ = g_file_get_path(file);
      static_cast<s21::FileSaver *>(self)->little_file_ =
          g_file_get_basename(file);
      static_cast<s21::FileSaver *>(self)->SendSignal();
    }
  }
};



#else

class FileChooser : public Widget {
public:
  FileChooser() { InitButton(); }

  FileChooser(const char *name) { InitButton(name); }

  ~FileChooser() { ClearFile(); };

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal(); // TODO
  }

  void CatchSignal() override{};

  void SetName(const char *name) override {
    gtk_button_set_label(GTK_BUTTON(button_), name);
  }

  const char *GetValue() { return file_name_; }
  const char *GetFileName() { return little_file_; }

private:
  GtkWidget *button_ = nullptr;
  char *file_name_ = nullptr;
  char *little_file_ = nullptr;
  s21::Widget *mother_ = nullptr;

  void ClearFile() {
    if (file_name_)
      delete file_name_;
  }

  void InitButton(const char *name = "File_Button") {
    button_ = gtk_button_new_with_label(name);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), button_);
    g_signal_connect(button_, "clicked", G_CALLBACK(OpenFileDialog), this);
  }

  static void OpenFileDialog(GtkWidget *button, FileChooser *self) {
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(button));
    GtkFileDialog *dialog;
    // GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog = gtk_file_dialog_new(); //"Open file", parent, action, "Load",
                                    //    "Cancel");

    gtk_file_dialog_open(dialog, parent, NULL, GetFile, self);
    g_object_unref(dialog);
  }

  static void GetFile(GObject *dialog, GAsyncResult *result, void *self) {
    GFile *file =
        gtk_file_dialog_open_finish(GTK_FILE_DIALOG(dialog), result, NULL);
    if (file) {
      static_cast<s21::FileChooser *>(self)->ClearFile();
      static_cast<s21::FileChooser *>(self)->file_name_ = g_file_get_path(file);
      static_cast<s21::FileChooser *>(self)->little_file_ =
          g_file_get_basename(file);
      static_cast<s21::FileChooser *>(self)->SendSignal();
    }
  }
};


class FileSaver : public Widget {
public:
  FileSaver() { InitButton(); }

  FileSaver(const char *name) { InitButton(name); }

  ~FileSaver() { ClearFile(); };

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal(); // TODO
  }

  void CatchSignal() override{};

  void SetName(const char *name) override {
    gtk_button_set_label(GTK_BUTTON(button_), name);
  }

  const char *GetValue() { return file_name_; }
  const char *GetFileName() { return little_file_; }

private:
  GtkWidget *button_ = nullptr;
  char *file_name_ = nullptr;
  char *little_file_ = nullptr;
  s21::Widget *mother_ = nullptr;

  void ClearFile() {
    if (file_name_)
      delete file_name_;
  }

  void InitButton(const char *name = "File_Button") {
    button_ = gtk_button_new_with_label(name);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), button_);
    g_signal_connect(button_, "clicked", G_CALLBACK(OpenFileDialog), this);
  }

  static void OpenFileDialog(GtkWidget *button, FileChooser *self) {
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(button));
    GtkFileDialog *dialog;
    // GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    dialog = gtk_file_dialog_new(); //"Open file", parent, action, "Load",
                                    //    "Cancel");

    gtk_file_dialog_save(dialog, parent, NULL, GetFile, self);
    g_object_unref(dialog);
  }

  static void GetFile(GObject *dialog, GAsyncResult *result, void *self) {
    GFile *file =
        gtk_file_dialog_save_finish(GTK_FILE_DIALOG(dialog), result, NULL);
    if (file) {
      static_cast<s21::FileSaver *>(self)->ClearFile();
      static_cast<s21::FileSaver *>(self)->file_name_ = g_file_get_path(file);
      static_cast<s21::FileSaver *>(self)->little_file_ =
          g_file_get_basename(file);
      static_cast<s21::FileSaver *>(self)->SendSignal();
    }
  }
};



#endif

#if !defined GTK_TYPE_COLOR_DIALOG_BUTTON

class ColorButton : public Widget {
public:
  ColorButton() { InitColorButton(); }

  ~ColorButton(){};

  void SetName(const char *name) override {
    gtk_color_button_set_title(GTK_COLOR_BUTTON(color_button_), name);
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SetValue(GdkRGBA color) {
    color_ = color;
    gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(color_button_), &color_);
  }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override {} // TODO

  GdkRGBA *GetColor() { return &color_; }

private:
  GtkWidget *color_button_ = nullptr;
  s21::Widget *mother_ = nullptr;
  GdkRGBA color_;

  void InitColorButton() {
    color_button_ = gtk_color_button_new();
    gtk_frame_set_child(GTK_FRAME(GetRoot()), color_button_);
    g_signal_connect(color_button_, "color-set", G_CALLBACK(SetColor), this);
  }

  static void SetColor(GtkColorButton *button, s21::ColorButton *self) {
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &(self->color_));
    self->SendSignal();
  }
};

#else

class ColorButton : public Widget {
public:
  ColorButton() { InitColorButton(); }

  ~ColorButton(){};

  void SetName(const char *name) override {
    // gtk_color_button_set_title(GTK_COLOR_BUTTON(color_button_), name);
    gtk_button_set_label(GTK_BUTTON(color_button_), name);
  }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override {} // TODO

  GdkRGBA *GetColor() { return &color_; }

  void SetValue(GdkRGBA color) {
    color_ = color;
    gtk_color_dialog_button_set_rgba(GTK_COLOR_DIALOG_BUTTON(color_button_),
                                     &color_);
  }

private:
  GtkWidget *color_button_ = nullptr;
  s21::Widget *mother_ = nullptr;
  GdkRGBA color_;

  void InitColorButton() {
    color_button_ = gtk_color_dialog_button_new(gtk_color_dialog_new());
    gtk_frame_set_child(GTK_FRAME(GetRoot()), color_button_);
    g_signal_connect(color_button_, "notify::rgba", G_CALLBACK(SetColor), this);
  }

  static void SetColor(GtkColorDialogButton *button, GParamSpec *param,
                       s21::ColorButton *self) {
    self->color_ = *(gtk_color_dialog_button_get_rgba(button));
    self->SendSignal();
  }
};
#endif

class DropDownButton : public Widget {
public:
  DropDownButton(const char *const *strings) { InitDropDownButton(strings); }

  DropDownButton(GListModel *model, GtkExpression *expression) {
    InitDropDownButton(model, expression);
  }

  ~DropDownButton(){};

  void SetName(const char *name) override { s21::Widget::SetName(name); }

  const char *GetName() override { return s21::Widget::GetName(); }

  void SetMother(s21::Widget *mother) override { mother_ = mother; }

  void SendSignal() override {
    if (mother_)
      mother_->CatchSignal();
  }

  void CatchSignal() override {}

  int GetValue() {
    guint value = gtk_drop_down_get_selected(GTK_DROP_DOWN(drop_down_button_));
    return (value == GTK_INVALID_LIST_POSITION) ? (-1)
                                                : static_cast<int>(value);
  }

  void SetValue(int value) {
    gtk_drop_down_set_selected(GTK_DROP_DOWN(drop_down_button_),
                               static_cast<guint>(value));
  }

private:
  s21::Widget *mother_ = nullptr;
  GtkWidget *drop_down_button_ = nullptr;

  void InitDropDownButton(const char *const *strings) {
    drop_down_button_ = gtk_drop_down_new_from_strings(strings);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), drop_down_button_);
  }

  void InitDropDownButton(GListModel *model, GtkExpression *expression) {
    drop_down_button_ = gtk_drop_down_new(model, expression);
    gtk_frame_set_child(GTK_FRAME(GetFrame()), drop_down_button_);
  }
};

} // namespace s21

#endif
