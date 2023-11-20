#ifndef SRC_VIEW_VALUE_H_
#define SRC_VIEW_VALUE_H_


#include <vector>

namespace s21 {
class Value {
  public:
    Value(){};

    Value(const Value& other) {
      std::copy(text_, other.text_);
      std::copy(int_, other.int_);
      std::copy(double_, other.double_);
    }

    Value(Value&& other) {
      std::swap(text_, other.text_);
      std::swap(int_, other.int_);
      std::swap(double_, other.double_);
    }

    ~Value(){};

    Value& operator=(const Value& other) {
      std::copy(text_, other.text_);
      std::copy(int_, other.int_);
      std::copy(double_, other.double_);
    }

    enum Type {
      kStringType = 0,
      kIntType,
      kDoubleType,
      kTypesCount
    };



  private:
    std::vector<std::string> text_;
    std::vector<int> int_;
    std::vector<double> double_;

};
}
#endif
