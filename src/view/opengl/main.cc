#include <gtk/gtk.h>

//#include <GL/glew.h>
#include <epoxy/gl.h>
//#include <GLFW/glfw3.h>

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
//#include <SDL/SDL.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>


static GtkWidget* area = NULL;
static GdkGLContext* context = NULL;

static GLuint position_buffer;
static GLuint program;
static GLuint mvp_location;

static std::vector<double> v{1,-1,-1,1,-1,1,-1,-1,1,-1,-1,-1,
                              1,1,-1,1,1,1,-1,1,1,-1,1,-1}; //24 = 8*3

static std::vector<int> s{2,3,3,4,4,2, 8,7,7,6,6,8,
	5,6,6,2,2,5, 6,7,7,3,3,6, 3,7,7,8,8,3,1,4,4,8,8,1};


static std::vector<double> v3{-1, -1, 0,  1, -1, 0,  0, 1, 0};

static void unrealize (GtkGLArea* area) {
  gtk_gl_area_make_current(GTK_GL_AREA(area));

  glDeleteBuffers(1, &position_buffer);
  glDeleteProgram(program);
}


static void InitBuffer(GLuint* vao_out, GLuint* buffer_out) {

  GLuint vao, buffer;
  
 // glGenVertexArrays(1, &vao);
  //glBindVertexArray(vao);

  //glGenBuffers(1, &buffer);
  
  //glBindBuffer(GL_ARRAY_BUFFER, buffer);
  //glBufferData(GL_ARRAY_BUFFER, 8, v.data(), GL_STATIC_DRAW);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);

  if (vao_out != NULL) *vao_out = vao;
  if (buffer_out != NULL) *buffer_out = buffer;
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void draw() {
  //glfwInit();
  //glewInit();
  gtk_gl_area_attach_buffers(GTK_GL_AREA(area));
  gdk_gl_context_make_current(context);
  //glAttachBuffers();
  //glCreateBuffers();
  /*
  glUseProgram(program);
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
  glEnableVertexAttribArray(0); //???
  glVertexAttribPointer(0, 4, GL_DOUBLE, GL_FALSE, 0, 0);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);
  */
}

static void realize (GtkGLArea *area) {
  // We need to make the context current if we want to
  // call GL API
 // gtk_gl_area_make_current (area);
 // context = gtk_gl_area_get_context(GTK_GL_AREA(area));

  const char* vertex_path = "glarea/glarea-gl.vs.glsl";
  const char* fragment_path = "glarea/glarea-gl.fs.glsl";

  InitBuffer(NULL, &position_buffer);
  //InitShaders(vertex_path, fragment_path, &program, &mvp_location);
}

static gboolean render (GtkGLArea *area, GdkGLContext *context) {
  // inside this function it's safe to use GL; the given
  // GdkGLContext has been made current to the drawable
  // surface used by the `GtkGLArea` and the viewport has
  // already been set to be the size of the allocation
 // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  // Clear the viewport
  glClearColor (0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw your object
  //draw();
  //glFlush();
  //
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  //programm id ?? 64

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, v3.size(), v3.data(), GL_STATIC_DRAW);

 // while(true) {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0);
 // }
  glDrawArrays(GL_LINE, 0, 3);
  glDisableVertexAttribArray(0);

  //glfwSwapBuffer(area);
  //glPollEvents();
  // we completed our drawing; the draw commands will be
  // flushed at the end of the signal emission chain, and
  // the buffers will be drawn on the window
  return TRUE;
}

 static void Activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget* grid;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 600);

  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  area = gtk_gl_area_new();
  gtk_widget_set_hexpand(area, TRUE);
  gtk_widget_set_vexpand(area, TRUE);
  gtk_widget_set_size_request(area, 100,100);
  gtk_grid_attach(GTK_GRID(grid), area, 0, 0, 3, 3);


  g_signal_connect(area, "realize", G_CALLBACK(realize), NULL);
  g_signal_connect(area, "unrealize", G_CALLBACK(unrealize), NULL);
  g_signal_connect (area, "render", G_CALLBACK(render), NULL);

  GtkWidget* button = gtk_button_new_with_label("AAA");
  gtk_grid_attach(GTK_GRID(grid), button, 4,4,1,1);
  


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
