#include "parser.h"

#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

#include "figure.h"

void s21::Parser::ParserMethod(const char* file_name) {
  std::ifstream fin(file_name);
  if (!fin.is_open())
    throw std::runtime_error("s21::Parser::ParserMethod(const char*) - couldn't open the file");

  char buffer[buffer_length_]{0};
  fin >> buffer;
  while (buffer[0]) {
    if (('v' == buffer[0]) && ('\0' == buffer[1])) {  
      ReadVertexes(fin);
    } else if (('f' == buffer[0]) && ('\0' == buffer[1])) {
      ReadSurface(fin);
    }
    buffer[0] = 0;
    fin >> buffer;
  }

  fin.close();
}

void s21::Parser::ReadVertexes(std::ifstream& fin) {
  char buffer[buffer_length_]{0};
  double vertex[3]{0};
  for (int i = 0; i < 3; ++i) {
    fin >> buffer;
    if (!IsNumber(buffer[0]))
      throw std::invalid_argument("s21::Parser - object file include less " 
                 "then 3 coordinates in one vertex");
    vertex[i] = std::strtod(buffer, nullptr);
  }
  s21::Figure::GetInstance()->AddVertex(vertex[0], vertex[1], vertex[2]);
}

void s21::Parser::ReadSurface(std::ifstream& fin) {
  char buffer[buffer_length_]{0};
  std::vector<int> surface;
  int v_count = static_cast<int>(s21::Figure::GetInstance()->GetVertexCount());
  fin >> buffer;
  while(IsNumber(buffer[0])) {
    int vertex_id = std::atoi(buffer);
    if (vertex_id < 0) {
      vertex_id = v_count + 1 + vertex_id;
    }
    if ((vertex_id <= 0) || (vertex_id > v_count))
      throw std::invalid_argument("s21::Parser - invalid number of vertex");

    surface.push_back(vertex_id);
    fin >> buffer;
  }
  s21::Figure::GetInstance()->AddSurface(static_cast<const std::vector<int>>(surface));
  fin.seekg(fin.tellg() - static_cast<long int>(strlen(buffer) + 1));
}

bool s21::Parser::IsNumber(char ch) {
  return std::isdigit(static_cast<unsigned char>(ch)) || ('+' == ch ) || ('-' == ch);
}

