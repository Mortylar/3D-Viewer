#include <gtk/gtk.h>
#include <epoxy/gl.h>
#include <iostream>
#include <vector>

static double x,y,z;
static GtkWidget* area = NULL;
static GdkGLContext* context = NULL;

static GLuint position_buffer; //-->init_buffer
static GLuint element_buffer; //-->init_Buffer

static GLuint program;  //-->init_shaders
static GLuint mvp_location; //-->init_shaders

static std::vector<float> rot_matrix {1,0,0, 0,1,0, 0,0,1};

static std::vector<double> v{0.5,-0.5,-0.5,0.5,-0.5,0.5,-0.5,-0.5,0.5,-0.5,-0.5,-0.5,
                              0.5,0.5,-0.5,0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5}; //24 = 8*3

static std::vector<int> s{2,3,3,4,4,2, 8,7,7,6,6,8,
	5,6,6,2,2,5, 6,7,7,3,3,6, 3,7,7,8,8,3,1,4,4,8,8,1};


static std::vector<float> v3{ 0.1, 0.1, -0.1,
                              -0.1, 0.1, -0.1,   
                              -0.1, -0.1, -0.1,  
                              0.1, -0.1 ,-0.1, 
                              0.2, 0.2, 0.1,
                              -0.2, 0.2, 0.1,   
                              -0.2, -0.2, 0.1,  
                              0.2, -0.2 ,0.1};

static std::vector<int> f3 {1,2,3,4};
static std::vector<int> f4 {5,6,7,8};

void ResetRotMatrix() {
  rot_matrix = {1,0,0,  0,1,0,  0,0,1};
}

char* LoadFile(const char* file_name) {
  int len = 1024; //TODO
  char* text = new char[len]();
  FILE* fp = fopen(file_name, "rb");
  if (fp) {
    fread(text, 1, len, fp);
    fclose(fp);
  } else {
    g_print("\nError Opening File\n");
  }
  return text;
}

static void InitBuffers(GLuint* vao_out, GLuint* buffer_out, GLuint* el_buff) {
  GLuint vao, buffer, element_buff;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);


  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*v3.size(), v3.data(), GL_STATIC_DRAW);
  //glBindBuffer(GL_ARRAY_BUFFER, 0); //TODO

  glGenBuffers(1, &element_buff);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buff);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*f3.size(), f3.data(), GL_STATIC_DRAW);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*f4.size(), f4.data(), GL_STATIC_DRAW);
 // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


  if(vao_out != NULL) *vao_out = vao;
  if(buffer_out != NULL) *buffer_out = buffer;
  if(el_buff != NULL) *el_buff = element_buff;

 // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static GLuint CreateShader(int type, const char* src) {
  GLuint shader;
  int status;

  shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    g_print("\nCreate shader error\n");
  } //TODO
  return shader;
}


static void InitShaders(GLuint* program_out, GLuint* mvp_out) {
  GLuint vertex, fragment;
  GLuint program = 0;
  GLuint mvp = 0;
  int status; //??
  
  const char* file_name = "glarea/glarea-gl.vs.glsl";
  vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(file_name));

  if (vertex) {
    file_name = "glarea/glarea-gl.fs.glsl";
    fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(file_name));
  } else {
    g_print("\nvertex shader failed\n");
    *program_out = 0;
    return;
  }

  if (!fragment) {
    *program_out = 0;
    glDeleteShader(vertex);
    g_print("\nfragment shader failed\n");
    return;
  }

  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status = GL_FALSE) {
    g_print("\nprogram link failed\n");
  } //TODO

  mvp = glGetUniformLocation(program, "mvp");

  glDetachShader(program, vertex);
  glDetachShader(program, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  if (program_out) *program_out = program;
  if (mvp_out) *mvp_out = mvp;
  g_print("\nprog = %i, <-> %i\n", program, *program_out);
}



static void Realize(GtkWidget* widget) {
  gtk_gl_area_make_current(GTK_GL_AREA(widget));
  context = gtk_gl_area_get_context(GTK_GL_AREA(widget));

  InitBuffers(NULL, &position_buffer, &element_buffer);
  InitShaders(&program, &mvp_location);
}

static void Unrealize(GtkWidget* widget) {
  gtk_gl_area_make_current(GTK_GL_AREA(widget));
  glDeleteBuffers(1, &position_buffer);
  glDeleteProgram(program);
}

static void DrawFigure() {
  float mvp[16] = {rot_matrix[0]/2, rot_matrix[1]/2, rot_matrix[2]/2, 0,
                   rot_matrix[3]/2, rot_matrix[4]/2, rot_matrix[5]/2, 0,
                   rot_matrix[6]/2, rot_matrix[7]/2, rot_matrix[8]/2, 0,
                   0, 0, 0, 1}; 
  //{0.5,0,0,0,  0,0.5,0,0, 0,0,0.5,0, 0,0,0,1};
  //for (int i = 0; i < 4; ++i) {
  //  g_print("\n%f<>%f<>%f<>%f\n", mvp[4*i], mvp[4*i+1], mvp[4*i+2], mvp[4*i+3]);
 // }
  //g_print("End\n");
  ResetRotMatrix();
  glUseProgram(program);

  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0]);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);

  //glLineWidth(1);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(10);
  glEnable(GL_POINT_SMOOTH);
  glDrawArrays(GL_POINTS, 0, 4);
  glDrawArrays(GL_POINTS, 4, 4);
  //glDrawArrays(GL_LINE_LOOP, 6, 9);

  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

static void Render(GtkGLArea* area, GdkGLContext* context){

  glClearColor(0.0, 0.0, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawFigure();
  glFlush();
  //return true;
}

void Rotate(std::vector<float>& v, double x_rad, double y_rad, double z_rad) {
  size_t size = v.size();
  for (size_t i = 0; i < size; i += 3) {
    double x_tmp = v[i + 0];
    double x_rot_1 = sin(x_rad) * v[i + 1] - cos(x_rad) * v[i + 2];
    double x_rot_2 = cos(x_rad) * v[i + 1] + sin(x_rad) * v[i + 2];
    double y_z_rot = cos(y_rad) * x_tmp;

    v[i + 0] = cos(z_rad) * (y_z_rot + sin(y_rad) * x_rot_1) + sin(z_rad) * x_rot_2;
    v[i + 1] = sin(z_rad) * (-y_z_rot - sin(y_rad) * x_rot_1)  + cos(z_rad) * x_rot_2;
    v[i + 2] = x_tmp * sin(y_rad) - x_rot_1 * cos(y_rad);
  }
}

static void XRot(GtkAdjustment* adj) {
  x = gtk_adjustment_get_value(adj);
  Rotate(rot_matrix, x, y,z);
  gtk_widget_queue_draw(area);
}

static void YRot(GtkAdjustment* adj) {
  y = gtk_adjustment_get_value(adj);
  Rotate(rot_matrix, x, y,z);
  gtk_widget_queue_draw(area);
}

static void ZRot(GtkAdjustment* adj) {
  z = gtk_adjustment_get_value(adj);
  Rotate(rot_matrix, x, y,z);
  gtk_widget_queue_draw(area);
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


  g_signal_connect(area, "realize", G_CALLBACK(Realize), NULL);
  g_signal_connect(area, "unrealize", G_CALLBACK(Unrealize), NULL);
  g_signal_connect (area, "render", G_CALLBACK(Render), NULL);

  GtkWidget* button = gtk_button_new_with_label("AAA");
  gtk_grid_attach(GTK_GRID(grid), button, 4,4,1,1);
  
  GtkAdjustment* x_adj = gtk_adjustment_new(0.0, -2*G_PI, 2*G_PI, 1, 12, 0);
  GtkWidget* x_scale_button = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, x_adj);
  g_signal_connect(x_adj, "value-changed", G_CALLBACK(XRot), NULL);
  gtk_grid_attach(GTK_GRID(grid), x_scale_button, 0,4,3,1);

  GtkAdjustment* y_adj = gtk_adjustment_new(0.0, -2*G_PI, 2*G_PI, 1, 12, 0);
  GtkWidget* y_scale_button = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, y_adj);
  g_signal_connect(y_adj, "value-changed", G_CALLBACK(YRot), NULL);
  gtk_grid_attach(GTK_GRID(grid), y_scale_button, 0,5,3,1);

  GtkAdjustment* z_adj = gtk_adjustment_new(0.0, -2*G_PI, 2*G_PI, 1, 12, 0);
  GtkWidget* z_scale_button = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, z_adj);
  g_signal_connect(z_adj, "value-changed", G_CALLBACK(ZRot), NULL);
  gtk_grid_attach(GTK_GRID(grid), z_scale_button, 0,6,3,1);

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
