#include "model.h"

#include <vector>

#include "figure.h"

void s21::Model::ReadFile(const char* file_name) {
  parser_->ParserMethod(file_name);
}

void s21::Model::Translation(std::vector<float>& v, float dx, float dy, float dz) {
  affine_->Translation(v, dx, dy, dz);
}

void s21::Model::Rotation(std::vector<float>& v, float x_rad, float y_rad, float z_rad) {
  affine_->Rotation(v, x_rad, y_rad, z_rad);
}

void s21::Model::Scaling(std::vector<float>& v, float x, float y, float z) {
  affine_->Scaling(v, x, y, z);
}

void s21::Model::Normalize(std::vector<float>& v) {
  affine_->Normalize(v);
}

void s21::Model::Centring(std::vector<float>& v) {
  affine_->Centring(v);
}


size_t s21::Model::GetVertexCount() {
  return s21::Figure::GetInstance()->GetVertexCount();
}

const std::vector<float>& s21::Model::GetVertex() { 
  return s21::Figure::GetInstance()->GetVertex();
}


size_t s21::Model::GetSurfacesCount() {
  return s21::Figure::GetInstance()->GetSurfacesCount();
}

const std::vector<unsigned int>& s21::Model::GetSurface(size_t n) {
  return s21::Figure::GetInstance()->GetSurface(n);
}

