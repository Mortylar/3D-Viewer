#ifndef SRC_MODEL_OPENGL_MODEL_H_
#define SRC_MODEL_OPENGL_MODEL_H_


#include <epoxy/gl.h>
#include <gtk/gtk.h>
#include <vector>


#ifndef STB_IMAGE_WRITE_IMPLEMENTATION 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include "../libs/stb_image_write.h"
#endif

#ifndef STB_IMAGE_IMPLEMENTATION 
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "../libs/stb_image.h"
#endif

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

  void LoadShader(const char* vertex_path, const char* fragment_path, const char* geometry_path) {
    InitShader(vertex_path, fragment_path, geometry_path);
  }

  GLuint GetProgram() {
    return program_;
  }

private:
  GLuint program_ = 0;

  void InitShader(const char* vertex_path, const char* fragment_path, const char* geometry_path) {
    GLuint vertex, fragment, geometry;
    int status;

    vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(vertex_path));

    if (vertex) {
      fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(fragment_path));
        if (fragment && geometry_path) {
          g_print("\ngeom shader start %s\n", geometry_path);
	  geometry = CreateShader(GL_GEOMETRY_SHADER, LoadFile(geometry_path));
	  if (!geometry) {
	    g_print("\ngeometry shader failed\n");
	  }
	}
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
    if (geometry_path) { 
      glAttachShader(program_, geometry);
      g_print("\nattach\n");
    }
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
    glDetachShader(program_, geometry); //TODO

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
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
      g_print("\ntype = %s\n", (type == GL_VERTEX_SHADER) ? "vertex" :
                                   ((type == GL_FRAGMENT_SHADER) ? "fragment" : "geometry"));
      g_print("\nprogram link failed = %s\n", buffer);

    } // TODO
    delete src;
    return shader;
  }

  char *LoadFile(const char *file_name) {
    int len = 4096; // TODO
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

class Texture {
public:
  Texture() {};

  ~Texture() {};

  GLuint GetID() {
    return id_;
  }

  void Create(const std::string& file_name) {
    if (file_name != file_) {
      file_ = file_name;
      unsigned char* data = stbi_load(file_name.data(), &width_, &height_, &color_mod_, 0);
      if (color_mod_ < 3) {} //TODO
      glGenTextures(1, &id_);
      glBindTexture(GL_TEXTURE_2D, id_);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0,
                   ((color_mod_ == 3) ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);

      SamplerInit();
      glBindTexture(id_, 0);
      stbi_image_free(data);
    }
  }

private:
  GLuint id_ = 0;
  int width_ = 0;
  int height_ = 0;
  int color_mod_ = 0;
  std::string file_;

  void SamplerInit() {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
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
    std::string file = "1.jpg"; //TODO
    LoadTexture(file);
  }

  void LoadTexture(std::string& file) {
    texture_image_.Create(file);
  }//TODO

  void Draw() {
    if (vertex_->GetVertexBuffer() != 0) {
      DrawFigure();
    }

    g_warning("\nepoxy = %i\n", epoxy_glsl_version());
  }

  unsigned int* Mirroring(size_t width, size_t height, unsigned int* data) {
    unsigned int arr[width*height];
    for (size_t i = 0; i < height; ++i) {
      unsigned int* row = data + width*i;
      unsigned int* arr_row = arr + width*(height - i - 1);
      for (size_t j = 0; j < width; ++j) {
        arr_row[j] = row[j];
      }
    }

    for (size_t i = 0; i < width*height; ++i) {
      data[i] = arr[i];
    }
    return data;
  }

  void SavePicture(size_t m_width, size_t m_height, const char* file_name, const char* type) {
    g_print("\nsave picture\n");

    size_t width = gtk_widget_get_width(GTK_WIDGET(area_));
    size_t height = gtk_widget_get_height(GTK_WIDGET(area_));
    size_t chanels = 4;

		GLint default_frame_buffer; 
		glGetIntegerv(GL_FRAMEBUFFER, &default_frame_buffer);
		g_warning("\nframebuffer_id = %i\n", default_frame_buffer);

    unsigned int* data = new unsigned int[width * height]{0};
		//glBindBuffer(GL_FRAMEBUFFER, default_frame_buffer);
   // Draw();
   // glPixelStorei(GL_PACK_ALIGNMENT, 1);
    //glReadPixels(m_width - width, m_height - height, width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, data);
    
    glReadPixels(m_width - width, m_height - height, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		data = Mirroring(width, height, data);
   
   stbi_write_png(file_name, width, height, chanels, data, chanels*width);
   stbi_write_jpg(file_name, width, height, chanels, data, 80);
   stbi_write_bmp(file_name, width, height, chanels, data);

    g_print("\nw = %li\nh = %li\n", width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
  }


private:
  s21::Data *data_ = nullptr;
  GtkGLArea *area_ = nullptr;

  GLuint vao_ = 0;
  //GLuint program_ = 0;
  Texture texture_image_;
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
    //float mvp[16]{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
   // LoadTexture("1.png");
    Matrix4f mvp;
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
    //glClearDepth(1.0);
  }

  void ConnectBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_->GetVertexBuffer());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_TEXTURE_2D, texture_->GetVertexBuffer());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr); //TODO ->
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, normals_->GetVertexBuffer());
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr); //TODO -> glTexCoordPointer
    glEnableVertexAttribArray(2);
  }

  void DrawPoints(Matrix4f& mvp) {
    if (data_->GetPointType()) {
      mvp_location_ = glGetUniformLocation(point_shader.GetProgram(), "mvp");
      color_location_ = glGetUniformLocation(point_shader.GetProgram(), "color");
      glUseProgram(point_shader.GetProgram());
      glBindVertexArray(vao_);
      glUniformMatrix4fv(mvp_location_, 1, GL_TRUE, &mvp(0,0));
      glEnableVertexAttribArray(0); //TODO??
				    //
      GdkRGBA color = *(data_->GetPointColor());
      GLfloat point_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(color_location_, 1, point_color);
      glUniform1f(glGetUniformLocation(point_shader.GetProgram(), "size"), data_->GetPointSize());
      glUniform1i(glGetUniformLocation(point_shader.GetProgram(), "type"), data_->GetPointType());
      //glUniform1f(point_size_location_, data_->GetPointSize());
      //glPointSize(data_->GetPointSize());
      glDrawArrays(GL_POINTS, 0, s21::Figure::GetInstance()->GetVertexCount());
      glFlush();
    }
  }

  void DrawLines(Matrix4f& mvp) {
    if (data_->GetLineType()) {
      mvp_location_ = glGetUniformLocation(line_shader.GetProgram(), "mvp");
      //color_location_ = glGetUniformLocation(line_shader.GetProgram(), "color");
      glUseProgram(line_shader.GetProgram());
      glBindVertexArray(vao_);
     // mvp.Print();
      glUniformMatrix4fv(mvp_location_, 1, GL_TRUE, &mvp(0,0));
      glEnableVertexAttribArray(0); //TODO??

      GdkRGBA color = *(data_->GetLineColor());
      GLfloat line_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(glGetUniformLocation(line_shader.GetProgram(), "color"), 1, line_color);

      color = *(data_->GetAreaColor());
      GLfloat background_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(glGetUniformLocation(line_shader.GetProgram(), "background_color"), 1, background_color);


      glUniform1f(glGetUniformLocation(line_shader.GetProgram(), "size"), data_->GetLineWidth());
      glUniform1i(glGetUniformLocation(line_shader.GetProgram(), "type"), data_->GetLineType());
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

  void DrawSurfaces(s21::Matrix4f& mvp) { 
    mvp_location_ = glGetUniformLocation(texture_shader.GetProgram(), "mvp");
    glUseProgram(texture_shader.GetProgram());
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp(0,0));



    glBindBuffer(GL_ARRAY_BUFFER, vertex_->GetVertexBuffer());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, texture_->GetVertexBuffer());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr); //TODO ->
    glEnableVertexAttribArray(1);

    //glEnableVertexAttribArray(0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    glTexBuffer(GL_TEXTURE_BUFFER, GL_TEXTURE0, texture_->GetVertexBuffer());

    //glFrontFace(GL_CW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_image_.GetID());
    //glBindTexture(GL_TEXTURE_BUFFER, texture_->GetVertexBuffer());
    //glDrawArrays(GL_TRIANGLE_FAN, 0, s21::Figure::GetInstance()->GetVertex().size());
   
   // std::vector<GLuint> texture_ind = texture_->GetElementBuffer();   
    std::vector<GLuint> element_buffer = vertex_->GetElementBuffer();
    for(size_t i = 0; i < element_buffer.size(); ++i) {
      //glBindTexture(GL_TEXTURE_2D, texture_buffer_); 
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer[i]);
     // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texture_ind[i]);
      glDrawElements(GL_TRIANGLE_STRIP, s21::Figure::GetInstance()->GetVSurface(i).size(),
                     GL_UNSIGNED_INT, nullptr);
    }
/*
    std::vector<GLuint> t_element_buffer = texture_->GetElementBuffer();
    for(size_t i = 0; i < t_element_buffer.size(); ++i) {
      glBindTexture(GL_TEXTURE_2D, texture_buffer_); 
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_element_buffer[i]);
      //glBindBuffer(GL_ELEMENT)
      glDrawElements(GL_TRIANGLE_STRIP, s21::Figure::GetInstance()->GetTSurface(i).size(),
                     GL_UNSIGNED_INT, nullptr);
      glFlush();
      glBindTexture(GL_TEXTURE_2D, 0);
    }
*/

  }

  void InitShaders() {
    point_shader.LoadShader("glarea/point_vs.glsl", "glarea/point_fs.glsl", "glarea/point_gs.glsl");
    line_shader.LoadShader("glarea/line_vs.glsl", "glarea/line_fs.glsl", "glarea/line_gs.glsl");
    texture_shader.LoadShader("glarea/texture_vs.glsl", "glarea/texture_fs.glsl", nullptr);
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

  void ComputeMVP(Matrix4f& mvp) {
    //Scaling(mvp);
    //Rotation(mvp);
    //Translation(mvp);
    Projection(mvp);
    Translation(mvp);
    Rotation(mvp);
    Scaling(mvp);
  }

  void Rotation(Matrix4f& mvp) {
    Affine3D affine;
    float *rotor = data_->GetRotation();
    mvp *= affine.GetRotation(rotor[0], rotor[1], rotor[2]);
  }

  void Scaling(Matrix4f& mvp) {
    Affine3D affine;
    float *scale = data_->GetScaling();
    mvp *= affine.GetScaling(scale[0], scale[1], scale[2]);
  }

  void Translation(Matrix4f& mvp) {
    Affine3D affine;
    float *trans = data_->GetTranslation();
    mvp *= affine.GetTranslation(trans[0], trans[1], 5 + trans[2]);
  }

  void Projection(Matrix4f& mvp) {
    Affine3D affine;
   // mvp *= affine.GetTranslation(0,0,5);
    if(data_->GetProjection() == 0) { 
      mvp *= affine.GetParralelProjection();
    } else {
      mvp *= affine.GetCentralProjection();
    }
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
