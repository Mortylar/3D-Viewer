#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

// fasade

#include "affine_3d.h"
#include "opengl_model.h"
#include "parser.h"

namespace s21 {
class Model {
public:
  Model() {
    affine_ = new Affine3D();
    parser_ = new Parser();
    opengl_model_ = new OpenGLModel();
  };

  ~Model() {
    delete affine_;
    delete parser_;
    delete opengl_model_;
  };

  void ReadFile(const char *file_name);

  // void Translation(std::vector<float>& v, float dx, float dy, float dz);
  // void Rotation(std::vector<float>& v, float, float, float);
  // void Scaling(std::vector<float>& v, float, float, float);
  // void Normalize(std::vector<float>& v);
  // void Centring(std::vector<float>& v);

  size_t GetVertexCount();
  const std::vector<float> &GetVertex();

  size_t GetSurfacesCount();
  const std::vector<unsigned int> &GetSurface(size_t n);

  void SetGLArea(GtkGLArea *area);   // TODO
  void ConnectData(s21::Data *data); // TODO
  void SetBuffers();                 // TODO
  void Draw();                       // TODO
  void SavePicture(size_t width, size_t height);

private:
  Affine3D *affine_;
  Parser *parser_;
  OpenGLModel *opengl_model_;

  Model(const Model &);
  Model(Model &&);
  Model &operator=(const Model &);
};
} // namespace s21

#endif // SRC_MODEL_MODEL_H_
