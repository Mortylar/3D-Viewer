#include <gtest/gtest.h>
#include "../model/model.h"
#include <vector>
#include<cmath>

#include "../model/affine_3d.h"
#include "../model/matrix_4f.h"

inline void Compare(const std::vector<float>& v1, const std::vector<float>& v2, size_t size) {
  for (size_t i = 0; i < size; ++i) { 
//    std::cout << "i="<< i << " " << v1[i] << "<-> " << v2[i] << std::endl;
    ASSERT_DOUBLE_EQ(v1.at(i), v2.at(i));
  }
}

inline void Compare(const float (&res)[16], const float (&orig)[16]) {
  for (size_t i = 0; i < 16; ++i) {
	  ASSERT_FLOAT_EQ(res[i], orig[i]);
	}
}


TEST(Matrix4fTest, DefaultConstructorTest) {
  s21::Matrix4f m;
	float res[4][4]{};
	res[0][0] = res[1][1] = res[2][2] = res[3][3] = 1;
	for (int i = 0; i < 4; ++i) {
	  for (int j = 0; j < 4; ++j) {
		  ASSERT_FLOAT_EQ(m(i,j), res[i][j]);
		}
	}
}

TEST(ParserTest, Test_1) {
  s21::Model A;
  const char* file_name = "files/simple_square";
  A.ReadFile(file_name);

  //==================vertexes=================//
  size_t orig_count = 8;
  EXPECT_EQ(orig_count, A.GetVertexCount());

  const std::vector<float>& vertex = A.GetVertex();
  const std::vector<float>& orig{1, -1, -1, 1, -1, 1,
                                  -1, -1, 1, -1, -1, -1,
                                  1, 1, -1, 1, 1, 1,
                                  -1, 1, 1, -1, 1, -1};
  Compare(vertex, orig, 3 * orig_count);

  //====================surfaces===================//
  orig_count = 12;
  EXPECT_EQ(orig_count, A.GetSurfacesCount());

  std::vector<unsigned int> orig_surfaces {2,3,4, 1,2,4,
                      8,7,6, 5,6,2, 6,7,3, 3,7,8, 1,4,8,
                      5,8,6, 1,5,2, 2,6,3, 4,3,8, 5,1,8};

    const std::vector<unsigned int> this_surface = A.GetSurface();
    EXPECT_EQ(this_surface.size(), orig_surfaces.size());
    for (size_t i = 0; i < this_surface.size(); ++i) {
     EXPECT_EQ(this_surface.at(i), orig_surfaces.at(i) - 1);
		 //g_print("\ns21 = %i <==> file = %i\n", orig_surfaces[i], this_surface[i]);
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
  s21::Affine3D A;
  float mat[16]{0};
	float dx = 1;
	float dy = 2;
	float dz = 3;
	float res[16] = {0,0,0,0,0,0,0,0,
	                 0,0,0,0,dx,dy,dz,0};

  A.Translation(mat, dx, dy, dz);
  Compare(mat, res);
}

TEST(AffineTest, Test2) {
  s21::Affine3D A;
	float mat[16]{};

}


//TEST(AffineTest, Test) {
//}

//TEST(AffineTest, Test) {
//}

/*
TEST(AffineTest, Test7) {
  s21::Model A;
  std::vector<double> v {1, 2, 3};
  EXPECT_THROW(A.Scaling(v, 0, 1, 2), std::invalid_argument);
  EXPECT_THROW(A.Scaling(v, -1, 0, 1), std::invalid_argument);
  EXPECT_THROW(A.Scaling(v, -2, -1, 0), std::invalid_argument);
}
*/

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

