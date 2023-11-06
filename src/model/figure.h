#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include<vector>
#include<cstddef>


//singleton
namespace s21 {

class Figure;

class FigureKiller {
  public:
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
    const double* GetVertexData();
    const std::vector<double>& GetVertex();
    void AddVertex(double x, double y, double z);

    size_t GetSurfacesCount();
    const std::vector<int>& GetSurface(size_t n);
    void AddSurface(const std::vector<int>& x);

    void Clear();

  private:
    static Figure* self_;
    static FigureKiller killer_;
    std::vector<double>* vertex_;
    std::vector<std::vector<int>>* surfaces_;

    Figure() {
      vertex_ = new std::vector<double>();
      surfaces_ = new std::vector<std::vector<int>>();
    }

    ~Figure() {
      delete vertex_;
      delete surfaces_;
    }

    Figure(const Figure&) = delete;
    Figure(const Figure&&) = delete;
    Figure operator=(Figure&) = delete;
    friend class FigureKiller;
};
}

#endif // SRC_MODEL_FIGURE_H_
