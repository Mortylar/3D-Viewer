#ifndef SRC_VIEW_WIDGET_LINE_PANNEL_H_
#define SRC_VIEW_WIDGET_LINE_PANNEL_H_

#include <gtk/gtk.h>

#include "widget.h"
#include "factory.h"

namespace s21 {
enum class LineType {
  k_ErrorType = -1,
  k_NoLineType = 0,
  k_SolidLineType,
  k_DottedLineType
};

class LinePannel: public Widget {
 public:
   LinePannel() {
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

   void SetMother(s21::Widget* mother) override {
     mother_ = mother;
   }

   void CatchSignal() override {
     SendSignal();
   }

   void SendSignal() override {
     if(mother_) mother_->CatchSignal();
   }


 private:
   GtkWidget* grid_ = nullptr;
   s21::Widget* mother_ = nullptr;
   s21::LabelDropDownButtonPair* type_ = nullptr;
   s21::LabelColorButtonPair* color_ = nullptr;
   s21::LabelDSpinButtonPair* size_ = nullptr;

   void InitGrid() {
     grid_ = gtk_grid_new();
	 gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
   }

   void CreateSizePannel() {
     s21::LineSizeFactory factory;
	 size_ = static_cast<s21::LabelDSpinButtonPair*>(factory.CreateWidget());
	 size_->SetMother(this);
	 gtk_grid_attach(GTK_GRID(grid_), size_->GetRoot(), 0,0,1,1);
   }

   void CreateColorPannel() {
     s21::LineColorFactory factory;
	 color_ = static_cast<s21::LabelColorButtonPair*>(factory.CreateWidget());
	 color_->SetMother(this);
	 gtk_grid_attach(GTK_GRID(grid_), color_->GetRoot(), 0,1,1,1);
   }

   void CreateTypePannel() {
     s21::LineTypeFactory factory;
	 type_ = static_cast<s21::LabelDropDownButtonPair*>(factory.CreateWidget());
	 type_->SetMother(this);
	 gtk_grid_attach(GTK_GRID(grid_), type_->GetRoot(), 0,2,1,1);
   }
};
}


#endif
