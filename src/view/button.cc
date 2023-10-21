#include <gtk/gtk.h>


static void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;
  GtkWidget* spin_button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  GtkAdjustment* adj = gtk_adjustment_new(0.0, 0.0, 1e2, 1, 0, 0);
  spin_button = gtk_spin_button_new(adj, 100, 12);
  gtk_grid_attach(GTK_GRID(grid), spin_button, 0, 0, 1, 1);


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
