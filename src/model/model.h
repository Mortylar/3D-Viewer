#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

//fasade

#include "affine_3d.h"
#include "parser.h"

namespace s21 {
class Model {
  public:
    Model() {
      affine_ = new Affine3D();
      parser_ = new Parser();
    };

    ~Model() {
      delete affine_;
      delete parser_;
    };

    void ReadFile(const char* file_name);

    void Translation(std::vector<float>& v, float dx, float dy, float dz);
    void Rotation(std::vector<float>& v, float, float, float);
    void Scaling(std::vector<float>& v, float, float, float);
    void Normalize(std::vector<float>& v);
    void Centring(std::vector<float>& v);

    size_t GetVertexCount();
    const std::vector<float>& GetVertex();

    size_t GetSurfacesCount();
    const std::vector<unsigned int>& GetSurface(size_t n);

  private:
    Affine3D* affine_;
    Parser* parser_;

    Model(const Model&);
    Model(Model&&);
    Model& operator=(const Model&);
};
}

#endif // SRC_MODEL_MODEL_H_
