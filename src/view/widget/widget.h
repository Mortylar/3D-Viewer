#ifndef SRC_VIEW_WIDGET_WIDGET_H_
#define SRC_VIEW_WIDGET_WIDGET_H_

#include <gtk/gtk.h>

namespace s21 {
class Widget {
  public:
    Widget() {
      frame_ = gtk_frame_new(nullptr);
    }

    virtual ~Widget(){};

    virtual GtkWidget* GetFrame() {//TODO virtual
      return frame_;
    }

    virtual GtkWidget* GetRoot() { //TODO virtual
      return frame_;
    }

    virtual void SetName(const char* name) { //TODO virual
      gtk_frame_set_label(GTK_FRAME(frame_), name);
      gtk_frame_set_label_align(GTK_FRAME(frame_), 0.5);
    }

    virtual void SetMother(s21::Widget* mother)=0;
    virtual void CatchSignal()=0;
    virtual void SendSignal()=0;

  private:
    GtkWidget* frame_ = nullptr;
};


class Label: public Widget {
  public:
    Label() {
      InitLabel();
    }

    Label(const char* text) {
      InitLabel();
      SetName(text);
    }

    ~Label(){};

    void SetName(const char* name) override { //TODO override
      gtk_label_set_text(GTK_LABEL(label_), name);
    }

    const char* GetValue() {
      return (gtk_label_get_text(GTK_LABEL(label_)));
    };

    void SetValue(const char* value) {
      gtk_label_set_text(GTK_LABEL(label_), value);
    }

	void SendSignal() override {};

	void SetMother(s21::Widget* mother) override {
	  mother_ = mother;
	}

	void CatchSignal() override {
	  g_print("\nWarning: s21::Label::CatchSignal() has no implementation!\n");
	}

  private:
    GtkWidget* label_ = nullptr;
	s21::Widget* mother_ = nullptr;
    //TODO value_;

    void InitLabel() {
      label_ = gtk_label_new(nullptr);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), label_);
    }

};

class DSpinButton: public Widget {
  public:
    DSpinButton() {
      adjustment_ = gtk_adjustment_new(0.0, -1e100, 1e100, 1, 0, 0);
      InitSpinButton();
    }

    DSpinButton(GtkAdjustment* adjustment): adjustment_(adjustment) {
      InitSpinButton();
    }

    ~DSpinButton(){};

    double GetValue() {
      return value_;
    }

    double* GetData() {
      return &value_;
    }

    void SetValue(const double value) {
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_), value);
    };

	void SetMother(s21::Widget* mother) override {
	  mother_ = mother;
	}

	void SendSignal() override {
	  if(mother_) mother_->CatchSignal();
	}

	void CatchSignal() override {
	  g_print("\nWarning: s21::DSpinButton::CatchSignal() has no implementation!\n");
	}

  private:
    GtkWidget* spin_button_ = nullptr;
    GtkAdjustment* adjustment_ = nullptr;
	s21::Widget* mother_ = nullptr;
    double value_ = 0.0;

    DSpinButton(DSpinButton&);
    DSpinButton(DSpinButton&&);

    static void ValueReboot(GtkAdjustment* adjustment, DSpinButton* self) {
      self->value_ = gtk_adjustment_get_value(self->adjustment_);
	  self->SendSignal();
    }

    void InitSpinButton() {
      spin_button_ = gtk_spin_button_new(adjustment_, 100, 20);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), spin_button_);
      g_signal_connect(spin_button_, "value_changed", G_CALLBACK(ValueReboot), this);
    }

};

class DSlider: public Widget {
  public:
    DSlider() {
      adjustment_ = gtk_adjustment_new(0.0, -100.0, 100.0, 1, 12, 0);
      InitSlider();
    }

    DSlider(GtkAdjustment* adjustment): adjustment_(adjustment) {
      InitSlider();
    }

    ~DSlider(){};

     double GetValue() {
       return value_;
     }

    double* GetData() {
      return &value_;
    }

     void SetValue(double x) {
       gtk_adjustment_set_value(adjustment_, x);
     }

	void SetMother(s21::Widget* mother) override {
	  mother_ = mother;
	}

	void SendSignal() override {
	  if(mother_) mother_->CatchSignal();
	}

	void CatchSignal() override {
	  g_print("\nWarning: s21::DSlider::CatchSignal() has no implementation!\n");
	}

  private:
    GtkWidget* scale_button_ = nullptr;
    GtkAdjustment* adjustment_ = nullptr;
	s21::Widget* mother_ = nullptr;
	double value_ = 0.0;

    static void ValueReboot(GtkAdjustment* adjustment, DSlider* self) {
      self->value_ = gtk_adjustment_get_value(self->adjustment_);
	  self->SendSignal();
    }

    void InitSlider() {
      scale_button_ = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, adjustment_);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), scale_button_);
	  //gtk_widget_set_hexpand(scale_button_, true);
	  //gtk_widget_set_vexpand(scale_button_, true);
      g_signal_connect(adjustment_, "value_changed", G_CALLBACK(ValueReboot), this);
    }
};

class FileChooser: public Widget {
  public:
    FileChooser() {
	  InitButton();
	}

	FileChooser(const char* name) {
	  InitButton(name);
	}

	~FileChooser(){
      ClearFile();
	  g_print("\nDestr = %s\n", file_name_);
	};

	void SetMother(s21::Widget* mother) override {
	  mother_ = mother;
	}

	void SendSignal() override {
	  if(mother_) mother_->CatchSignal();
	  g_print("\nName = %s\n", file_name_);
	}

	void CatchSignal() override {
	};

	void SetName(const char* name) override {
	  gtk_button_set_label(GTK_BUTTON(button_), name);
	}

	const char* GetValue() {
	  return file_name_;
	}

  private:
    GtkWidget* button_ = nullptr;
	char* file_name_ = nullptr;
	s21::Widget* mother_ = nullptr;


	void ClearFile() {
	  if(file_name_) delete file_name_;
	  g_print("\nDelete file\n");
	}

    void InitButton(const char* name = "File_Button") {
	  button_ = gtk_button_new_with_label(name);
	  gtk_frame_set_child(GTK_FRAME(GetFrame()), button_);
	  g_signal_connect(button_, "clicked", G_CALLBACK(OpenFileDialog), this);
	}

	static void OpenFileDialog(GtkWidget* button, FileChooser* self) {
	  GtkWindow* parent = GTK_WINDOW(gtk_widget_get_root(button));
	  GtkFileDialog* dialog = gtk_file_dialog_new();

	  gtk_file_dialog_open(dialog, parent, nullptr, GetFile, (void*)self);
	  g_object_unref(dialog);
	}

	static void GetFile(GObject* source, GAsyncResult* result, void* self) {
	  GFile* file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, nullptr);
	  if (file) {
        static_cast<s21::FileChooser*>(self)->ClearFile();
	    static_cast<s21::FileChooser*>(self)->file_name_ = g_file_get_path(file);
	    static_cast<s21::FileChooser*>(self)->SendSignal();
	  }
	}

};

}


#endif

