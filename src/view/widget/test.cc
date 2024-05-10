#include <gtk/gtk.h>
#include "widget.h"

static void Activate(GtkApplication* app, void* data) {
  GtkWidget* window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "window");

  GtkWidget* grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  s21::FileSaver* file_saver = new s21::FileSaver();
  gtk_grid_attach(GTK_GRID(grid), file_saver->GetRoot(), 0,0,1,1);

  gtk_widget_set_visible(window, true);
}


int main(void) {
  GtkApplication* app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(Activate), NULL);
  g_application_run(G_APPLICATION(app), 0, NULL);
  g_object_unref(app);
  return 0;
}
