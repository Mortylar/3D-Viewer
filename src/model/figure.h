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
    const std::vector<float>& GetVertex();
    void AddVertex(float x, float y, float z);

    size_t GetSurfacesCount();
    const std::vector<unsigned int>& GetSurface(size_t n);
    void AddSurface(const std::vector<unsigned int>& x);

    void Clear();

  private:
    static Figure* self_;
    static FigureKiller killer_;
    std::vector<float>* vertex_;
    std::vector<std::vector<unsigned int>>* surfaces_;

    Figure() {
      vertex_ = new std::vector<float>();
      surfaces_ = new std::vector<std::vector<unsigned int>>();
    }

    ~Figure() {
      delete vertex_;
      delete surfaces_;
      std::cout << "\n~Figure()\n" << std::endl;
    }

    Figure(const Figure&) = delete;
    Figure(const Figure&&) = delete;
    Figure operator=(Figure&) = delete;
    friend class FigureKiller;
};
}

#endif // SRC_MODEL_FIGURE_H_
