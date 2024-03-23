#ifndef SRC_MODEL_OPENGL_MODEL_H_
#define SRC_MODEL_OPENGL_MODEL_H_

#include <gtk/gtk.h>
#include <vector>

namespace s21 {

class Buffer {
public:
  Buffer(){};

  ~Buffer() {
    Clear();
  }

  void CreateBuffer(std::vector<float>& v_data, std::vector<std::vector<unsigned int>>& e_data) {
    Clear();
    CreateVertexBuffer(v_data);
    CreateElementBuffer(e_data);
  }

private:
  GLuint vertex_;
  std::vector<GLuint> element_;

  void CreateVertexData(std::vector<float>& data) {
    glGenBuffers(1, &vertex_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*data.size(), data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void CreateElementBuffer(std::vector<std::vector<unsigned int>>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
      GLuint tmp_buffer = 0;
      glGenBuffers(1, &tmp_buffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp_buffer);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*data[i].size(),
                                            data[i].data(), GL_STATIC_DRAW);
      glBundBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      element_.push_back(tmp_buffer);
    }
  }

  void Clear() {
    if (vertex_) glDeleteBuffers(1, &vertex_);
    for (size_t i = 0; i < element_.size(); ++i) {
      glDeleteBuffers(1, &(element[i]));
    }
    element_.clear();
};






class OpenGLModel {
public:
  OpenGLModel() {}

  ~OpenGLModel() {
    DeleteProgram();
  }

  void SetGLArea(GtkGLArea* area) {
    area_ = area;
    gtk_gl_area_make_current(GTK_GL_AREA(area_));
  }

  void ConnectData(s21::Data data) {
    data_ = data;
  }

  void SetBuffer() {
    gtk_gl_area_make_current(GTK_GL_AREA(area_));
    //context_ = gtk_gl_area_get_context(GTK_GL_AREA(area_));
    InitBuffer();
    InitShader();
  }



private:
  s21::Data* data_ = nullptr;
  GtkWidget *area_ = nullptr;

  GLuint vao_ = 0;
  //GLuint vertex_buffer_ = 0;
  //GLuint texture_buffer_ = 0;
  //GLuint normals_buffer_ = 0;

  GLuint program_ = 0;
  GLuint mvp_location_ = 0;

  Buffer vertex_;
  Buffer texture_;
  Buffer normals_;

  //std::vector<GLuint> element_buffer_;
  //std::vector<GLuint> texture_buffer_;
  //std::vector<GLuint> normals_buffer_;


  void InitBuffer() {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    std::vector<float> v = s21::Figure::GetInstance()->GetVertex();
    std::vector<std::vector<unsigned int>> e = s21::Figure::GetInstance()->GetVSurface();
    vertex_.CreateBuffer(v, e);

    v = s21::Figure::GetInstance()->GetTextures();
    e = s21::Figure::GetInstance()->GetTSurface();
    texture_.CreateBuffer(v,e);

    v = s21::Figure::GetInstance()->GetNormals();
    e = s21::Figure::GetInstance()->GetNSurface();
    normals_.CreateBuffer(v,e);
  }

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
      return; //TODO
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
    } // TODO

    mvp_location_ = glGetUniformLocation(program_, "mvp");

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
      g_print("\nCreate shader error\n");
    } // TODO
    delete src;
    return shader;
  }

  void DeleteProgram() {
    glDeleteProgram(program_);
    program_ = 0;
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
  }

};
} // namespace s21

#endif
