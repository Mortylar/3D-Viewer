#include <gtest/gtest.h>
#include "../model/model.h"
#include <vector>

TEST(ParserTest, Test_1) {
  s21::Model A;
  const char* file_name = "simple_square";
  A.ReadFile(file_name);

  //==================vertexes=================//
  size_t orig_count = 8;
  EXPECT_EQ(orig_count, A.GetVertexCount());

  const std::vector<double>& vertex = A.GetVertex();
  const std::vector<double>& orig{1, -1, -1, 1, -1, 1,
                                  -1, -1, 1, -1, -1, -1,
                                  1, 1, -1, 1, 1, 1,
                                  -1, 1, 1, -1, 1, -1};
  for (size_t i = 0; i < 3* orig_count; ++i) {
    EXPECT_EQ(vertex.at(i), orig.at(i));
  }

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
  const char* file_name = "empty";
  EXPECT_THROW(A.ReadFile(file_name), std::invalid_argument);
}

TEST(ParserTest, Test3) {
  s21::Model A;
  const char* file_name = "no.file";
  EXPECT_THROW(A.ReadFile(file_name), std::runtime_error);
}

TEST(ParserTest, Test4) {
  s21::Model A;
  const char* file_name = "2d_file";
  EXPECT_THROW(A.ReadFile(file_name), std::invalid_argument);
}


TEST(ParserTest, Test5) {
  s21::Model A;
  const char* file_name = "no_vertex_file";
  EXPECT_THROW(A.ReadFile(file_name), std::invalid_argument);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  //free(__cxxabiv1::__cxa_get_globals());
  return result;
}

