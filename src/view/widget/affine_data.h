#ifndef SRC_VIEW_WIDGET_AFFINE_DATA_H_
#define SRC_VIEW_WIDGET_AFFINE_DATA_H_

#include<iostream> //TODO remove

namespace s21 {
class AffineData {
  public:
    AffineData() {
      ReserveMemory();
    }

    ~AffineData() {
      ClearMemory();
    }

    AffineData& operator=(const AffineData& other) {
      for(size_t i = 0; i < kCommonSize_; ++i) {
        data_[i] = other.data_[i];
      }
      std::cout << "operator=" << std::endl;
      return *this;
    }

    double* GetData() {
      return data_;
    }

    void SetRotation(double x, double y, double z) {
      data_[Position::kRotation + 0] = x;
      data_[Position::kRotation + 1] = y;
      data_[Position::kRotation + 2] = z;
    }

    void SetTranslation(double x, double y, double z) {
      data_[Position::kTranslation + 0] = x;
      data_[Position::kTranslation + 1] = y;
      data_[Position::kTranslation + 2] = z;
    }

    void SetScaling(double x, double y, double z) {
      data_[Position::kScaling + 0] = x;
      data_[Position::kScaling + 1] = y;
      data_[Position::kScaling + 2] = z;
    }

    size_t GetDimension() {
      return kDim_;
    }

    size_t GetSize() {
      return kCommonSize_;
    }
  
  private:
    static const size_t kDim_ = 3;
    static const size_t kCommonSize_ = 9;
    double* data_ = nullptr; //Rotation, Translation, Scaling

    AffineData(const AffineData&);
    AffineData(const AffineData&&);
    AffineData& operator=(const AffineData&&);
    
    void ReserveMemory() {
      data_ = new double[kCommonSize_]();
    }

    void ClearMemory() {
      delete[] data_;
    }


    enum Position {
      kRotation = 0,
      kTranslation = kRotation + kDim_,
      kScaling = kTranslation + kDim_
    };


};
}

#endif
