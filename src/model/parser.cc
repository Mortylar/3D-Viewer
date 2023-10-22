#include "parser.h"

#include <fstream>
#include <std::exception>


void s21::Parser::ParserMethod(const char* file name) {
  ifstream fin(file_name);
  if (!fin.is_open())
    throw std::runtime_error("s21::Parser::ParserMethod(const char*) - couldn't open the file");

  char buffer[buffer_length_];
  fin >> buffer;
  while (buffer[0]) 
}
