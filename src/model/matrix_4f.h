#ifndef SRC_MODEL_MATRIX_4F_H_
#define SRC_MODEL_MATRIX_4F_H_

#include <cstring>
#include <iostream> //TODO remove


namespace s21 {

class Matrix4f {
public:
  //-----------------------constructor-destructor block--------------------//
  Matrix4f() {
    Clear();
    SetInit();
  }

  Matrix4f(const Matrix4f& other) {
    if (this != &other) {
      std::memcpy(data_, other.data_, size_ * size_ * sizeof(float));
    } else {
      Clear();
      SetInit();
    }
  }

  Matrix4f(Matrix4f&& other) {
    if (this != &other) {
      std::swap(data_, other.data_);
    } else {
      Clear();
      SetInit();
    }
  }

  Matrix4f& operator=(const Matrix4f& other) {
    if (this != &other) {
      std::memcpy(data_, other.data_, size_ * size_ * sizeof(float));
    }
    return *this;
  }

  Matrix4f& operator=(Matrix4f&& other) {
    if (this != &other) {
      std::swap(data_, other.data_);
    }
    return *this;
  }

  ~Matrix4f() {
    Clear();
  }
//--------------------------------------end block------------------------------//

//----------------------------------summ block-----------------------------//
//

  Matrix4f& operator+=(Matrix4f& other) {
    for(int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        data_[i][j] += other.data_[i][j];
      }
    }
    return *this;
  }

  Matrix4f& operator-=(Matrix4f& other) {
    for(int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        data_[i][j] -= other.data_[i][j];
      }
    }
    return *this;
  }

  Matrix4f operator+(Matrix4f& other) {
    Matrix4f result(*this);
    return result += other;
  }

  Matrix4f operator-(Matrix4f& other) {
    Matrix4f result(*this);
    return result -= other;
  }


//----------------------------------end block-----------------------------//
//--------------------------------multiply block-------------------------//

  Matrix4f& operator*=(Matrix4f& other) {
    *this = (*this)*other;
    return *this;
  }

  Matrix4f operator*(Matrix4f& other) {
    Matrix4f result;
    result.Clear();
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        for (int k = 0; k < size_; ++k) {
	  result.data_[i][j] += (this->data_[i][k] * other.data_[k][j]);
	}
      }
    }
    return result;
  }
  
  Matrix4f& operator*(float x) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        this->data_[i][j] *= x;
      }
    }
    return *this;
  }
  Matrix4f& operator*=(Matrix4f other) {
    *this = (*this)*other;
    return *this;
  }
//---------------------------------end block --------------------------//

  float& operator()(int i, int j) {
    return data_[i][j];
  }

  Matrix4f& SetIdentity() {
    Clear();
    SetInit();
    return *this;
  }

  Matrix4f& SetZero() {
    Clear();
    return *this;
  }

  void Print() { 
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        std::cout << data_[i][j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

private:
  static const int size_{4};
  float data_[size_][size_];

  void Clear() {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        data_[i][j] = 0.0f;
      }
    }
  }

  void SetInit() {
    data_[0][0] = 1.0f;
    data_[1][1] = 1.0f;
    data_[2][2] = 1.0f;
    data_[3][3] = 1.0f;
  }


};
}

#endif
