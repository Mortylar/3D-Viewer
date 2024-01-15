#ifndef SRC_VIEW_WIDGET_FACTORY_H_
#define SRC_VIEW_WIDGET_FACTORY_H_


#include "widget.h"
#include "pair_widget.h"
#include "pannel.h"
namespace s21 {
class Factory {
  public:
    Factory(){};
    ~Factory(){};
    virtual s21::Widget* CreateWidget()=0;
};

class TranslationPannelFactory: public Factory {
  public:
    TranslationPannelFactory(){};
    ~TranslationPannelFactory(){};

    s21::Widget* CreateWidget() override {
      s21::DSliderPannel* translation_pannel = new s21::DSliderPannel{GetAdjustment(),
                                                     GetAdjustment(), GetAdjustment()};
      translation_pannel->SetName("Translation_Pannel");
      translation_pannel->SetName(0, "X_AXIS");
      translation_pannel->SetName(1, "Y_AXIS");
      translation_pannel->SetName(2, "Z_AXIS");
      return translation_pannel;
    }
  private:
    GtkAdjustment* GetAdjustment() {
      return gtk_adjustment_new(0.0, -5.0, 5.0, 0.01, 0, 0);
    }
};

class RotationPannelFactory: public Factory {
  public:
    RotationPannelFactory(){};
    ~RotationPannelFactory(){};

    s21::Widget* CreateWidget() override {
      s21::DSliderPannel* rotation_pannel = new s21::DSliderPannel{GetAdjustment(),
                                                     GetAdjustment(), GetAdjustment()};
      rotation_pannel->SetName("Rotation_Pannel");
      rotation_pannel->SetName(0, "X_AXIS");
      rotation_pannel->SetName(1, "Y_AXIS");
      rotation_pannel->SetName(2, "Z_AXIS");
      return rotation_pannel;
    }
  private:
    GtkAdjustment* GetAdjustment() {
      return gtk_adjustment_new(0.0, -1*G_PI, 1*G_PI, 0.05, 0, 0);
    }
};

class ScalingPannelFactory: public Factory {
  public:
    ScalingPannelFactory(){};
    ~ScalingPannelFactory(){};

    s21::Widget* CreateWidget() override {
      s21::DSliderPannel* scaling_pannel = new s21::DSliderPannel{GetAdjustment(),
                                                 GetAdjustment(), GetAdjustment()};
      scaling_pannel->SetName("Scaling_Pannel");
      scaling_pannel->SetName(0, "X_AXIS");
      scaling_pannel->SetName(1, "Y_AXIS");
      scaling_pannel->SetName(2, "Z_AXIS");
      return scaling_pannel;
    }
  private:
    GtkAdjustment* GetAdjustment() {
      return gtk_adjustment_new(0.0, -0.9999999999, 0.999999999999, 0.001, 0, 0);
    }
};

class FileNamePannelFactory: public Factory {
  public:
    FileNamePannelFactory(){};
    ~FileNamePannelFactory(){};

	s21::Widget* CreateWidget() override {
	  s21::LabelPair* file_name_pair = new s21::LabelPair();
	  file_name_pair->SetName("Source_File");
	  file_name_pair->SetValue("No_File");
	  return file_name_pair;
	}
};

class VertexInfoPannelFactory: public Factory {
  public:
    VertexInfoPannelFactory(){};
    ~VertexInfoPannelFactory(){};

	s21::Widget* CreateWidget() override {
	  s21::LabelPair* vertex_info_pair = new s21::LabelPair();
	  vertex_info_pair->SetName("Vertex_Count");
	  vertex_info_pair->SetValue("0");
	  return vertex_info_pair;
	}
};

class EdgesInfoPannelFactory: public Factory {
  public:
    EdgesInfoPannelFactory(){};
    ~EdgesInfoPannelFactory(){};

	s21::Widget* CreateWidget() override {
	  s21::LabelPair* edge_info_pair = new s21::LabelPair();
	  edge_info_pair->SetName("Edges_Count");
	  edge_info_pair->SetValue("0");
	  return edge_info_pair;
	}
};

}


#endif
