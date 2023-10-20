#include <gtk/gtk.h>

#include "pannel.h"

static void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;
  Pannel pannel(3);

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);


  gtk_grid_attach(GTK_GRID(grid), pannel.GetRoot(), 0,0,1,1);
  pannel.SetName("pannel");
  const char** names = new const char*;
  names[0] = "lable_x";
  names[1] = "lable_y";
  names[2] = "lable_z";
  pannel.SetLabels(names);

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
