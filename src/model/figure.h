#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include<vector>
#include<cstddef>

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
    std::vector<double>& GetVertex();
    void AddVertex(double x, double y, double z);
    void SwapVertex(std::vector<double>*);  //TODO is needed??

    size_t GetSurfacesCount();
    const std::vector<double>& GetSurface(size_t n);
    void AddSurface(const std::vector<double>& x);
    void SwapSurface(size_t pos, const std::vector<double>& surface);

  private:
    static Figure* self_;
    static FigureKiller killer_;
    std::vector<double>* vertex_;
    std::vector<std::vector<double>>* surfaces_;

    Figure() {
      vertex_ = new std::vector<double>();
      surfaces_ = new std::vector<std::vector<double>>();
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
