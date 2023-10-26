#include "parser.h"

#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>

#include <iostream> //TODO remove

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
  std::cout << "\n =====vertex===== " << std::endl;
  for (int i = 0; i < 3; ++i) {
    fin >> buffer;
    if (!IsNumber(buffer[0]))
      throw std::invalid_argument("s21::Parser - object file include less " 
                 "then 3 coordinates in one vertex");
    vertex[i] = std::strtod(buffer, nullptr);
    std::cout << i << " <=> " << vertex[i] << std::endl;
  }
}

void s21::Parser::ReadSurface(std::ifstream& fin) {
  char buffer[buffer_length_]{0};
  std::vector<int> surface;
  fin >> buffer;
  while(IsNumber(buffer[0])) {
    surface.push_back(std::atoi(buffer));
    fin >> buffer;
  }
  fin.seekg(fin.tellg() - static_cast<long int>(strlen(buffer) + 1));
  std::cout << "\n----surface-----" << std::endl;
  for(size_t i = 0; i < surface.size(); ++i) {
    std::cout << i << " <=> " << surface[i] << std::endl;
  }
}

bool s21::Parser::IsNumber(char ch) {
  return std::isdigit(static_cast<unsigned char>(ch)) || ('+' == ch ) || ('-' == ch);
}

int main() {
  s21::Parser A;
  A.ParserMethod("123");
  return 0;
}

