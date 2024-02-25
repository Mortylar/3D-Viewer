#ifndef SRC_VIEW_WIDGET_MAIN_WIDGET_H_
#define SRC_VIEW_WIDGET_MAIN_WIDGET_H_

#include "widget.h"
#include "pair_widget.h"
#include "pannel.h"
#include "combo_widget.h"
#include "drawing_area.h"

#include "data/data.h"


namespace s21 {
class MainWidget: public Widget {
 public:
  MainWidget(Data* data):data_(data) {
    InitGrid();
  };

  ~MainWidget(){};

  void SetName(const char* name) override {
    s21::Widget::SetName(name);
  }

  const char* GetName() override {
    return s21::Widget::GetName();
  }

 void SetMother(s21::Widget* mother) override {
 }

 void CatchSignal() override {
 }

 void SendSignal() override {
 }



  void BuildWidget() {
    CreatePannel();
	GridPlacement();
  }

  void RemoveWidget() {
    RemovePannel();
  }

 private:
  s21::Data* data_ = nullptr;
  GtkWidget* grid_ = nullptr;

  s21::FileChooser* file_ = nullptr;
  s21::AffinePannel* affine_pannel_ = nullptr;
  s21::InfoPannel* info_pannel_ = nullptr;
  s21::LinePannel* line_pannel_ = nullptr;
  s21::PointPannel* point_pannel_ = nullptr;

  s21::DrawingArea* area_ = nullptr;


  void CreatePannel() {
    CreateAffinePannel();
	CreateInfoPannel();
	CreateLinePannel();
	CreatePointPannel();
	CreateDrawingArea();
	CreateFileChooser();
  }

  void InitGrid() {
    grid_ = gtk_grid_new();
	gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
	//gtk_grid_set_row_homogeneous(GTK_GRID(grid_), true);
	//gtk_grid_set_column_homogeneous(GTK_GRID(grid_), true);

  }

  void GridPlacement() {
    gtk_grid_attach(GTK_GRID(grid_), file_->GetRoot(), 0,0,10,1);
    gtk_grid_attach(GTK_GRID(grid_), affine_pannel_->GetRoot(), 0,1,5,9);

    gtk_grid_attach(GTK_GRID(grid_), info_pannel_->GetRoot(), 5,1,5,3);
    gtk_grid_attach(GTK_GRID(grid_), line_pannel_->GetRoot(), 5,4,5,3);
    gtk_grid_attach(GTK_GRID(grid_), point_pannel_->GetRoot(), 5,7,5,3);

    gtk_grid_attach(GTK_GRID(grid_), area_->GetRoot(), 10,0,10,10);
  }

  void RemovePannel() {
    delete affine_pannel_;
    delete info_pannel_;
    delete point_pannel_;
    delete line_pannel_;
    delete area_;
	delete file_;
  }

  void CreateAffinePannel() { 
    affine_pannel_ = new s21::AffinePannel(data_->GetAffineData());
	affine_pannel_->BuildWidget();
	affine_pannel_->SetMother(this);
  }

  void CreateInfoPannel() { 
    info_pannel_ = new s21::InfoPannel();
	info_pannel_->BuildWidget();
	info_pannel_->SetMother(this);
  }

  void CreateLinePannel() { 
    line_pannel_ = new s21::LinePannel(data_->GetLineData());
	line_pannel_->BuildWidget();
	line_pannel_->SetMother(this);
  }

  void CreatePointPannel() { 
    point_pannel_ = new s21::PointPannel(data_->GetPointData());
	point_pannel_->BuildWidget();
	point_pannel_->SetMother(this);
  }

  void CreateFileChooser() {
    file_ = new s21::FileChooser();
  }

  void CreateDrawingArea() {
    area_ = new s21::DrawingArea(data_);
	area_->SetMother(this);
  }

};
}

#endif
