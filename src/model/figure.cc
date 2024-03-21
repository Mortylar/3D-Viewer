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
  textures_->clear();
  normals_->clear();

  v_surfaces_->clear();
  t_surfaces_->clear();
  n_surfaces_->clear();
}

//---------------------------vertexes--------------------------//

size_t s21::Figure::GetVertexCount() {
  return vertex_->size() / 3;
}

std::vector<float>& s21::Figure::GetVertex() {
  return *vertex_;
}

std::vector<float>& s21::Figure::GetTextures() {
  return *textures_;
}

std::vector<float>& s21::Figure::GetNormals() {
  return *normals_;
}


//const float* s21::Figure::GetVertexData() {
//  return vertex_->data();
//}

void s21::Figure::AddVertex(float x, float y, float z) {
  vertex_->push_back(x);
  vertex_->push_back(y);
  vertex_->push_back(z);
}

void s21::Figure::AddTextures(float x, float y, float z) {
  textures_->push_back(x);
  textures_->push_back(y);
  textures_->push_back(z);
}

void s21::Figure::AddNormals(float x, float y, float z) {
  normals_->push_back(x);
  normals_->push_back(y);
  normals_->push_back(z);
}


//-------------------------surfaces----------------------------//

size_t s21::Figure::GetSurfacesCount() {
  return v_surfaces_->size();
}

const std::vector<unsigned int>& s21::Figure::GetVSurface(size_t i) {
  return v_surfaces_->at(i);
}

const std::vector<unsigned int>& s21::Figure::GetTSurface(size_t i) {
  return t_surfaces_->at(i);
}

const std::vector<unsigned int>& s21::Figure::GetNSurface(size_t i) {
  return n_surfaces_->at(i);
}


void s21::Figure::AddVSurface(const std::vector<unsigned int>& surface) {
  v_surfaces_->push_back(surface);
}

void s21::Figure::AddTSurface(const std::vector<unsigned int>& surface) {
  t_surfaces_->push_back(surface);
}

void s21::Figure::AddNSurface(const std::vector<unsigned int>& surface) {
  n_surfaces_->push_back(surface);
}
