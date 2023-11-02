#include "model.h"

#include <vector>

#include "figure.h"

void s21::Model::ReadFile(const char* file_name) {
  parser_->ParserMethod(file_name);
}

void s21::Model::Translation(std::vector<double>& v, double dx, double dy, double dz) {
  affine_->Translation(v, dx, dy, dz);
}

void s21::Model::Rotation(std::vector<double>& v, double x_rad, double y_rad, double z_rad) {
  affine_->Rotation(v, x_rad, y_rad, z_rad);
}

void s21::Model::Scaling(std::vector<double>& v, double x, double y, double z) {
  affine_->Scaling(v, x, y, z);
}

void s21::Model::Normalize(std::vector<double>& v) {
  affine_->Normalize(v);
}

size_t s21::Model::GetVertexCount() {
  return s21::Figure::GetInstance()->GetVertexCount();
}

const std::vector<double>& s21::Model::GetVertex() { 
  return s21::Figure::GetInstance()->GetVertex();
}

const double* s21::Model::GetVertexData() {
  return s21::Figure::GetInstance()->GetVertexData();
}


size_t s21::Model::GetSurfacesCount() {
  return s21::Figure::GetInstance()->GetSurfacesCount();
}

const std::vector<int>& s21::Model::GetSurface(size_t n) {
  return s21::Figure::GetInstance()->GetSurface(n);
}

