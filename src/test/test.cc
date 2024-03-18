#include <gtest/gtest.h>
#include "../model/model.h"
#include <vector>
#include<cmath>


inline void Compare(const std::vector<double>& v1, const std::vector<double>& v2, size_t size) {
  for (size_t i = 0; i < size; ++i) { 
//    std::cout << "i="<< i << " " << v1[i] << "<-> " << v2[i] << std::endl;
    ASSERT_DOUBLE_EQ(v1.at(i), v2.at(i));
  }
}


TEST(ParserTest, Test_1) {
  s21::Model A;
  const char* file_name = "files/simple_square";
  A.ReadFile(file_name);

  //==================vertexes=================//
  size_t orig_count = 8;
  EXPECT_EQ(orig_count, A.GetVertexCount());

  const std::vector<double>& vertex = A.GetVertex();
  const std::vector<double>& orig{1, -1, -1, 1, -1, 1,
                                  -1, -1, 1, -1, -1, -1,
                                  1, 1, -1, 1, 1, 1,
                                  -1, 1, 1, -1, 1, -1};
  Compare(vertex, orig, 3 * orig_count);

  //====================surfaces===================//
  orig_count = 12;
  EXPECT_EQ(orig_count, A.GetSurfacesCount());

  std::vector<std::vector<int>> orig_surfaces {{2,3,4}, {1,2,4},
                    {8,7,6}, {5,6,2}, {6,7,3}, {3,7,8}, {1,4,8},
                    {5,8,6}, {1,5,2}, {2,6,3}, {4,3,8}, {5,1,8}};

  for (size_t i = 0; i < orig_count; ++i) {
    const std::vector<int> this_surface = A.GetSurface(i);
    EXPECT_EQ(this_surface.size(), orig_surfaces[i].size());
    for (size_t j = 0; j < this_surface.size(); ++j) {
      EXPECT_EQ(this_surface.at(j), orig_surfaces[i].at(j));
    }
  }
}

TEST(ParserTest, Test2) {
  s21::Model A;
  const char* file_name = "files/empty";
  EXPECT_THROW(A.ReadFile(file_name), std::invalid_argument);
}

TEST(ParserTest, Test3) {
  s21::Model A;
  const char* file_name = "no.file";
  EXPECT_THROW(A.ReadFile(file_name), std::runtime_error);
}

TEST(ParserTest, Test4) {
  s21::Model A;
  const char* file_name = "files/2d_file";
  EXPECT_THROW(A.ReadFile(file_name), std::invalid_argument);
}


TEST(ParserTest, Test5) {
  s21::Model A;
  const char* file_name = "files/no_vertex_file";
  EXPECT_THROW(A.ReadFile(file_name), std::invalid_argument);
}

TEST(AffineTest, Test1) {
  s21::Model A;
  std::vector<double> v {1, 1, 1};
  std::vector<double> sample {1,2,3};

  A.Translation(v, 0, 1, 2);
  Compare(v, sample, v.size());
}


TEST(AffineTest, Test2) {
  s21::Model A;
  std::vector<double> v {1, 1, 1};
  std::vector<double> sample {1, 1, -1};

  A.Rotation(v, M_PI/2, 0, 0);
//  std::cout << std::fixed << std::setprecision(19);
//  for(int i = 0; i < 3; ++i) {
//    std::cout << v[i] << " ";
//  }
//  std::cout << std::endl;
  Compare(v, sample, v.size());

  sample = {1, 1, 1};
  A.Rotation(v, 0, M_PI/2, 0);
  Compare(v, sample, v.size());

  sample = {1, -1, 1};
  A.Rotation(v, 0, 0, M_PI/2);
  Compare(v, sample, v.size());

  v = {1, 1, 1};
  A.Rotation(v, M_PI/2, M_PI/2, M_PI/2);
  Compare(v, sample, v.size());
}


TEST(AffineTest, Test3) {
  s21::Model A;
  std::vector<double> v {1, 1, 1};
  std::vector<double> sample {1,2,3};

  A.Scaling(v, 1, 2, 3);
  Compare(v, sample, v.size());
}

TEST(AffineTest, Test4) {
  s21::Model A;
  std::vector<double> v {1, 2, 3};
  std::vector<double> sample {1.0/3, 2.0/3, 1.0};

  A.Normalize(v);
  Compare(v, sample, v.size());

  v = {0.1, 0.2, 0.3};
  A.Normalize(v);
  Compare(v, sample, v.size());
}

TEST(AffineTest, Test5) {
  s21::Model A;
  std::vector<double> v {1, 0, -1,
                         -1, 2, 3,
                         0, 1, 0 };
  std::vector<double> sample {1, -1, -2,
                              -1, 1, 2,
                               0, 0, -1 };

  A.Centring(v);
  Compare(v, sample, v.size());

  sample = {0.5, -0.5, -1,
            -0.5, 0.5, 1,
            0, 0, -0.5 };
  A.Normalize(v);
  Compare(v, sample, v.size());
}

TEST(AffineTest, Test6) {
  s21::Model A;
  std::vector<double> v {1, 2, 3, 4};
  EXPECT_THROW(A.Translation(v, 1, 2, 3), std::invalid_argument);
  v.clear(); 
  EXPECT_THROW(A.Rotation(v, 0, 1, 2), std::invalid_argument);
}

TEST(AffineTest, Test7) {
  s21::Model A;
  std::vector<double> v {1, 2, 3};
  EXPECT_THROW(A.Scaling(v, 0, 1, 2), std::invalid_argument);
  EXPECT_THROW(A.Scaling(v, -1, 0, 1), std::invalid_argument);
  EXPECT_THROW(A.Scaling(v, -2, -1, 0), std::invalid_argument);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

