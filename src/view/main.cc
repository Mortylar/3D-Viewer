#include <gtk/gtk.h>

#include <iostream>

#include "widget/widget.h"

void PrintDouble(GtkWidget* button, s21::DSpinButton* data) {
  double x = data->GetValue();
  g_print("\nvalue = %p, %lf\n", button, x);
}

 void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);


  s21::Label lab("label");
  gtk_grid_attach(GTK_GRID(grid), lab.GetRoot(), 0,0,1,1);

  s21::DSlider* slider = new s21::DSlider();
  gtk_grid_attach(GTK_GRID(grid), slider->GetRoot(), 0,1,1,1);
  //sp->SetValue(100.0);

  GtkWidget* button = gtk_button_new_with_label("button");
  gtk_grid_attach(GTK_GRID(grid), button, 0,2,1,1);
  g_signal_connect(button, "clicked", G_CALLBACK(PrintDouble), slider);

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
