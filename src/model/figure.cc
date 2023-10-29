#include "figure.h"


#include <iostream>
#include <vector>

s21::Figure* s21::Figure::self_ = nullptr;
s21::FigureKiller s21::Figure::killer_;

s21::FigureKiller::~FigureKiller() {
  delete figure_;
}

//---------------------------vertexes--------------------------//

size_t s21::Figure::GetVertexCount() {
  return vertex_->size() / 3;
}

std::vector<double>& s21::Figure::GetVertex() {
  return *vertex_;
}

const double* s21::Figure::GetVertexData() {
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

const std::vector<int>& s21::Figure::GetSurface(size_t i) {
  return surfaces_->at(i);
}

void s21::Figure::AddSurface(const std::vector<int>& surface) {
  surfaces_->push_back(surface);
}

