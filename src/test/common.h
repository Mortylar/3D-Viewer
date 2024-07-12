#ifndef SRC_TEST_COMMON_H_
#define SRC_TEST_COMMON_H_

#include <gtest/gtest.h>
#include <vector>
#include<cmath>

#include "../model/affine_3d.h"
#include "../model/matrix_4f.h"
#include "../model/figure.h"
#include "../model/parser.h"

inline void Compare(const std::vector<float>& v1, const std::vector<float>& v2, size_t size) {
  for (size_t i = 0; i < size; ++i) { 
    ASSERT_FLOAT_EQ(v1.at(i), v2.at(i));
  }
}

inline void Compare(const std::vector<unsigned int>& v1,
                    const std::vector<unsigned int>& v2, size_t size) {
  for (size_t i = 0; i < size; ++i) { 
    ASSERT_EQ(v1.at(i), v2.at(i));
  }
}

inline void Compare(const float (&res)[16], const float (&orig)[16]) {
  for (size_t i = 0; i < 16; ++i) {
	  ASSERT_FLOAT_EQ(res[i], orig[i]);
	}
}

inline void Compare(s21::Matrix4f &first, s21::Matrix4f &second) {
  for (int i = 0; i < 4; ++i) {
	  for (int j = 0; j < 4; ++j) {
		  ASSERT_FLOAT_EQ(first(i,j), second(i,j));
		}
	}
}


inline void Compare(s21::Matrix4f &first, s21::Matrix4f &second, float epsilon) {
  for (int i = 0; i < 4; ++i) {
	  for (int j = 0; j < 4; ++j) {
		  ASSERT_NEAR(first(i,j), second(i,j), std::abs(epsilon));
		}
	}
}

#endif
