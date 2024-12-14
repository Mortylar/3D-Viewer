#include "common.h"

TEST(Matrix4fTest, DefaultConstructorTest) {
  s21::Matrix4f m;
  float res[4][4]{};
  res[0][0] = res[1][1] = res[2][2] = res[3][3] = 1;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_FLOAT_EQ(m(i, j), res[i][j]);
    }
  }
}

TEST(Matrix4fTest, SetIdentityTest) {
  s21::Matrix4f e;
  e.SetIdentity();

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (i == j) {
        ASSERT_FLOAT_EQ(e(i, j), 1.0);
      } else {
        ASSERT_FLOAT_EQ(e(i, j), 0.0);
      }
    }
  }
}

TEST(Matrix4fTest, SetZeroTest) {
  s21::Matrix4f zero;
  zero.SetZero();

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_FLOAT_EQ(zero(i, j), 0.0);
    }
  }
}

TEST(Matrix4fTest, CopyConstructorTest) {
  s21::Matrix4f e;
  e.SetIdentity();

  s21::Matrix4f m = m;

  Compare(m, e);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      m(i, j) = i * j + i + j;
    }
  }
  s21::Matrix4f other = m;

  Compare(m, other);
}

TEST(Matrix4fTest, MoveConstructorTest) {
  s21::Matrix4f e;
  e.SetIdentity();

  s21::Matrix4f m = std::move(m);

  Compare(m, e);

  s21::Matrix4f other = std::move(m);

  Compare(other, e);
}

TEST(Matrix4fTest, CopyAssignmentOperator) {
  s21::Matrix4f e;
  e.SetIdentity();

  s21::Matrix4f m;

  Compare(m, e);

  m = m;

  Compare(m, e);

  s21::Matrix4f other;
  other = m;

  Compare(m, other);
  Compare(e, other);
}

TEST(Matrix4fTest, MoveAssignmentOperator) {
  s21::Matrix4f e;
  e.SetIdentity();

  s21::Matrix4f m;

  Compare(m, e);

  m = std::move(m);

  Compare(m, e);

  s21::Matrix4f other;
  other = std::move(m);

  Compare(e, other);
}

TEST(Matrix4fTest, SumAssignmentOperator) {
  s21::Matrix4f e;
  s21::Matrix4f m;

  Compare(m, e);

  s21::Matrix4f other;
  other = e + m;

  e += m;

  Compare(e, other);
}

TEST(Matrix4fTest, SubAssignmentOperator) {
  s21::Matrix4f e;
  s21::Matrix4f m;

  Compare(m, e);

  s21::Matrix4f other;
  other = e - m;

  e -= m;

  Compare(e, other);
}

TEST(Matrix4fTest, MulMatrix) {
  s21::Matrix4f e;
  s21::Matrix4f m;

  Compare(m, e);

  e(0, 0) = 2.0f;
  e(1, 1) = 2.0f;
  e(2, 2) = 2.0f;
  e(3, 3) = 2.0f;

  m(0, 0) = 1.0f;
  m(1, 1) = 2.0f;
  m(2, 2) = 3.0f;
  m(3, 3) = 4.0f;

  s21::Matrix4f result;
  result(0, 0) = 2.0f;
  result(1, 1) = 4.0f;
  result(2, 2) = 6.0f;
  result(3, 3) = 8.0f;

  s21::Matrix4f other;
  other = e * m;

  Compare(result, other);
}

TEST(Matrix4fTest, MulNumMatrix) {
  s21::Matrix4f e;
  float num = 2.0f;

  s21::Matrix4f result;
  result(0, 0) = 2.0f;
  result(1, 1) = 2.0f;
  result(2, 2) = 2.0f;
  result(3, 3) = 2.0f;

  s21::Matrix4f other;
  other = e * num;

  Compare(result, other);
}

TEST(Matrix4fTest, MulAssignmentOperator) {
  s21::Matrix4f e;
  s21::Matrix4f m;

  Compare(m, e);

  m(1, 1) = 2;
  m(2, 2) = 3;

  s21::Matrix4f other;
  other = e * m;

  e *= m;

  Compare(e, other);
}
