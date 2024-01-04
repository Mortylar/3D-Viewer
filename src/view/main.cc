#include <gtk/gtk.h>

#include <iostream>

#include "widget/widget.h"
#include "widget/pair_widget.h"
#include "widget/pannel.h"

#include "widget/factory.h"
#include "widget/affine_pannel.h"

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
  //gtk_grid_set_column_homogeneous(GTK_GRID(grid), true);



  s21::Label lab("label");
  //gtk_grid_attach(GTK_GRID(grid), lab.GetRoot(), 0,0,1,1);

  s21::LabelDSliderPair* pair = new s21::LabelDSliderPair();
  //gtk_grid_attach(GTK_GRID(grid), pair->GetRoot(), 0,1,4,1);
  pair->SetName("Name");
  pair->SetValue(11.11);
  //sp->SetValue(100.0);
  
  GtkAdjustment* a1 = gtk_adjustment_new(0.0, -10, 20, 1, 12, 0);
  GtkAdjustment* a2 = gtk_adjustment_new(0.0, -10, 20, 1, 12, 0);
  GtkAdjustment* a3 = gtk_adjustment_new(0.0, -10, 20, 1, 12, 0);

  s21::DSliderPannel* pannel = new s21::DSliderPannel{a1, a1, a1};
  gtk_grid_attach(GTK_GRID(grid), pannel->GetRoot(), 0,3,1,1);
  pannel->SetName("Name");
  pannel->SetName(0, "Name_0");
  pannel->SetName(1, "Name_1");
  pannel->SetName(2, "Name_2");

  s21::Widget* ptr = new s21::Label();

  //pannel->SetValue("Value");

  //try {g_print("\nvalue = %s\n", pannel->GetValue(2));
  //} catch (std::exception& error){
  //  g_print("\nERROR\n");
 // }

  GtkWidget* button = gtk_button_new_with_label("button");
  gtk_grid_attach(GTK_GRID(grid), button, 0,2,1,1);
  //g_signal_connect(button, "clicked", G_CALLBACK(PrintDouble), pannel);


  s21::ScalingPannelFactory f;
  s21::Widget* l = f.CreateWidget();
//  gtk_grid_attach(GTK_GRID(grid), l->GetRoot(), 0,0,2,1);
  g_signal_connect(button, "clicked", G_CALLBACK(PrintDouble), l);


  s21::AffinePannel* pan = new s21::AffinePannel();
  pan->BuildWidget();
  gtk_grid_attach(GTK_GRID(grid), pan->GetRoot(), 0,0,2,1);


  gtk_widget_set_visible(window, true);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(Activate), NULL);
  status = g_application_run (G_APPLICATION(app), argc, argv);
  g_object_unref (app);

  return status;
}
