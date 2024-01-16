#include <gtk/gtk.h>

#include <iostream>


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
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);


  const char* a = "AAA";
  const char* b = "BBB";
  const char* c = "CCC";

  const char** arr = new const char*[4];
  arr[0] = "AAA";
  arr[1] = "BBB";
  arr[2] = "CCC";
  arr[3] = nullptr;
  GtkWidget* button = gtk_drop_down_new_from_strings(arr);


  gtk_grid_attach(GTK_GRID(grid), button, 0,0,1,1);

  gtk_widget_set_visible(window, true);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", APPLICATION_NONE_FLAG);
  g_signal_connect (app, "activate", G_CALLBACK(Activate), NULL);
  status = g_application_run (G_APPLICATION(app), argc, argv);
  g_object_unref (app);

  return status;
}
