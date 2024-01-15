#include <gtk/gtk.h>

#include <iostream>


#ifdef __APPLE__
#define APPLICATION_NONE_FLAG G_APPLICATION_DEFAULT_FLAGS
#else
#define APPLICATION_NONE_FLAG G_APPLICATION_FLAGS_NONE
#endif

void Response(GtkWidget* file_chooser_widget, gpointer* data) {
  GtkFileChooser* chooser = GTK_FILE_CHOOSER(file_chooser_widget);
 // GFile* file = gtk_file_chooser_get_file(chooser);
 // g_print("\nFile is %s\n", file);
}

void FileOpened(GObject* source, GAsyncResult* result, void* data) {
  GFile* file;

  file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, NULL);
  g_print("\nPATH IS %s\n", g_file_get_path(file));

}

void Clicked(GtkWidget* button, GtkWidget* demo) {
  GtkWindow *parent = GTK_WINDOW (gtk_widget_get_root (button));
  GtkFileDialog *dialog;
  GtkFileFilter *filter;
  GListStore *filters;

  dialog = gtk_file_dialog_new ();

  //filter = gtk_file_filter_new ();
  //gtk_file_filter_set_name (filter, "Images"); 
  //gtk_file_filter_add_pixbuf_formats (filter);
  //filters = g_list_store_new (GTK_TYPE_FILE_FILTER);
  //g_list_store_append (filters, filter);
  //g_object_unref (filter);

  //gtk_file_dialog_set_filters (dialog, G_LIST_MODEL (filters));
  //g_object_unref (filters);

  gtk_file_dialog_open (dialog, parent, NULL, FileOpened, demo);

  g_object_unref (dialog);
}

 void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);



  GtkWidget* button = gtk_button_new_with_label("FILE");
  g_signal_connect(button, "clicked", G_CALLBACK(Clicked), NULL);


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
