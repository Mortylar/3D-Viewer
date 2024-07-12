#include "common.h"








TEST(ParserTest, Test_1) {
  s21::Parser p;
	s21::Figure* f = s21::Figure::GetInstance();
  const char* file_name = "files/simple_square";
  p.ParserMethod(file_name);

  //==================vertexes=================//
  size_t orig_count = 8;
  EXPECT_EQ(orig_count, f->GetVertexCount());

  const std::vector<float>& vertex = f->GetVertex();
  const std::vector<float>& orig{1, -1, -1, 1, -1, 1,
                                  -1, -1, 1, -1, -1, -1,
                                  1, 1, -1, 1, 1, 1,
                                  -1, 1, 1, -1, 1, -1};
  Compare(vertex, orig, 3 * orig_count);

  //====================surfaces===================//
  orig_count = 12;
  EXPECT_EQ(orig_count, f->GetSurfacesCount());

  std::vector<unsigned int> orig_surfaces {1,2,3, 0,1,3,
                      7,6,5, 4,5,1, 5,6,2, 2,6,7, 0,3,7,
                      4,7,5, 0,4,1, 1,5,2, 3,2,7, 4,0,7};

  const std::vector<unsigned int> this_surface = f->GetVSurface();
  EXPECT_EQ(this_surface.size(), orig_surfaces.size());

  for (size_t i = 0; i < this_surface.size(); ++i) {
		Compare(this_surface, orig_surfaces, this_surface.size());
  }
}


TEST(ParserTest, Test2) {
  s21::Parser p;
  const char* file_name = "files/empty";
  EXPECT_THROW(p.ParserMethod(file_name), std::invalid_argument);
}

TEST(ParserTest, Test3) {
  s21::Parser p;
  const char* file_name = "no.file";
  EXPECT_THROW(p.ParserMethod(file_name), std::runtime_error);
}

TEST(ParserTest, Test4) {
  s21::Parser p;
  const char* file_name = "files/2d_file";
  EXPECT_THROW(p.ParserMethod(file_name), std::invalid_argument);
}

TEST(ParserTest, Test5) {
  s21::Parser p;
  const char* file_name = "files/no_vertex_file";
  EXPECT_THROW(p.ParserMethod(file_name), std::invalid_argument);
}

