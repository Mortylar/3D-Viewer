#include <gtk/gtk.h>

#include "input_pannel.h"

/*GtkWidget* pannel() {
  GtkWidget* label = gtk_label_new("label");
  GtkWidget* line = gtk_text_new();
  GtkWidget* grid = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), label, 0,0,1,1);
  gtk_grid_attach(GTK_GRID(grid), line, 1, 0, 2,1);
  return grid;
}
*/
static void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;
  InputPannel pannel;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);


  gtk_grid_attach(GTK_GRID(grid), pannel.GetGrid(), 0,0,1,1);

 // GtkWidget* pannel_2 = pannel();
 // gtk_grid_attach(GTK_GRID(grid), pannel_2, 1,0,1,1);

  //label = gtk_label_new("label");
  //gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);

  //line = gtk_text_new();
  //gtk_grid_attach()


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
