#include "matrix_4f.h"

s21::Matrix4f::Matrix4f() {
  Clear();
  SetInit();
}

s21::Matrix4f::Matrix4f(const Matrix4f& other) {
  if (this != &other) {
    std::memcpy(data_, other.data_, size_ * size_ * sizeof(float));
  } else {
    Clear();
    SetInit();
  }
}

s21::Matrix4f::Matrix4f(Matrix4f&& other) {
  if (this != &other) {
    std::swap(data_, other.data_);
  } else {
    Clear();
    SetInit();
  }
}

s21::Matrix4f& s21::Matrix4f::operator=(const Matrix4f& other) {
  if (this != &other) {
    std::memcpy(data_, other.data_, size_ * size_ * sizeof(float));
  }
  return *this;
}

s21::Matrix4f& s21::Matrix4f::operator=(Matrix4f&& other) {
  if (this != &other) {
    std::swap(data_, other.data_);
  }
  return *this;
}

s21::Matrix4f::~Matrix4f() { Clear(); }

s21::Matrix4f& s21::Matrix4f::operator+=(const Matrix4f& other) {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      data_[i][j] += other.data_[i][j];
    }
  }
  return *this;
}

s21::Matrix4f& s21::Matrix4f::operator-=(const Matrix4f& other) {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      data_[i][j] -= other.data_[i][j];
    }
  }
  return *this;
}

s21::Matrix4f s21::Matrix4f::operator+(const Matrix4f& other) {
  Matrix4f result(*this);
  return result += other;
}

s21::Matrix4f s21::Matrix4f::operator-(const Matrix4f& other) {
  Matrix4f result(*this);
  return result -= other;
}

s21::Matrix4f s21::Matrix4f::operator*(const Matrix4f& other) {
  Matrix4f result;
  result.Clear();
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      for (int k = 0; k < size_; ++k) {
        result.data_[i][j] += (this->data_[i][k] * other.data_[k][j]);
      }
    }
  }
  return result;
}

s21::Matrix4f& s21::Matrix4f::operator*(float x) {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      this->data_[i][j] *= x;
    }
  }
  return *this;
}

s21::Matrix4f& s21::Matrix4f::operator*=(Matrix4f other) {
  *this = (*this) * other;
  return *this;
}

float& s21::Matrix4f::operator()(int i, int j) { return data_[i][j]; }

s21::Matrix4f& s21::Matrix4f::SetIdentity() {
  Clear();
  SetInit();
  return *this;
}

s21::Matrix4f& s21::Matrix4f::SetZero() {
  Clear();
  return *this;
}

void s21::Matrix4f::Clear() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      data_[i][j] = 0.0f;
    }
  }
}

void s21::Matrix4f::SetInit() {
  data_[0][0] = 1.0f;
  data_[1][1] = 1.0f;
  data_[2][2] = 1.0f;
  data_[3][3] = 1.0f;
}
