#include <gtk/gtk.h>
#include <epoxy/gl.h>
#include <iostream>
#include <vector>
#include "widget/widget.h"
#include "widget/aaa.h"


 static void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  s21::AAA* ar = new s21::AAA();
  ar->SignalConnect();
  gtk_grid_attach(GTK_GRID(grid), ar->GetRoot(), 0, 0, 3, 3);


  gtk_widget_show (window);
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
