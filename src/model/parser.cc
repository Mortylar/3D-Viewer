#include "parser.h"

#include <cstring>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "figure.h"

#include <iostream> //TODO remove

void s21::Parser::ParserMethod(const char *file_name) {
  setlocale(LC_NUMERIC, "C");
  size_t file_length = GetFileLength(file_name);
  FILE *fp = fopen(file_name, "rb");
  if (!fp)
    throw std::runtime_error(
        "s21::Parser::ParserMethod(const char*) - couldn't open the file");

  ResetFigure();
  while (file_length) {
    std::string buffer = ReadString(fp, &file_length);
    if ('v' == buffer[0]) {
      ReadVertexes(buffer);
    } else if (('f' == buffer[0]) && (' ' == buffer[1])) {
      ReadSurface(buffer);
    }
  }

  fclose(fp);
  s21::Figure::GetInstance()->GetVertex().shrink_to_fit();
  if (!s21::Figure::GetInstance()->GetVertexCount())
    throw std::invalid_argument("Empty figure");
}

void s21::Parser::ReadVertexes(const std::string &buffer) {
  float vertex[3]{0};
  int status = 0;
  if (buffer[1] == ' ') {
    status = ExtractVertexData(buffer, "v %f %f %f ##1", &vertex[0], &vertex[1],
                               &vertex[2]);
    s21::Figure::GetInstance()->AddVertex(vertex[0], vertex[1], vertex[2]);
  } else if (buffer[1] == 't') {
    status = ExtractVertexData(buffer, "vt %f %f %f", &vertex[0], &vertex[1],
                               &vertex[2]);
    if (status == 2)
      ++status;
    s21::Figure::GetInstance()->AddTextures(vertex[0], vertex[1], vertex[2]);
  } else if (buffer[1] == 'n') {
    status = ExtractVertexData(buffer, "vn %f %f %f", &vertex[0], &vertex[1],
                               &vertex[2]);
    s21::Figure::GetInstance()->AddNormals(vertex[0], vertex[1], vertex[2]);
  }
  if (status != 3)
    throw std::invalid_argument("s21::Parser - object file include less then 3 "
                                "coordinates in one vertex");
}

int s21::Parser::ExtractVertexData(const std::string &buffer,
                                   std::string format, float *x, float *y,
                                   float *z) {
  return sscanf(buffer.data(), format.data(), x, y, z);
}

void s21::Parser::ReadSurface(const std::string &buffer) {
  std::vector<unsigned int> v_surface;
  std::vector<unsigned int> t_surface;
  std::vector<unsigned int> n_surface;
  size_t pos = 2;
  while (pos < buffer.size()) {
    pos = ExtractFragment(buffer, pos, v_surface, t_surface, n_surface);
    while (!IsNumber(buffer[pos]) && (pos < buffer.size())) {
      if (buffer[pos] == '#') {
        pos = buffer.size();
      } else {
        ++pos;
      }
    }
  }

  s21::Figure::GetInstance()->AddVSurface(v_surface);
  if (t_surface.size())
    s21::Figure::GetInstance()->AddTSurface(t_surface);
  if (n_surface.size())
    s21::Figure::GetInstance()->AddNSurface(n_surface);
}

size_t s21::Parser::ExtractFragment(const std::string &buffer, size_t pos,
                                    std::vector<unsigned int> &v,
                                    std::vector<unsigned int> &t,
                                    std::vector<unsigned int> &n) {
  std::string fragment;
  int mod_count = 0;

  while (buffer[pos] && (buffer[pos] != ' ') && (buffer[pos] != '\n')) {
    if (buffer[pos] == '/') {
      fragment += ' ';
      ++mod_count;
      if (buffer[pos + 1] == '/') {
        fragment += "0 ";
        pos += 2;
        ++mod_count;
      } else {
        fragment += ' ';
        ++pos;
      }
    } else {
      fragment += buffer[pos];
      ++pos;
    }
  }
  WriteFragment(fragment, mod_count, v, t, n);
  return pos;
}

void s21::Parser::WriteFragment(const std::string &fragment, int mod_count,
                                std::vector<unsigned int> &v,
                                std::vector<unsigned int> &t,
                                std::vector<unsigned int> &n) {
  int vertex_id, texture_id, normal_id;
  int status =
      sscanf(fragment.data(), "%i %i %i", &vertex_id, &texture_id, &normal_id);
  if (status == 0)
    throw std::invalid_argument("s21::Parser - empty surface");

  int vertex_count =
      static_cast<int>(s21::Figure::GetInstance()->GetVertexCount());
  if (vertex_id < 0) {
    vertex_id = vertex_count + vertex_id + 1;
  }
  if ((vertex_id <= 0) || (vertex_id > vertex_count))
    throw std::invalid_argument("s21::Parser - invalid number of vertex");
  v.push_back(static_cast<unsigned int>(vertex_id - 1));

  if (status == 3) {
    t.push_back(static_cast<unsigned int>(texture_id - 1));
    n.push_back(static_cast<unsigned int>(normal_id));
  } else if (status == 2) {
    if (mod_count == 2) {
      n.push_back(static_cast<unsigned int>(normal_id));
    } else {
      t.push_back(static_cast<unsigned int>(texture_id));
    }
  }
}

bool s21::Parser::IsNumber(char ch) {
  return std::isdigit(static_cast<unsigned char>(ch)) || ('+' == ch) ||
         ('-' == ch);
}

size_t s21::Parser::GetFileLength(const char *file_name) {
  size_t file_length = 0;
  FILE *fp = fopen(file_name, "rb");
  if (fp) {
    fseek(fp, 0, SEEK_END);
    file_length = ftell(fp);
    fclose(fp);
  }
  return file_length;
}

std::string s21::Parser::ReadString(FILE *fp, size_t *file_length) {
  std::string result;
  char letter{'a'};
  while ((*file_length) && (letter != '\n') && letter) {
    fread(&letter, 1, 1, fp);
    result += letter;
    --(*file_length);
  }
  return result;
}

void s21::Parser::ResetFigure() {
  s21::Figure::GetInstance()->Clear();
  s21::Figure::GetInstance()->Reserve(10000);
}
