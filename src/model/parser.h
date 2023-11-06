#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <fstream>

namespace s21 {
class Parser {
  public:
    Parser() = default;
    ~Parser() = default;

    void ParserMethod(const char* file_name);

  private:
    const int buffer_length_ = 255;
    
    void ReadVertexes(std::ifstream& fin);
    void ReadSurface(std::ifstream& fin);
    void ResetFigure();

    bool IsNumber(char ch);
};
}


#endif // SRC_MODEL_PARSER_H_
