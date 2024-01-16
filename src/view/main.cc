#include <gtk/gtk.h>

#include <iostream>

#include "widget/widget.h"
#include "widget/pair_widget.h"
#include "widget/pannel.h"

#include "widget/factory.h"
#include "widget/affine_pannel.h"
#include "widget/info_pannel.h"
#include "widget/drawing_area.h"


#ifdef __APPLE__
#define APPLICATION_NONE_FLAG G_APPLICATION_DEFAULT_FLAGS
#else
#define APPLICATION_NONE_FLAG G_APPLICATION_FLAGS_NONE
#endif


void PrintDouble(GtkWidget* button, s21::Widget* data) {
  std::vector<double*> x = static_cast<s21::DSliderPannel*>(data)->GetData();
  for (size_t i = 0; i < 3; ++i) {
    if (*x[i] > 0) {
      *x[i] = 1/(1 - *x[i]);
    }
    if (*x[i] < 0) {
      *x[i] = (1 + *x[i]);
    }
  }
  g_print("\nvalue = %lf, %lf, %lf\n", *x[0], *x[1], *x[2]);
}

 void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);
  //gtk_grid_set_row_homogeneous(GTK_GRID(grid), true);
 // gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);




  GtkWidget* button = gtk_button_new_with_label("button");
  gtk_grid_attach(GTK_GRID(grid), button, 0,2,1,1);
  //g_signal_connect(button, "clicked", G_CALLBACK(PrintDouble), pannel);


  s21::AffinePannel* pan = new s21::AffinePannel();
  pan->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), pan->GetRoot(), 0,0,2,1);

  s21::DrawingArea* area = new s21::DrawingArea();
  gtk_grid_attach(GTK_GRID(grid), area->GetRoot(), 2, 0, 4, 4);

  pan->SetMother(area);
  area->AttachAffineData(pan->GetData());

//  s21::FileChooser* file_chooser = new s21::FileChooser();
//  gtk_grid_attach(GTK_GRID(grid), file_chooser->GetRoot(), 6,4,1,1);


//  s21::InfoPannel* info = new s21::InfoPannel();
//  info->BuildWidget();
//  gtk_grid_attach(GTK_GRID(grid), info->GetRoot(), 6,5,1,1);

  s21::ColorButton* color_button = new s21::ColorButton("AAAAAA");
  gtk_grid_attach(GTK_GRID(grid), color_button->GetRoot(), 6,0, 2,1);

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
