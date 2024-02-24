#include <gtk/gtk.h>

#include <iostream>

#include "widget/widget.h"
#include "widget/pair_widget.h"
#include "widget/pannel.h"

#include "widget/factory.h"
#include "widget/combo_widget.h"
#include "widget/drawing_area.h"
#include "widget/main_widget.h"

#ifdef __APPLE__
#define APPLICATION_NONE_FLAG G_APPLICATION_DEFAULT_FLAGS
#else
#define APPLICATION_NONE_FLAG G_APPLICATION_FLAGS_NONE
#endif



 void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 900, 100);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);
  //gtk_grid_set_row_homogeneous(GTK_GRID(grid), true);
 // gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);


  s21::Data* data = new s21::Data();

  s21::MainWidget* mv = new s21::MainWidget(data);
  mv->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), mv->GetRoot(), 0,0,1,1);

  /*
  //GtkWidget* button = gtk_button_new_with_label("button");
  //gtk_grid_attach(GTK_GRID(grid), button, 0,2,1,1);
 // g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(PrintDouble), f_data);


  s21::AffinePannel* pan = new s21::AffinePannel(data->GetAffineData());
  pan->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), pan->GetRoot(), 0,1,1,4);


  s21::InfoPannel* info_pannel = new s21::InfoPannel();
  info_pannel->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), info_pannel->GetRoot(), 0,0,1,1);

  s21::LinePannel* line_pannel = new s21::LinePannel(data->GetLineData());
  line_pannel->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), line_pannel->GetRoot(), 5,0,1,1);


  s21::PointPannel* point_pannel = new s21::PointPannel(data->GetPointData());
  point_pannel->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), point_pannel->GetRoot(), 5,1,1,1);

  s21::DrawingArea* area = new s21::DrawingArea(data);
  gtk_grid_attach(GTK_GRID(grid), area->GetRoot(), 1, 0, 4, 5);

  pan->SetMother(area);
  //area->AttachAffineData(pan->GetData());

//  s21::FileChooser* file_chooser = new s21::FileChooser();
//  gtk_grid_attach(GTK_GRID(grid), file_chooser->GetRoot(), 6,4,1,1);


//  s21::InfoPannel* info = new s21::InfoPannel();
//  info->BuildWidget();
//  gtk_grid_attach(GTK_GRID(grid), info->GetRoot(), 6,5,1,1);

//  s21::LabelColorButtonPair* color_button = new s21::LabelColorButtonPair("AAAAAA");
//  gtk_grid_attach(GTK_GRID(grid), color_button->GetRoot(), 6,0, 2,1);

//  const char* arr[10] = {"AAA", "BBB", "CCC", "DDD", nullptr};
//  s21::LabelDropDownButtonPair* lddb = new s21::LabelDropDownButtonPair("_LABEL_", arr);
//  gtk_grid_attach(GTK_GRID(grid), lddb->GetRoot(), 6,0,1,1);

  //g_print("\nSelected = %i\n", drop_down_button->GetValue());

 // g_signal_connect(button, "clicked", G_CALLBACK(PrintDouble), drop_down_button);



  float* arr = data->GetTranslation();
  g_print("Data is = %f, %f, %f", arr[0], arr[1], arr[2]);
*/
  gtk_widget_set_visible(window, true);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", APPLICATION_NONE_FLAG);
  g_signal_connect (app, "activate", G_CALLBACK(Activate), NULL);
  //g_signal_connect
  status = g_application_run (G_APPLICATION(app), argc, argv);
  g_object_unref (app);

  return status;
}
