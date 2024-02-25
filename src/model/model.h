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

    void Translation(std::vector<double>& v, double dx, double dy, double dz);
    void Rotation(std::vector<double>& v, double, double, double);
    void Scaling(std::vector<double>& v, double, double, double);
    void Normalize(std::vector<double>& v);
    void Centring(std::vector<double>& v);

    size_t GetVertexCount();
    const std::vector<double>& GetVertex();

    size_t GetSurfacesCount();
    const std::vector<int>& GetSurface(size_t n);

  private:
    Affine3D* affine_;
    Parser* parser_;

    Model(const Model&);
    Model(Model&&);
    Model& operator=(const Model&);
};
}

#endif // SRC_MODEL_MODEL_H_
