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

int s21::Model::GetEdgesCount() {
  return s21::Figure::GetInstance()->GetEdgesCount();
}

size_t s21::Model::GetSurfacesCount() {
  return s21::Figure::GetInstance()->GetSurfacesCount();
}

void s21::Model::ConnectData(s21::Data *data) {
  opengl_model_->ConnectData(data);
}

void s21::Model::SetBuffers() { opengl_model_->SetBuffer(); }

void s21::Model::Draw() { opengl_model_->Draw(); }
