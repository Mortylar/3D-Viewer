#include "common.h"
//#include "../model/affine_3d.h"

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

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << res(i, j) << "\t";
    }
    std::cout << std::endl;
  }
}

// TEST(AffineTest, Test) {
// }

// TEST(AffineTest, Test) {
// }

/*
TEST(AffineTest, Test7) {
  s21::Model A;
  std::vector<double> v {1, 2, 3};
  EXPECT_THROW(A.Scaling(v, 0, 1, 2), std::invalid_argument);
  EXPECT_THROW(A.Scaling(v, -1, 0, 1), std::invalid_argument);
  EXPECT_THROW(A.Scaling(v, -2, -1, 0), std::invalid_argument);
}
*/
