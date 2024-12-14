#include "../model/figure.h"

#include "common.h"

TEST(FigureTest, VertexTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  float x = 1, y = 2, z = 3;

  f->AddVertex(x, y, z);

  ASSERT_EQ(f->GetVertexCount(), 1);
  ASSERT_EQ(f->GetVertex().size(), 3);

  ASSERT_FLOAT_EQ(f->GetVertex()[0], x);
  ASSERT_FLOAT_EQ(f->GetVertex()[1], y);
  ASSERT_FLOAT_EQ(f->GetVertex()[2], z);
  f->Clear();

  ASSERT_EQ(f->GetVertexCount(), 0);
}

TEST(FigureTest, TextureTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  float x = 1, y = 2, z = 3;

  f->AddTextures(x, y, z);

  ASSERT_EQ(f->GetVertexCount(), 0);

  ASSERT_FLOAT_EQ(f->GetTextures()[0], x);
  ASSERT_FLOAT_EQ(f->GetTextures()[1], y);
  ASSERT_FLOAT_EQ(f->GetTextures()[2], z);

  f->Clear();

  ASSERT_EQ(f->GetTextures().size(), 0);
}

TEST(FigureTest, NormalsTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  float x = 1, y = 2, z = 3;

  f->AddNormals(x, y, z);

  ASSERT_EQ(f->GetNormals().size(), 3);

  ASSERT_FLOAT_EQ(f->GetNormals()[0], x);
  ASSERT_FLOAT_EQ(f->GetNormals()[1], y);
  ASSERT_FLOAT_EQ(f->GetNormals()[2], z);

  f->Clear();

  ASSERT_EQ(f->GetNormals().size(), 0);
}

TEST(FigureTest, VertexIndexesTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  std::vector<unsigned int> v1{0, 1, 2};
  std::vector<unsigned int> v2{3, 4, 5};

  f->AddVSurface(v1);

  EXPECT_EQ(f->GetSurfacesCount(), 1);

  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], f->GetVSurface()[i]);
  }

  f->AddVSurface(v2);

  EXPECT_EQ(f->GetSurfacesCount(), 2);

  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], f->GetVSurface()[i]);
  }

  for (int i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], f->GetVSurface()[i + v1.size()]);
  }
}

TEST(FigureTest, TexturesIndexesTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  std::vector<unsigned int> v1{0, 1, 2};
  std::vector<unsigned int> v2{3, 4, 5};

  f->AddTSurface(v1);

  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], f->GetTSurface()[i]);
  }

  f->AddTSurface(v2);

  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], f->GetTSurface()[i]);
  }

  for (int i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], f->GetTSurface()[i + v1.size()]);
  }

  f->Clear();

  EXPECT_EQ(f->GetTSurface().size(), 0);
}

TEST(FigureTest, NormalsIndexesTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  std::vector<unsigned int> v1{0, 1, 2};
  std::vector<unsigned int> v2{3, 4, 5};

  f->AddNSurface(v1);

  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], f->GetNSurface()[i]);
  }

  f->AddNSurface(v2);

  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], f->GetNSurface()[i]);
  }

  for (int i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], f->GetNSurface()[i + v1.size()]);
  }

  f->Clear();

  EXPECT_EQ(f->GetNSurface().size(), 0);
}

TEST(FigureTest, IndexOffsetTest) {
  s21::Figure* f = s21::Figure::GetInstance();

  std::vector<unsigned int> v1{0, 1, 2};
  std::vector<unsigned int> v2{3, 4, 5};

  f->AddVSurface(v1);
  f->AddVSurface(v2);

  EXPECT_EQ(f->GetIndexOffset()[0], v1.size());
  EXPECT_EQ(f->GetIndexOffset()[1], v2.size());

  f->Clear();

  EXPECT_EQ(f->GetIndexOffset().size(), 0);
}

TEST(FigureTest, EdgesTest) {
  s21::Parser p;
  s21::Figure* f = s21::Figure::GetInstance();
  const char* file_name = "files/pyramid";
  p.ParserMethod(file_name);

  size_t edges_count = 8;

  EXPECT_EQ(f->GetEdgesCount(), edges_count);
}