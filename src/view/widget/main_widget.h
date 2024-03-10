#ifndef SRC_VIEW_WIDGET_MAIN_WIDGET_H_
#define SRC_VIEW_WIDGET_MAIN_WIDGET_H_

#include "widget.h"
#include "pair_widget.h"
#include "pannel.h"
#include "combo_widget.h"
#include "drawing_area.h"
#include "../../controller/controller.h"

#include "data/data.h"

#include <iostream> //TODO remove

namespace s21 {
class MainWidget: public Widget {
 public:
  MainWidget(Data* data, s21::Controller* controller):data_(data), controller_(controller) {
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
   area_->CatchSignal();
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
  s21::Controller* controller_ = nullptr;

  GtkWidget* start_button_ = nullptr;
  GtkWidget* start_button_frame_ = nullptr;
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
    gtk_grid_attach(GTK_GRID(grid_), file_->GetRoot(), 0,0,9,1);
    gtk_grid_attach(GTK_GRID(grid_), start_button_frame_, 9,0,1,1);
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
    start_button_ = gtk_button_new_with_label("Load File");
    start_button_frame_ = gtk_frame_new(nullptr);
    gtk_frame_set_child(GTK_FRAME(start_button_frame_), start_button_);
    g_signal_connect(start_button_, "clicked", G_CALLBACK(LoadFile), this); 
  }

  void CreateDrawingArea() {
    area_ = new s21::DrawingArea(data_, controller_);
    area_->SetMother(this);
  }

  static void LoadFile(GtkWidget* button, s21::MainWidget* self) {
		const char* file_name = self->file_->GetValue();
		if (file_name) {
		  self->data_->SetFileName(file_name);
		  self->controller_->ReadFile(file_name);
      self->area_->SetBuffer();
		  self->area_->CatchSignal();
		}
  }



};
}

#endif

