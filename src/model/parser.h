#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <string>
#include <vector>

namespace s21 {
class Parser {
 public:
  Parser() = default;
  ~Parser() = default;

  void ParserMethod(const char *file_name);

 private:
  void ReadVertexes(const std::string &buffer);
  int ExtractVertexData(const std::string &, const std::string &, float *,
                        float *, float *);

  void ReadSurface(const std::string &buffer);
  size_t ExtractFragment(const std::string &, size_t,
                         std::vector<unsigned int> &,
                         std::vector<unsigned int> &,
                         std::vector<unsigned int> &);
  void WriteFragment(const std::string &, int, std::vector<unsigned int> &,
                     std::vector<unsigned int> &, std::vector<unsigned int> &);
  void ResetFigure();
  size_t GetFileLength(const char *file_name);
  std::string ReadString(FILE *, size_t *);
  bool IsNumber(char ch);
};
}  // namespace s21

#endif  // SRC_MODEL_PARSER_H_
