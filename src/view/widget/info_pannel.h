#ifndef SRC_VIEW_WIDGET_INFO_PANNEL_H_
#define SRC_VIEW_WIDGET_INFO_PANNEL_H_

#include <gtk/gtk.h>

#include"widget.h"
#include "factory.h"

namespace s21 {
class InfoPannel: public Widget {
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

	void SetMother(s21::Widget* mother) {
	  mother_ = mother;
	}

	void CatchSignal() {
	  SendSignal();
	}

	void SendSignal() {
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
    }

    void CreateFileNamePannel() {
      s21::FileNamePannelFactory factory;
      file_name_ = static_cast<s21::LabelPair*>(factory.CreateWidget());
      file_name_->SetMother(this);
      gtk_grid_attach(GTK_GRID(grid_), file_name_->GetRoot(), 0,0,1,1);
    }

    void CreateVertexInfoPannel() {
      s21::VertexInfoPannelFactory factory;
      vertex_count_ = static_cast<s21::LabelPair*>(factory.CreateWidget());
      vertex_count_->SetMother(this);
      gtk_grid_attach(GTK_GRID(grid_), vertex_count_->GetRoot(), 0,1,1,1);
    }

    void CreateEdgesInfoPannel() {
      s21::EdgesInfoPannelFactory factory;
      edges_count_ = static_cast<s21::LabelPair*>(factory.CreateWidget());
      edges_count_->SetMother(this);
      gtk_grid_attach(GTK_GRID(grid_), edges_count_->GetRoot(), 0,2,1,1);
    }
};

}

#endif
