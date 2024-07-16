#ifndef SRC_MODEL_OPENGL_MODEL_H_
#define SRC_MODEL_OPENGL_MODEL_H_

#include <epoxy/gl.h>
#include <gtk/gtk.h>

#include <vector>


#include "../libs/data.h"
#include "affine_3d.h"

namespace s21 {

class Buffer {
 public:
  Buffer() {
    vertex_ = 0;
    element_ = 0;
  }

  ~Buffer() { Clear(); }

  void CreateBuffer(std::vector<float>& v_data,
                    std::vector<unsigned int>& e_data);
  inline GLuint& GetVertexBuffer() { return vertex_; }
  inline GLuint& GetElementBuffer() { return element_; }
  void Clear();

 private:
  GLuint vertex_ = 0;
  GLuint element_ = 0;

  void CreateVertexBuffer(std::vector<float>& data);
  void CreateElementBuffer(std::vector<unsigned int>& data);
};

class Shader {
 public:
  Shader(){};

  ~Shader() { program_ = 0; }

  void LoadShader(const char* vertex_path, const char* fragment_path,
                  const char* geometry_path);
  inline GLuint GetProgram() { return program_; }

 private:
  GLuint program_ = 0;

  void InitShader(const char* vertex_path, const char* fragment_path,
                  const char* geometry_path);
  GLuint CreateShader(int type, const char* src);
	size_t GetFileLength(const char* file);
  char* LoadFile(const char* file_name);
};



class OpenGLModel {
 public:
  OpenGLModel() {
    vertex_ = new s21::Buffer();
  }

  ~OpenGLModel() {
    delete vertex_;
  }

  inline void SetGLArea(GtkGLArea* area) { area_ = area; }

  inline void ConnectData(s21::Data* data) { data_ = data; }

  void SetBuffer();
  void Draw();


 private:
  s21::Data* data_ = nullptr;
  GtkGLArea* area_ = nullptr;

  GLuint vao_ = 0;
  Shader point_shader;
  Shader line_shader;

  GLuint mvp_location_ = 0;
  GLuint color_location_ = 0;
  GLuint point_size_location_ = 0;

  Buffer* vertex_ = nullptr;

  void DrawFigure();
  void ResetField();
  void ConnectBuffers();
  void DrawPoints(Matrix4f& mvp);
  void DrawLines(Matrix4f& mvp);

  void InitShaders();
  void InitBuffer();

  void ComputeMVP(Matrix4f& mvp);
  void Rotation(Matrix4f& mvp);
  void Scaling(Matrix4f& mvp);
  void Translation(Matrix4f& mvp);
  void Projection(Matrix4f& mvp);
};
}  // namespace s21

#endif
