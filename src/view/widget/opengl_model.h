#ifndef SRC_VIEW_WIDGET_OPENGL_MODEL_H_
#define SRC_VIEW_WIDGET_OPENGL_MODEL_H_

#include <epoxy/gl.h>
#include <gtk/gtk.h>

#include <vector>

namespace s21 {
class Buffer {
 public:
  Buffer(GtkGLArea* area):area_(area){};

  ~Buffer() {
    glDeleteBuffers(1, &vertex_);
    glDeleteBuffers(1, &element_);
  }

  void CreateBuffer(std::vector<float>& vertex, std::vector<int>& element) {
    gtk_gl_area_make_current(area_);
    CreateVertexArrayObject();
    CreateVertexBuffer(vertex);
    CreateElementBuffer(element);
  }

  GLuint GetVAO() { return vao_; }
  GLuint GetVertexBuffer() { return vertex_; }
  GLuint GetElementBuffer() { return element_; }

 private:
  GtkGLArea* area_ = nullptr;
  GLuint vao_ = 0;  // TODO vbo
  GLuint vertex_ = 0;
  GLuint element_ = 0;

  void CreateVertexArrayObject() {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
  }

  void CreateVertexBuffer(std::vector<float>& vertex) {
    glGenBuffers(1, &vertex_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), vertex.data(),
                 GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void CreateElementBuffer(std::vector<int>& element) {
    glGenBuffers(1, &element_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * element.size(),
     //            element.data(), GL_STATIC_DRAW);
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
};

class Shader {
 public:
  Shader(GtkGLArea* area):area_(area) {}
  ~Shader() {}

  void InitShader() {
    gtk_gl_area_make_current(area_);

    GLuint vertex = CreateShader(GL_VERTEX_SHADER, GetVertexShaderSource());
    if (!vertex) throw std::runtime_error("Compilation vertex shader failed");
    
    GLuint fragment =
        CreateShader(GL_FRAGMENT_SHADER, GetFragmentShaderSource());
    if (!fragment)
      throw std::runtime_error("Compilation fragment shader failed");

    program_ = glCreateProgram();
    glAttachShader(program_, vertex);
    glAttachShader(program_, fragment);
    glLinkProgram(program_);

    int link_status = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &link_status);
    if (GL_FALSE == link_status) g_print("\nprogram link failed\n");

    mvp_ = glGetUniformLocation(program_, "mvp");

    glDetachShader(program_, vertex);
    glDetachShader(program_, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  GLuint GetProgram() { return program_; }
  GLuint GetMVP() { return mvp_; }

 private:
  GtkGLArea* area_ = nullptr;
  GLuint program_ = 0;
  GLuint mvp_ = 0;
  const char* vs_file_ = "glarea/vs.glsl";
  const char* fs_file_ = "glarea/fs.glsl";

  GLuint CreateShader(int type, const char* src) {
   static GLuint shader = glCreateShader(type); //TODO
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int compile_status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
      g_print("\nCreate Shader error! %i=%i\n", type, GL_FRAGMENT_SHADER);
    }
    return shader;
  }

  char* GetVertexShaderSource() {
    return LoadFile(vs_file_);
  }

  char* GetFragmentShaderSource() {
    return LoadFile(fs_file_);
  }

  char* LoadFile(const char* file_name) {
    static int length = 1024;
    char* text = new char[length]();
    FILE* fp = fopen(file_name, "rb");
    if(fp) {
      fread(text, 1, length, fp);
      fclose(fp);
    } else {
      g_print("\nLoad Error\n"); //TODO
    }
    return text;
  }
};

}  // namespace s21

#endif
