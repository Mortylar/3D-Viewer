#include "common.h"








/*
TEST(AffineTest, TestTranslation) {
  s21::Affine3D A;
	float dx = 1, dy = 2, dz = 3;
	s21::Matrix4f tar;
	tar(0,3) = dx;
	tar(1,3) = dy;
	tar(2,3) = dz;

	s21::Matrix4f res = A.GetTranslation(dx, dy, dz);
	CompareMatrix(tar, res);
}

TEST(AffineTest, TestRotation) {
  s21::Affine3D A;
	float dx = 0, dy = 0, dz = 0;

	s21::Matrix4f e;
	e.SetIdentity();

	s21::Matrix4f res = A.GetRotation(dx, dy,dz);

	CompareMatrix(res, e);

}*/


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

/*
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
*/

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

