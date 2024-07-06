#include "model.h"

#include <vector>

#include "figure.h"

void s21::Model::ReadFile(const char *file_name) {
  parser_->ParserMethod(file_name);
  affine_->Normalize(s21::Figure::GetInstance()->GetVertex());
  affine_->Centring(s21::Figure::GetInstance()->GetVertex());
}


size_t s21::Model::GetVertexCount() {
  return s21::Figure::GetInstance()->GetVertexCount();
}

/*
const std::vector<float> &s21::Model::GetVertex() {
  return s21::Figure::GetInstance()->GetVertex();
}*/

size_t s21::Model::GetSurfacesCount() {
  return s21::Figure::GetInstance()->GetSurfacesCount();
}

/*const std::vector<unsigned int> &s21::Model::GetSurface(size_t n) {
  return s21::Figure::GetInstance()->GetVSurface(n);
}*/

void s21::Model::SetGLArea(GtkGLArea *area) { opengl_model_->SetGLArea(area); }

void s21::Model::ConnectData(s21::Data *data) {
  opengl_model_->ConnectData(data);
}

void s21::Model::SetBuffers() { opengl_model_->SetBuffer(); }

void s21::Model::Draw() { opengl_model_->Draw(); }

void s21::Model::SavePicture(size_t width, size_t height, const char* file_name, const char* type) {
  opengl_model_->SavePicture(width, height, file_name, type);
}

