#include<fstream>
#include<iostream>
#include<string>

int main() {
  std::ifstream fin("123");
  std::cout << fin.is_open() << std::endl;
  //char buffer[255];
  std::string buffer{0};
  int i = 1;
  fin >> buffer;
  while (buffer[0]) {
    buffer = '\0';
    fin >> buffer;
	std::cout << i << "<=>" << buffer << "|||" << std::endl;
	+i;
  }
  return 0;
}

