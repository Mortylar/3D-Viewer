#ifndef SRC_VIEW_WIDGET_AFFINE_PANNEL_H_
#define SRC_VIEW_WIDGET_AFFINE_PANNEL_H_

#include <gtk/gtk.h>

#include "widget.h"
#include "factory.h"
#include "affine_data.h"

namespace s21 {
class AffinePannel: public Widget {
  public:
    AffinePannel(){
      InitGrid();
      s21::Widget::SetName("__AFFINE_PANNEL__");
    }

    void BuildWidget() {
      CreateTranslationPannel();
      CreateRotationPannel();
      CreateScalingPannel();
    }

    ~AffinePannel(){};

  private:
    GtkWidget* grid_ = nullptr;
    s21::DSliderPannel* translation_pannel_ = nullptr;
    s21::DSliderPannel* rotation_pannel_ = nullptr;
    s21::DSliderPannel* scaling_pannel_ = nullptr;

    void InitGrid() {
      grid_ = gtk_grid_new();
      gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    }

    void CreateTranslationPannel() {
      s21::TranslationPannelFactory factory;
      translation_pannel_ = static_cast<s21::DSliderPannel*>(factory.CreateWidget());
      gtk_grid_attach(GTK_GRID(grid_), translation_pannel_->GetRoot(), 0,0,1,1);
    }

    void CreateRotationPannel() {
      s21::RotationPannelFactory factory;
      rotation_pannel_ = static_cast<s21::DSliderPannel*>(factory.CreateWidget());
      gtk_grid_attach(GTK_GRID(grid_), rotation_pannel_->GetRoot(), 0,1,1,1);
    }

    void CreateScalingPannel() {
      s21::ScalingPannelFactory factory;
      scaling_pannel_ = static_cast<s21::DSliderPannel*>(factory.CreateWidget());
      gtk_grid_attach(GTK_GRID(grid_), scaling_pannel_->GetRoot(), 0,2,1,1);
    }


};

}


#endif
