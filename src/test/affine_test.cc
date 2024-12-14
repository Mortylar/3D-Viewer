#include "common.h"

TEST(AffineTest, TestTranslation) {
  s21::Affine3D A;
  float dx = 1, dy = 2, dz = 3;
  s21::Matrix4f tar;
  tar(0, 3) = dx;
  tar(1, 3) = dy;
  tar(2, 3) = dz;

  s21::Matrix4f res = A.GetTranslation(dx, dy, dz);
  Compare(tar, res);
}

TEST(AffineTest, TestRotation) {
  s21::Affine3D A;
  const double k_PI = 3.141592653589793;
  const double epsilon = 1e-7;

  float dx = 0, dy = 0, dz = 0;

  s21::Matrix4f e;
  e.SetIdentity();

  s21::Matrix4f res = A.GetRotation(dx, dy, dz);
  Compare(res, e);

  dx = k_PI / 2;
  res = A.GetRotation(dx, dy, dz);

  e(1, 1) = 0.0;
  e(1, 2) = -1.0;
  e(2, 1) = 1.0;
  e(2, 2) = 0.0;

  Compare(e, res, epsilon);

  dy = k_PI / 2;
  res = A.GetRotation(dx, dy, dz);

  e.SetZero();
  e(0, 2) = 1;
  e(1, 0) = 1;
  e(2, 1) = 1;
  e(3, 3) = 1;

  Compare(e, res, epsilon);

  dz = k_PI / 2;
  res = A.GetRotation(dx, dy, dz);

  e.SetZero();
  e(0, 2) = 1;
  e(1, 1) = -1;
  e(2, 0) = 1;
  e(3, 3) = 1;

  Compare(e, res, epsilon);
}

TEST(AffineTest, TestScaling) {
  s21::Affine3D A;
  float dx = 1, dy = 2, dz = 3;
  s21::Matrix4f e;
  e(0, 0) = dx;
  e(1, 1) = dy;
  e(2, 2) = dz;

  s21::Matrix4f res = A.GetScaling(dx, dy, dz);
  Compare(e, res);
}

TEST(AffineTest, TestParralelProjection) {
  s21::Affine3D A;
  float dx = 0.02020202, dy = -1.020202;
  s21::Matrix4f e;
  e(2, 2) = dx;
  e(2, 3) = dy;

  s21::Matrix4f res = A.GetParralelProjection();
  Compare(e, res);
}

TEST(AffineTest, TestCentralProjection) {
  s21::Affine3D A;
  float dx = 1.02020202, dy = -2.0202019;
  float angle = 1.1917536;
  s21::Matrix4f e;
  e(0, 0) = angle;
  e(1, 1) = angle;
  e(2, 2) = dx;
  e(2, 3) = dy;
  e(3, 2) = 1.0;
  e(3, 3) = 0.0;

  s21::Matrix4f res = A.GetCentralProjection();
  Compare(e, res);
}

TEST(AffineTest, TestNormalize) {
  s21::Affine3D A;
  std::vector<float> v1{1, 2, 3};
  std::vector<float> v2{0.33333334, 0.66666669, 1};

  A.Normalize(v1);
  Compare(v1, v2, 3);
}

TEST(AffineTest, TestCentring) {
  s21::Affine3D A;
  std::vector<float> v1{1, 2, 3, 4, 5, 6};
  std::vector<float> v2{-1.5, -1.5, -1.5, -1.5, -1.5, -1.5};

  A.Centring(v1);
  Compare(v1, v2, 3);
}

TEST(AffineTest, TestDimension1) {
  s21::Affine3D A;
  std::vector<float> v{};

  EXPECT_THROW(A.Normalize(v), std::invalid_argument);
}

TEST(AffineTest, TestDimension2) {
  s21::Affine3D A;
  std::vector<float> v{1, 2, 3, 4};

  EXPECT_THROW(A.Centring(v), std::invalid_argument);
}

TEST(AffineTest, TestScalingNilpotency) {
  s21::Affine3D A;
  float dx = 1, dy = 2, dz = 0;

  EXPECT_THROW(A.GetScaling(dx, dy, dz), std::invalid_argument);
}
