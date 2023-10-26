#include<fstream>
#include<iostream>
#include<string>

int main() {
  size_t v_pos;
  std::ifstream fin("123");
  std::cout << fin.is_open() << std::endl;
  //char buffer[255];
  std::string buffer{0};
  int i = 1;
  fin >> buffer;
  while (buffer[0] != 'f') {
//    fin.seekg(0);
    buffer = '\0';
    fin >> buffer;
    if (buffer[0] == 'f')  v_pos = fin.tellg();
    std::cout << i << "<=>" << buffer << "|" << std::endl;
    ++i;
  }
  fin.close();
  fin.open("123");

  std::cout << "\n=========================================" << std::endl;
  
  //fin.seekg(0);
  int shift = 0;
  std::cin >> shift;
  fin.seekg(v_pos - shift);
  fin >> buffer;
  std::cout <<"buffer is" << buffer << std::endl;
  return 0;
}

