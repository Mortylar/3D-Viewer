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
	  InitData();
      s21::Widget::SetName("_AFFINE_PANNEL_");
    }

    void BuildWidget() {
      CreateTranslationPannel();
      CreateRotationPannel();
      CreateScalingPannel();
	  SetMother(this);
    }

    ~AffinePannel() {
      RemoveData();
	};

	void CollectData() {
	  CollectTranslation();
	  CollectRotation();
	  CollectScaling();
	}

	void SetMother(s21::Widget* mother) override {
	  translation_pannel_->SetMother(mother);
	  rotation_pannel_->SetMother(mother);
	  scaling_pannel_->SetMother(mother);
	}

	void CatchSignal() override { //TODO
      CollectData();
	  for(size_t i = 0; i < 3; ++i) {
	    g_print("\n%i = (%lf, %lf, %lf)\n", i, data_->GetData()[3*i], data_->GetData()[3*i+1], data_->GetData()[3*i+2]);
	  }
	  g_print("\n--------------------------------\n");
	}

	void SendSignal() override {
	  g_print("\nWarning: s21::AffinePannel::SendSignal() has no implementation!\n");
	}

  private:
    GtkWidget* grid_ = nullptr;
    s21::DSliderPannel* translation_pannel_ = nullptr;
    s21::DSliderPannel* rotation_pannel_ = nullptr;
    s21::DSliderPannel* scaling_pannel_ = nullptr;

    s21::AffineData* data_ = nullptr;

    void InitGrid() {
      grid_ = gtk_grid_new();
      gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
    }

	void InitData() {
      data_ = new s21::AffineData();
	}

	void RemoveData() {
	  delete data_;
	}

	void CollectTranslation() {
	  std::vector<double*> translation_data = translation_pannel_->GetData();
	  data_->SetTranslation(*translation_data[0], *translation_data[1], *translation_data[2]);
	}

	void CollectRotation() {
	  std::vector<double*> rotation_data = rotation_pannel_->GetData();
	  data_->SetRotation(*rotation_data[0], *rotation_data[1], *rotation_data[2]);
	}

	void CollectScaling() {
	  std::vector<double*> scaling_data = scaling_pannel_->GetData();
	  double scaling_vector[scaling_data.size()] = {0.0, 0.0, 0.0};
	  for (size_t i = 0; i < scaling_data.size(); ++i) {
        if(*scaling_data[i] >= 0.0) {
		  scaling_vector[i] = 1.0/(1.0 - *scaling_data[i]);
		} else {
		  scaling_vector[i] = 1.0 + *scaling_data[i];
		}
	  }
	  data_->SetScaling(scaling_vector[0], scaling_vector[1], scaling_vector[2]);
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
