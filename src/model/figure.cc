#include "figure.h"


#include <iostream>
#include <vector>

s21::Figure* s21::Figure::self_ = nullptr;

//---------------------------vertexes--------------------------//

size_t s21::Figure::GetVertexCount() {
  return vertex_->size();
}

const double* s21::Figure::GetVertex() {
  return vertex_->data();
}

void s21::Figure::AddVertex(double x, double y, double z) {
  vertex_->push_back(x);
  vertex_->push_back(y);
  vertex_->push_back(z);
}


void s21::Figure::SwapVertex(std::vector<double>* x) {
  std::swap(vertex_, x);
}


//-------------------------surfaces----------------------------//

size_t s21::Figure::GetSurfacesCount() {
  return surfaces_->size();
}

const std::vector<double>& s21::Figure::GetSurface(size_t i) {
  return surfaces_->at(i);
}

void s21::Figure::AddSurface(const std::vector<double>& surface) {
  surfaces_->push_back(surface);
}





int main() {
  s21::Figure::GetInstance();
  std::vector<double> a{1,2,3};
  std::vector<double> b{1,2,3};
  std::vector<double> c{1,2,3};
  std::vector<double> d{1,2,3};
  std::vector<double> e{1,2,3};
  std::vector<double> f{1,2,3};
  s21::Figure::GetInstance()->AddSurface(a);
  s21::Figure::GetInstance()->AddSurface(b);
  s21::Figure::GetInstance()->AddSurface(c);
  s21::Figure::GetInstance()->AddSurface(d);
  s21::Figure::GetInstance()->AddSurface(e);
  s21::Figure::GetInstance()->AddSurface(f);



  s21::Figure::GetInstance()->AddVertex(1, 2, 3);
  size_t n = s21::Figure::GetInstance()->GetSurface(5).size();
  std::cout << "surfaces_count = " << n << std::endl;
  std::cout << "size = " << s21::Figure::GetInstance()->GetSurface(0).size() << std::endl;
  const double* arr = s21::Figure::GetInstance()->GetSurface(5).data();
  for (int i = 0; i < n; ++i) {
    std::cout << i << " <=> " << arr[i] << std::endl;
  }
  return 0;
}
