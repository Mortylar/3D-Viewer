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

// TEST(Matrix4fTest, ) {
// }
