#include "affine_3d.h"
#include "figure.h"

#include <iostream>

#include <cmath>

void Print() {
  size_t size = s21::Figure::GetInstance()->GetVertexCount();
  std::cout << "size = " << size << std::endl;
  for (size_t i = 0; i < size; ++i) {
    std::cout << i << " <=> " << s21::Figure::GetInstance()->GetVertex()[i] << std::endl;
  }
  std::cout<<std::endl;
}


int main() {
  s21::Affine3D A;
  double p = M_PI;
  s21::Figure::GetInstance()->AddVertex(1,2,3);
  std::vector<double>& v = s21::Figure::GetInstance()->GetVertex();
  A.Translation(v, 1, 2, 3);
  Print();
  A.Rotation(v, p,p,0);
  Print();
  A.Scaling(v, 0.01, 10, 10.10);
  Print();
  A.Normalize(v);
  Print();
  return 0;
}
