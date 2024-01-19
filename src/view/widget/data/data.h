#ifndef SRC_VIEW_WIDGET_DATA_DATA_H_
#define SRC_VIEW_WIDGET_DATA_DATA_H_

#include <cstring>
#include <algorithm>
#include <initializer_list>
#include <gtk/gtk.h>

namespace s21 {
class VectorData {
 public:
  VectorData() {
    size_ = 1;
    Allocate();
  }

  VectorData(size_t size) : size_(size) { Allocate();}

  VectorData(std::initializer_list<float> const& items) {
    size_ = items.size();
    Allocate();
    auto it = items.begin();
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = *it++;
    }
  }

  VectorData(const VectorData& other) {
    if (this != &other) {
      size_ = other.size_;
      Allocate();
      Copy(other);
    } else {
      DefaultInit();
    } 
  }

  VectorData(VectorData&& other) {
    if (this != &other) {
      swap(other);
    } else {
      DefaultInit();
    }
  }

  VectorData& operator=(const VectorData& other) {
    if(this != &other) {
      Reallocate(other.size_);
      Copy(other);
    }
    return *this;
  }

  VectorData& operator=(VectorData&& other) {
    if(this != &other) {
      Reallocate(other.size_);
      std::swap(data_, other.data_);
    }
    return *this;
  }

  ~VectorData() { Unallocate();}

  size_t GetSize() {return size_;}

  float* GetData() {return data_;}

  void SetValue(size_t pos, float value) {
    if(pos >= size_) throw std::out_of_range("s21::VectorData::SetValue - out of range");
    data_[pos] = value;
  }

  void SetValue(std::initializer_list<float> const &values) {
    auto it = values.begin();
    for(size_t i = 0; i < size_, i < values.size(); ++i) {
      data_[i] = *it++;
    }
  }

 private:
  float* data_ = nullptr;
  size_t size_ = 0;

  void Allocate() { data_ = new float[size_](); }

  void Unallocate() { delete[] data_; }

  void Reallocate(size_t size) {
    Unallocate();
    size_ = size;
    Allocate();
  }

  void DefaultInit() {
    size_ = 1;
    Allocate();
  }

  void Copy(const VectorData& other) {
    std::memcpy(data_, other.data_, size_*sizeof(float));
  }

  void swap(VectorData& other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }
};


class FormatData {
 public:
   FormatData(){}

   FormatData(float size, GdkRGBA color, int type): size_(size), color_(color), type_(type){}

   FormatData(const FormatData& other) {
     if(this != &other) {
       Copy(other);
     }
   }

   FormatData& operator=(const FormatData& other) {
     if (this != &other) {
       Copy(other);
     }
     return *this;
   }

   ~FormatData(){}

   float GetSize() { return size_; }
   GdkRGBA GetColor() { return color_; }
   int GetType() { return type_; }

   void SetColor(GdkRGBA color) { color_ = color; }
   void SetSize(float size) { size_ = size; }
   void SetType(int type) { type_ = type; }

 private:
   float size_ = 0;
   GdkRGBA color_ = {0,0,0,0};
   int type_ = 0;

   void Copy(const FormatData& other) {
     size_ = other.size_;
     color_ = other.color_;
     type_= other.type_;
   }
};

class AffineData {
 public:
   AffineData() {
   }

   AffineData(const AffineData& other) {
   }

   ~AffineData() {
   }

 private:
   const size_t kDim_ = 3;
   VectorData* translation_ = nullptr;
   VectorData* rotation_ = nullptr;
   VectorData* scaling_ = nullptr;

   void Init() {
     translation_ = new VectorData(kDim_);
     rotation_ = new VectorData(kDim_);
     scaling_ = new VectorData{1,1,1};
   }
};

}  // namespace s21

#endif
