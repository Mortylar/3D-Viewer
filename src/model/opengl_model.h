#ifndef SRC_MODEL_OPENGL_MODEL_H_
#define SRC_MODEL_OPENGL_MODEL_H_

#include <epoxy/gl.h>
#include <gtk/gtk.h>

#include <vector>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
//#include <stb/stb_image_write.h>
#include "../stb/stb_image_write.h"
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
//#include <stb/stb_image.h>
#include "../stb/stb_image.h"
#endif

#include "../libs/data.h"
#include "affine_3d.h"
//#include "figure.h" //TODO try to remove

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
  char* LoadFile(const char* file_name);
};

class Texture {
 public:
  Texture(){};

  ~Texture(){};

  inline GLuint GetID() { return id_; }
  void Create(const std::string& file_name);

 private:
  GLuint id_ = 0;
  int width_ = 0;
  int height_ = 0;
  int color_mod_ = 0;
  std::string file_;

  void SamplerInit();
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

  inline void SetGLArea(GtkGLArea* area) { area_ = area; }

  inline void ConnectData(s21::Data* data) { data_ = data; }

  void SetBuffer();
  void LoadTexture(std::string& file);
  void Draw();

  unsigned int* Mirroring(size_t width, size_t height, unsigned int* data);

  void SavePicture(size_t m_width, size_t m_height, const char* file_name,
                   const char* type);

 private:
  s21::Data* data_ = nullptr;
  GtkGLArea* area_ = nullptr;

  GLuint vao_ = 0;
  Texture texture_image_;
  Shader point_shader;
  Shader line_shader;
  Shader texture_shader;

  GLuint mvp_location_ = 0;
  GLuint color_location_ = 0;
  GLuint point_size_location_ = 0;

  Buffer* vertex_ = nullptr;
  Buffer* texture_ = nullptr;
  Buffer* normals_ = nullptr;

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
