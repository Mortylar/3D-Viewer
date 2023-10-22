#ifndef SRC_MODEL_FIGURE_H_
#define SRC_MODEL_FIGURE_H_

#include<vector>

namespace s21 {
class Figure {
  public:
    static Figure* GetInstance() {
	  return self_ ? (self_) : (self_ = new Figure());
	}

	size_t GetVertexCount();
	const double* GetVertex();
	void AddVertex(double x, double y, double z);
    void SwapVertex(std::vector<double>*);  //TODO is needed??

	size_t GetSurfacesCount();
    const std::vector<double>& GetSurface(size_t n);
	void AddSurface(const std::vector<double>& x);
    void SwapSurface(size_t pos, const std::vector<double>& surface);





  private:
    static Figure* self_;
	std::vector<double>* vertex_;
	std::vector<std::vector<double>>* surfaces_;

	Figure() {
      vertex_ = new std::vector<double>();
	  surfaces_ = new std::vector<std::vector<double>>();
	}

	~Figure() {
      delete self_;
	  delete vertex_;
	  delete surfaces_;
	}

	Figure(const Figure&) = delete;
	Figure(const Figure&&) = delete;
	Figure operator=(Figure&) = delete;
};

//Figure* Figure::self_ = nullptr;
}

#endif // SRC_MODEL_FIGURE_H_
