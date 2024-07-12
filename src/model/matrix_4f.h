#ifndef SRC_MODEL_MATRIX_4F_H_
#define SRC_MODEL_MATRIX_4F_H_

#include <cstring>
#include <iostream>

namespace s21 {

class Matrix4f {
 public:
  Matrix4f();

  Matrix4f(const Matrix4f& other);
  Matrix4f(Matrix4f&& other);

  Matrix4f& operator=(const Matrix4f& other);
  Matrix4f& operator=(Matrix4f&& other);

  ~Matrix4f();

  Matrix4f& operator+=(Matrix4f& other);
  Matrix4f& operator-=(Matrix4f& other);
  Matrix4f operator+(Matrix4f& other);
  Matrix4f operator-(Matrix4f& other);
  Matrix4f& operator*=(Matrix4f& other);
  Matrix4f operator*(Matrix4f& other);
  Matrix4f& operator*(float x);
  Matrix4f& operator*=(Matrix4f other);

  float& operator()(int i, int j);

  Matrix4f& SetIdentity();
  Matrix4f& SetZero();

 private:
  static const int size_{4};
  float data_[size_][size_];

  void Clear();
  void SetInit();
};
}  // namespace s21

#endif
