#include "figure.h"

#include <iostream>
#include <vector>

s21::Figure *s21::Figure::self_ = nullptr;
s21::FigureKiller s21::Figure::killer_;

s21::FigureKiller::~FigureKiller() { delete figure_; }

void s21::Figure::Clear() {
  vertex_->clear();
  textures_->clear();
  normals_->clear();

  v_surfaces_->clear();
  t_surfaces_->clear();
  n_surfaces_->clear();

  index_offset_->clear();
}

void s21::Figure::Reserve(size_t n) {
  vertex_->reserve(n);
  textures_->reserve(n);
  normals_->reserve(n);

  v_surfaces_->reserve(n);
  t_surfaces_->reserve(n);
  n_surfaces_->reserve(n);
}

//---------------------------vertexes--------------------------//

size_t s21::Figure::GetVertexCount() { return vertex_->size() / 3; }

std::vector<float> &s21::Figure::GetVertex() { return *vertex_; }

std::vector<float> &s21::Figure::GetTextures() { return *textures_; }

std::vector<float> &s21::Figure::GetNormals() { return *normals_; }

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

size_t s21::Figure::GetSurfacesCount() { return index_offset_->size(); }

int s21::Figure::GetEdgesCount() {
  return GetVertexCount() + GetSurfacesCount() - 2;
}

const std::vector<unsigned int> &s21::Figure::GetVSurface() {
  return *v_surfaces_;
}

const std::vector<unsigned int> &s21::Figure::GetTSurface() {
  return *t_surfaces_;
}

const std::vector<unsigned int> &s21::Figure::GetNSurface() {
  return *n_surfaces_;
}

const std::vector<unsigned int> &s21::Figure::GetIndexOffset() {
  return *index_offset_;
}

void s21::Figure::AddVSurface(const std::vector<unsigned int> &surface) {
  index_offset_->push_back(surface.size());
  for (size_t i = 0; i < surface.size(); ++i) {
    v_surfaces_->push_back(surface[i]);
  }
}

void s21::Figure::AddTSurface(const std::vector<unsigned int> &surface) {
  for (size_t i = 0; i < surface.size(); ++i) {
    t_surfaces_->push_back(surface[i]);
  }
}

void s21::Figure::AddNSurface(const std::vector<unsigned int> &surface) {
  for (size_t i = 0; i < surface.size(); ++i) {
    n_surfaces_->push_back(surface[i]);
  }
}
