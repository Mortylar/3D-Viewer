#include <gtk/gtk.h>

#include <iostream>

#include "widget.h"
#include "pair_widget.h"
#include "pannel.h"

 void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);



  s21::DSpinButtonPannel pannel(5);
  gtk_grid_attach(GTK_GRID(grid), pannel.GetRoot(), 1, 1, 1, 1);
  pannel.SetNames(0, "first");
  pannel.SetNames(1, "first");
  pannel.SetValue("Second");
  pannel.SetName("123");
  gtk_widget_set_visible(window, true);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK(Activate), NULL);
  status = g_application_run (G_APPLICATION(app), argc, argv);
  g_object_unref (app);

  return status;
}
