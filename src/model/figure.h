#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include<vector>
#include<cstddef>
#include<iostream>

//singleton
namespace s21 {

class Figure;

class FigureKiller {
  public:
//   FigureKiller();
  ~FigureKiller();

  void Initialize(Figure* figure) {
    figure_ = figure;
  }
  private:
    Figure* figure_;
};


class Figure {
  public:
    static Figure* GetInstance() {
      if (!self_) {
        self_ = new Figure();
        killer_.Initialize(self_);
      }
      return self_;
    }

    size_t GetVertexCount();
    
    std::vector<float>& GetVertex();
    std::vector<float>& GetTextures();
    std::vector<float>& GetNormals();

    void AddVertex(float x, float y, float z); 
    void AddTextures(float x, float y, float z);
    void AddNormals(float x, float y, float z);

    size_t GetSurfacesCount();

    const std::vector<unsigned int>& GetVSurface(size_t n);
    const std::vector<unsigned int>& GetTSurface(size_t n);
    const std::vector<unsigned int>& GetNSurface(size_t n);

    void AddVSurface(const std::vector<unsigned int>& x);
    void AddTSurface(const std::vector<unsigned int>& x);
    void AddNSurface(const std::vector<unsigned int>& x);

    void Clear();

  private:
    static Figure* self_;
    static FigureKiller killer_;
    std::vector<float>* vertex_;
    std::vector<float>* textures_;
    std::vector<float>* normals_;
    std::vector<std::vector<unsigned int>>* v_surfaces_; 
    std::vector<std::vector<unsigned int>>* t_surfaces_;
    std::vector<std::vector<unsigned int>>* n_surfaces_;

    Figure() {
      vertex_ = new std::vector<float>();
      textures_ = new std::vector<float>();
      normals_ = new std::vector<float>();
      v_surfaces_ = new std::vector<std::vector<unsigned int>>(); 
      t_surfaces_ = new std::vector<std::vector<unsigned int>>();
      n_surfaces_ = new std::vector<std::vector<unsigned int>>();
    }

    ~Figure() {
      delete vertex_;
      delete textures_;
      delete normals_;
      delete v_surfaces_;
      delete t_surfaces_;
      delete n_surfaces_;
    }

    Figure(const Figure&) = delete;
    Figure(const Figure&&) = delete;
    Figure operator=(Figure&) = delete;
    friend class FigureKiller;
};
}

#endif // SRC_MODEL_FIGURE_H_
