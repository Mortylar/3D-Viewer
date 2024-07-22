#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include <cstddef>
#include <iostream>
#include <vector>

namespace s21 {

class Figure;

class FigureKiller {
 public:
  ~FigureKiller();

  void Initialize(Figure *figure) { figure_ = figure; }

 private:
  Figure *figure_;
};

class Figure {
 public:
  static Figure *GetInstance() {
    if (!self_) {
      self_ = new Figure();
      killer_.Initialize(self_);
    }
    return self_;
  }

  size_t GetVertexCount();

  std::vector<float> &GetVertex();
  std::vector<float> &GetTextures();
  std::vector<float> &GetNormals();

  void AddVertex(float x, float y, float z);
  void AddTextures(float x, float y, float z);
  void AddNormals(float x, float y, float z);

  size_t GetSurfacesCount();

  const std::vector<unsigned int> &GetVSurface();
  const std::vector<unsigned int> &GetTSurface();
  const std::vector<unsigned int> &GetNSurface();

  const std::vector<unsigned int> &GetIndexOffset();

  void AddVSurface(const std::vector<unsigned int> &x);
  void AddTSurface(const std::vector<unsigned int> &x);
  void AddNSurface(const std::vector<unsigned int> &x);

  int GetEdgesCount();

  void Clear();
  void Reserve(size_t n);

 private:
  static Figure *self_;
  static FigureKiller killer_;

  std::vector<float> *vertex_;
  std::vector<float> *textures_;
  std::vector<float> *normals_;

  std::vector<unsigned int> *index_offset_;

  std::vector<unsigned int> *v_surfaces_;
  std::vector<unsigned int> *t_surfaces_;
  std::vector<unsigned int> *n_surfaces_;

  Figure() {
    vertex_ = new std::vector<float>();
    textures_ = new std::vector<float>();
    normals_ = new std::vector<float>();
    v_surfaces_ = new std::vector<unsigned int>();
    t_surfaces_ = new std::vector<unsigned int>();
    n_surfaces_ = new std::vector<unsigned int>();
    index_offset_ = new std::vector<unsigned int>();
  }

  ~Figure() {
    delete vertex_;
    delete textures_;
    delete normals_;
    delete v_surfaces_;
    delete t_surfaces_;
    delete n_surfaces_;
    delete index_offset_;
  }

  Figure(const Figure &) = delete;
  Figure(const Figure &&) = delete;
  Figure operator=(Figure &) = delete;
  friend class FigureKiller;
};
}  // namespace s21

#endif  // SRC_MODEL_FIGURE_H_
