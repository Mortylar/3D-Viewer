#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

namespace s21 {
class Parser {
  public:
    Parser() = default;
	~Parser() = default;

	void ParserMethod(const char* file_name);

  private:
    const int buffer_length_ = 255; 
};
}


#endif // SRC_MODEL_PARSER_H_
