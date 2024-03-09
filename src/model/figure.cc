#include "figure.h"


#include <iostream>
#include <vector>

s21::Figure* s21::Figure::self_ = nullptr;
s21::FigureKiller s21::Figure::killer_;

s21::FigureKiller::~FigureKiller() {
  delete figure_;
}

void s21::Figure::Clear() {
  vertex_->clear();
  surfaces_->clear();
}

//---------------------------vertexes--------------------------//

size_t s21::Figure::GetVertexCount() {
  return vertex_->size() / 3;
}

const std::vector<float>& s21::Figure::GetVertex() {
  return *vertex_;
}

//const float* s21::Figure::GetVertexData() {
//  return vertex_->data();
//}

void s21::Figure::AddVertex(float x, float y, float z) {
  vertex_->push_back(x);
  vertex_->push_back(y);
  vertex_->push_back(z);
}


//-------------------------surfaces----------------------------//

size_t s21::Figure::GetSurfacesCount() {
  return surfaces_->size();
}

const std::vector<int>& s21::Figure::GetSurface(size_t i) {
  return surfaces_->at(i);
}

void s21::Figure::AddSurface(const std::vector<int>& surface) {
  surfaces_->push_back(surface);
}

