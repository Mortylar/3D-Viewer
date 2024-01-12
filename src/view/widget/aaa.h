#ifndef SRC_VIEW_DRAWING_AREA_H_
#define SRC_VIEW_DRAWING_AREA_H_

#include <gtk/gtk.h>
#include <epoxy/gl.h>
//#include <iostream>
//#include <vector>
#include "widget.h"

namespace s21 {
class AAA : public s21::Widget{
  public:
    AAA() {
      area_ = gtk_gl_area_new();
      gtk_widget_set_hexpand(area_, TRUE);
      gtk_widget_set_vexpand(area_, TRUE);
      gtk_frame_set_child(GTK_FRAME(GetFrame()), area_);
      //`gtk_widget_set_size_request(area, 100,100);

      g_print("\nthis=%p, this->area = %p\n", this, this->area_);
      //g_print("\n1 = %p 2 = %p\n", this->area, area);
      //g_signal_connect(area, "realize", G_CALLBACK(Realize), this);
      //g_signal_connect(area, "unrealize", G_CALLBACK(Unrealize), this);
      //g_signal_connect (area, "render", G_CALLBACK(Render), this);
    }

    void SignalConnect() { 
      g_print("\n1 = %p 2 = %p\n", this->area_, area_);
      g_signal_connect(this->area_, "realize", G_CALLBACK(Realize), this);
      g_signal_connect(this->area_, "unrealize", G_CALLBACK(Unrealize), this);
      g_signal_connect (this->area_, "render", G_CALLBACK(Render), this);
    }

    GtkWidget* GetArea() {
      return area_;
    }

    void SetMother(s21::Widget* mother) {};
    void CatchSignal(){};
    void SendSignal() {};

  private:
    GtkWidget* area_ = nullptr;
    GdkGLContext* context_ = NULL;

    GLuint vao_ = 0;
    GLuint position_buffer_ = 0; //-->init_buffer
    GLuint element_buffer_ = 0; //-->init_Buffer

    GLuint program_ = 10;  //-->init_shaders
    GLuint mvp_location_ = 10; //-->init_shaders


    std::vector<float> v3{ 0.1, 0.1, -0.1,
                              -0.1, 0.1, -0.1,   
                              -0.1, -0.1, -0.1,  
                              0.1, -0.1 ,-0.1, 
                              0.2, 0.2, 0.1,
                              -0.2, 0.2, 0.1,   
                              -0.2, -0.2, 0.1,  
                              0.2, -0.2 ,0.1};

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

void InitBuffers() {
  GLuint vao, buffer, element_buff;

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);


  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*v3.size(), v3.data(), GL_STATIC_DRAW);
  //glBindBuffer(GL_ARRAY_BUFFER, 0); //TODO

  glGenBuffers(1, &element_buff);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buff);
  
  //vao_ = vao;
  position_buffer_ = buffer;
  element_buffer_ = element_buff;
}

GLuint CreateShader(int type, const char* src) {
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


void InitShaders() { //(GLuint* program_out, GLuint* mvp_out) {
  GLuint vertex, fragment;
  int status; //??
  
  const char* file_name = "glarea/vs.glsl";
  vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(file_name));

  if (vertex) {
    file_name = "glarea/fs.glsl";
    fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(file_name));
  } else {
    g_print("\nvertex shader failed\n");
    return;
  }

  if (!fragment) {
    glDeleteShader(vertex);
    g_print("\nfragment shader failed\n");
    return;
  }

  program_ = glCreateProgram();
  glAttachShader(program_, vertex);
  glAttachShader(program_, fragment);
  glLinkProgram(program_);

  glGetProgramiv(program_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    g_print("\nprogram link failed\n");
  } //TODO

  mvp_location_ = glGetUniformLocation(program_, "mvp");

  glDetachShader(program_, vertex);
  glDetachShader(program_, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  //g_print("\nprog = %i, <-> %i\n", program, *program_out);
}



static void Realize(GtkWidget* widget, s21::AAA* self) {
  gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
  self->context_ = gtk_gl_area_get_context(GTK_GL_AREA(self->area_));

  self->InitBuffers();
  self->InitShaders(); //(&self->program, &self->mvp_location);
}

static void Unrealize(GtkWidget* widget ) {
  gtk_gl_area_make_current(GTK_GL_AREA(widget));
  //glDeleteBuffers(1, &position_buffer);
  //glDeleteProgram(program);
}

void DrawFigure() {
  float mvp[16] = {1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   0, 0,0,1}; 
  glUseProgram(program_);
  g_print("\nmvp = %i, program = %i\n", mvp_location_, program_);

  glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp[0]);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);

  glLineWidth(1);
 // glEnable(GL_POINT_SMOOTH);
  glPointSize(10);
  glEnable(GL_POINT_SMOOTH);
  glDrawArrays(GL_POINTS, 0, 4);
  glDrawArrays(GL_POINTS, 4, 4);
  glDrawArrays(GL_LINE_LOOP, 0, 8);
  //glDrawArrays(GL_LINE_LOOP, 6, 9);

  //glDisableVertexAttribArray(0);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

static void Render(GtkGLArea* area, GdkGLContext* context, s21::AAA* self){
  gtk_gl_area_make_current(GTK_GL_AREA(area));
  g_print("\nself = %p self->area = %p area =%p\n", self, self->GetArea(), area);
  glClearColor(0.0, 0.0, 0.5, 1.0);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  self->DrawFigure();
  glFlush();
  //return true;
}


};
}

#endif
