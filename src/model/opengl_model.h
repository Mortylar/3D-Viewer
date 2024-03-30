#ifndef SRC_MODEL_OPENGL_MODEL_H_
#define SRC_MODEL_OPENGL_MODEL_H_

#define STB_IMAGE_IMOLEMENTATION 

#include <epoxy/gl.h>
#include <gtk/gtk.h>
#include <vector>
#include <stb/stb_image.h>

#include "../libs/data.h"
#include "affine_3d.h"
#include "figure.h" //TODO try to remove

namespace s21 {

class Buffer {
public:
  Buffer() {
    vertex_ = 0;
    element_.clear();
  }

  ~Buffer() { Clear(); }

  void CreateBuffer(std::vector<float> &v_data,
                    std::vector<std::vector<unsigned int>> &e_data) {
    Clear();
    CreateVertexBuffer(v_data);
    CreateElementBuffer(e_data);
  }

  GLuint &GetVertexBuffer() { return vertex_; }

  std::vector<GLuint> &GetElementBuffer() { return element_; }


  void Clear() {
    if (vertex_)
      glDeleteBuffers(1, &vertex_);
    for (size_t i = 0; i < element_.size(); ++i) {
      glDeleteBuffers(1, &(element_[i]));
    }
    element_.clear();
  }

private:
  GLuint vertex_ = 0;
  std::vector<GLuint> element_;

  void CreateVertexBuffer(std::vector<float> &data) {
    glGenBuffers(1, &vertex_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void CreateElementBuffer(std::vector<std::vector<unsigned int>> &data) {
    for (size_t i = 0; i < data.size(); ++i) {
      GLuint tmp_buffer = 0;
      glGenBuffers(1, &tmp_buffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp_buffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   sizeof(unsigned int) * data[i].size(), data[i].data(),
                   GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      element_.push_back(tmp_buffer);
    }
  }

  /*void Clear() {
    if (vertex_)
      glDeleteBuffers(1, &vertex_);
    for (size_t i = 0; i < element_.size(); ++i) {
      glDeleteBuffers(1, &(element_[i]));
    }
    element_.clear();
  }*/
};


class Shader {
public:
  Shader() {g_print("\nshader start\n");};

  ~Shader() { 
//    glDeleteProgram(program_);
    program_ = 0;
  }

  void LoadShader(const char* vertex_path, const char* fragment_path) {
    InitShader(vertex_path, fragment_path);
  }

  GLuint GetProgram() {
    return program_;
  }

private:
  GLuint program_ = 0;

  void InitShader(const char* vertex_path, const char* fragment_path) {
    GLuint vertex, fragment;
    int status;

    vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(vertex_path));

    if (vertex) {
      fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(fragment_path));
    } else {
      g_print("\nvertex shader failed\n");
      return; // TODO
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
      int log_len;
      char* buffer;
      glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &log_len);
      buffer = (char*)g_malloc(log_len + 1);
      glGetProgramInfoLog(program_, log_len, NULL, buffer);
      g_print("\nprogram link failed = %s\n", buffer);
    } // TODO

    //mvp_location_ = glGetUniformLocation(program_, "mvp");
    //color_location_ = glGetUniformLocation(program_, "color");
    //point_size_location_ = glGetUniformLocation(program_, "p_size");

    glDetachShader(program_, vertex);
    glDetachShader(program_, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  GLuint CreateShader(int type, const char *src) {
    GLuint shader;
    int status;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
      int log_len;
      char* buffer;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
      buffer = (char*)g_malloc(log_len + 1);
      glGetShaderInfoLog(shader, log_len, NULL, buffer);
      g_print("\ntype = %s\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
      g_print("\nprogram link failed = %s\n", buffer);

    } // TODO
    delete src;
    return shader;
  }

  char *LoadFile(const char *file_name) {
    int len = 1024; // TODO
    char *text = new char[len]();
    FILE *fp = fopen(file_name, "rb");
    if (fp) {
      fread(text, 1, len, fp);
      fclose(fp);
    } else {
      g_print("\nError Opening File\n");
    }
    return text;
  } //TODO GetFileLength


};





class OpenGLModel {
public:
  OpenGLModel() {
    vertex_ = new s21::Buffer();
    texture_ = new s21::Buffer();
    normals_ = new s21::Buffer();
  }

  ~OpenGLModel() {
    delete vertex_;
    delete texture_;
    delete normals_;
//    DeleteProgram();
  }

  void SetGLArea(GtkGLArea *area) { area_ = area; }

  void ConnectData(s21::Data *data) { data_ = data; }

  void SetBuffer() {
    gtk_gl_area_make_current(GTK_GL_AREA(area_));
    InitBuffer();
    InitShaders();
    LoadTexture("1.png");
  }

  void Draw() {
    if (vertex_->GetVertexBuffer() != 0) {
      DrawFigure();
    }

    //g_warning("\nepoxy = %i\n", epoxy_glsl_version());
  }


private:
  s21::Data *data_ = nullptr;
  GtkGLArea *area_ = nullptr;

  GLuint vao_ = 0;
  //GLuint program_ = 0;
  GLuint texture_buffer_ = 0;
  Shader point_shader;
  Shader line_shader;
  Shader texture_shader;


  GLuint mvp_location_ = 0;
  GLuint color_location_ = 0;
  GLuint point_size_location_ = 0;

  Buffer *vertex_ = nullptr;
  Buffer *texture_ = nullptr;
  Buffer *normals_ = nullptr;

  void DrawFigure() {
    float mvp[16]{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    //LoadTexture("1.png");
    ComputeMVP(mvp);
    ResetField();

    //glUseProgram(program_);
    //glBindVertexArray(vao_);
    //glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp[0]);
    //glEnableVertexAttribArray(0);

    ConnectBuffers();

    DrawSurfaces(mvp);
    DrawLines(mvp);
    DrawPoints(mvp);

    glDisableVertexAttribArray(0);
    glUseProgram(0);
  }

  void ResetField() {
    GdkRGBA *color = data_->GetAreaColor();
    glClearColor(color->red, color->green, color->blue, color->alpha + 1);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void ConnectBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_->GetVertexBuffer());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_TEXTURE_BUFFER, texture_->GetVertexBuffer());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr); //TODO ->
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, normals_->GetVertexBuffer());
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr); //TODO -> glTexCoordPointer
    glEnableVertexAttribArray(2);
  }

  void DrawPoints(float(&mvp)[16]) {
    if (data_->GetPointType()) {
      mvp_location_ = glGetUniformLocation(point_shader.GetProgram(), "mvp");
      color_location_ = glGetUniformLocation(point_shader.GetProgram(), "color");
      glUseProgram(point_shader.GetProgram());
      glBindVertexArray(vao_);
      glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp[0]);
      glEnableVertexAttribArray(0); //TODO??
				    //
      GdkRGBA color = *(data_->GetPointColor());
      GLfloat point_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(color_location_, 1, point_color);
      //glUniform1f(point_size_location_, data_->GetPointSize());
      glPointSize(data_->GetPointSize());
      glDrawArrays(GL_POINTS, 0, s21::Figure::GetInstance()->GetVertexCount());
      glFlush();
    }
  }

  void DrawLines(float(&mvp)[16]) {
    if (data_->GetLineType()) {
      mvp_location_ = glGetUniformLocation(line_shader.GetProgram(), "mvp");
      color_location_ = glGetUniformLocation(line_shader.GetProgram(), "color");
      glUseProgram(line_shader.GetProgram());
      glBindVertexArray(vao_);
      glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp[0]);
      glEnableVertexAttribArray(0); //TODO??

      GdkRGBA color = *(data_->GetLineColor());
      GLfloat line_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(color_location_, 1, line_color);
      glLineWidth(data_->GetLineWidth());
      std::vector<GLuint> element_buffer = vertex_->GetElementBuffer();
      for (size_t i = 0; i < element_buffer.size(); ++i) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer[i]);
        glDrawElements(GL_LINE_LOOP,
                       s21::Figure::GetInstance()->GetVSurface(i).size(),
                       GL_UNSIGNED_INT, nullptr);
        glFlush();
      }
    }
  }

  void DrawSurfaces(float(&mvp)[16]) { 
    mvp_location_ = glGetUniformLocation(texture_shader.GetProgram(), "mvp");
    glUseProgram(texture_shader.GetProgram());
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp[0]);
    glEnableVertexAttribArray(0); //TODO??

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_buffer_);
    std::vector<GLuint> element_buffer = vertex_->GetElementBuffer();
    for(size_t i = 0; i < element_buffer.size(); ++i) {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer[i]);
      //glBindBuffer(GL_ELEMENT)
      glDrawElements(GL_TRIANGLE_STRIP, s21::Figure::GetInstance()->GetVSurface(i).size(),
                     GL_UNSIGNED_INT, nullptr);
      glFlush();
    }
  }

  void InitShaders() {
    point_shader.LoadShader("glarea/point_vs.glsl", "glarea/point_fs.glsl");
    line_shader.LoadShader("glarea/line_vs.glsl", "glarea/line_fs.glsl");
    texture_shader.LoadShader("glarea/texture_vs.glsl", "glarea/texture_fs.glsl");
  }

  void InitBuffer() {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    std::vector<float> v = s21::Figure::GetInstance()->GetVertex();
    std::vector<std::vector<unsigned int>> e =
        s21::Figure::GetInstance()->GetVSurface();
    vertex_->CreateBuffer(v, e);

    v = s21::Figure::GetInstance()->GetTextures();
    e = s21::Figure::GetInstance()->GetTSurface();
    texture_->CreateBuffer(v, e);

    v = s21::Figure::GetInstance()->GetNormals();
    e = s21::Figure::GetInstance()->GetNSurface();
    normals_->CreateBuffer(v, e);
  }
/*
  void InitShader() {
    GLuint vertex, fragment;
    int status; //??

    const char *file_name = "glarea/vs.glsl";
    vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(file_name));

    if (vertex) {
      file_name = "glarea/fs.glsl";
      fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(file_name));
    } else {
      g_print("\nvertex shader failed\n");
      return; // TODO
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
      int log_len;
      char* buffer;
      glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &log_len);
      buffer = (char*)g_malloc(log_len + 1);
      glGetProgramInfoLog(program_, log_len, NULL, buffer);
      g_print("\nprogram link failed = %s\n", buffer);
    } // TODO

    mvp_location_ = glGetUniformLocation(program_, "mvp");
    color_location_ = glGetUniformLocation(program_, "color");
    //point_size_location_ = glGetUniformLocation(program_, "p_size");

    glDetachShader(program_, vertex);
    glDetachShader(program_, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  GLuint CreateShader(int type, const char *src) {
    GLuint shader;
    int status;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
      int log_len;
      char* buffer;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
      buffer = (char*)g_malloc(log_len + 1);
      glGetShaderInfoLog(shader, log_len, NULL, buffer);
      g_print("\ntype = %s\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
      g_print("\nprogram link failed = %s\n", buffer);

    } // TODO
    delete src;
    return shader;
  }
*/

  void LoadTexture(const char* file_name) {
    int width{0}, height{0}, color_mod{0};
    unsigned char* texture_data = stbi_load("3.jpg", &width, &height, &color_mod, 0);
    //g_print("Data = %s <->%li\n", "2.png", color_mod);
    //for (int i = 0; i < 1000; ++i) {
    //  g_print("a%c", texture_data[i]);
    //}
    glGenTextures(1, &texture_buffer_);
    glBindTexture(GL_TEXTURE_2D, texture_buffer_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, (color_mod == 3) ? GL_RGB : GL_RGBA , GL_UNSIGNED_BYTE, texture_data);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(texture_buffer_, 0);
    stbi_image_free(texture_data);
  }

  void ComputeMVP(float (&mvp)[16]) {
    Rotation(mvp);
    Scaling(mvp);
    float* trans = data_->GetTranslation();
    Translation(mvp);
    //mvp[3] = 2 * mvp[2];
    //mvp[7] = 2 * mvp[6];
    //mvp[11] = 2 * mvp[10];

   // mvp[3] += trans[0];
   // mvp[7] += trans[1];
   // mvp[11] += trans[2];
  }

  void Rotation(float (&v)[16]) {
    Affine3D affine;
    float *rotor = data_->GetRotation();
    affine.Rotation(v, rotor[0], rotor[1], rotor[2]);
  }

  void Scaling(float (&v)[16]) {
    Affine3D affine;
    float *scale = data_->GetScaling();
    affine.Scaling(v, scale[0], scale[1], scale[2]);
  }

  void Translation(float (&v)[16]) {
    Affine3D affine;
    float *trans = data_->GetTranslation();
    affine.Translation(v, trans[0], trans[1], trans[2]);
  }

//  void DeleteProgram() {
//    glDeleteProgram(program_);
//    program_ = 0;
//  }
/*
  char *LoadFile(const char *file_name) {
    int len = 1024; // TODO
    char *text = new char[len]();
    FILE *fp = fopen(file_name, "rb");
    if (fp) {
      fread(text, 1, len, fp);
      fclose(fp);
    } else {
      g_print("\nError Opening File\n");
    }
    return text;
  }
  */
};
} // namespace s21

#endif
