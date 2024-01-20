#ifndef SRC_VIEW_WIDGET_DATA_DATA_H_
#define SRC_VIEW_WIDGET_DATA_DATA_H_

#include <cstring>
//#include <algorithm>
#include <stdexcept>
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


  //TODO overload []
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
     Init();
   }

   AffineData(const AffineData& other) {
     TemplateInit(other);
   }

   ~AffineData() {
     Clear();
   }

   size_t GetSize() { return kDim_; }

   VectorData* GetTranslationData() { return translation_; }
   VectorData* GetRotationData() { return rotation_; }
   VectorData* GetScalingData() { return scaling_; }

   float* GetTranslation() { return translation_->GetData(); }
   float* GetRotation() { return rotation_->GetData(); }
   float* GetScaling() { return scaling_->GetData(); }

   void SetTranslation(const VectorData& translation) {
     *translation_ = translation;
   }

   void SetRotation(const VectorData& rotation) {
     *rotation_ = rotation;
   }

   void SetScaling(const VectorData& scaling) {
     *scaling_ = scaling;
   }

   void SetTranslation(float x, float y, float z) {
     translation_->SetValue({x,y,z});
   }

   void SetRotation(float x, float y, float z) {
     rotation_->SetValue({x,y,z});
   }

   void SetScaling(float x, float y, float z) {
     scaling_->SetValue({x,y,z});
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

  void TemplateInit(const AffineData& other) { 
    translation_ = new VectorData(*(other.translation_));
    rotation_ = new VectorData(*(other.rotation_));
    scaling_ = new VectorData(*(other.scaling_));
  }

  void Clear() {
    delete translation_;
    delete rotation_;
    delete scaling_;
  }
};


class Data {
 public:
   Data() {
     InitData();
   }

   ~Data() {
     ClearData();
   }

   int GetProjection() {
     return projection_data_;
   }

   void SetProjection(int type) {
     projection_data_ = type;
   }

   GdkRGBA GetAreaColor() {
     return area_color_data_;
   }

   void SetAreaColor(GdkRGBA color) {
     area_color_data_ = color;
   }

   float GetLineWidth() {
     return line_data_->GetSize();
   }

   void SetLineWidth(float width) {
     line_data_->SetSize(width);
   }

   float GetPointSize() {
     return point_data_->GetSize();
   }

   void SetPointSize(float size) {
     point_data_->SetSize(size);
   }

   int GetLineType() {
     return line_data_->GetType();
   }

   void SetLineType(int type) {
     line_data_->SetType(type);
   }

   int GetPointType() {
     return point_data_->GetType();
   }

   void SetPointType(int type) {
     point_data_->SetType(type);
   }

  GdkRGBA GetLineColor() {
    return line_data_->GetColor();
  }

  void SetLineColor(GdkRGBA color) {
    line_data_->SetColor(color);
  }

  GdkRGBA GetPointColor() {
    return point_data_->GetColor();
  }

  void SetPointColor(GdkRGBA color) {
    point_data_->SetColor(color);
  }

  VectorData* GetTranslationData() {
    return affine_data_->GetTranslationData();
  }

  float* GetTranslation() {
    return affine_data_->GetTranslation();
  }

  void SetTranslationData(VectorData* data) {
    affine_data_->SetTranslation(*data);
  }

  void SetTranslation(float x, float y, float z) {
    affine_data_->SetTranslation(x,y,z);
  }

  VectorData* GetRotationData() {
    return affine_data_->GetRotationData();
  }

  float* GetRotation() {
    return affine_data_->GetRotation();
  }

  void SetRotationData(VectorData* data) {
    affine_data_->SetRotation(*data);
  }

  void SetRotation(float x, float y, float z) {
    affine_data_->SetRotation(x,y,z);
  }

  VectorData* GetScalingData() {
    return affine_data_->GetScalingData();
  }

  float* GetScaling() {
    return affine_data_->GetScaling();
  }

  void SetScalingData(VectorData* data) {
    affine_data_->SetScaling(*data);
  }

  void SetScaling(float x, float y, float z) {
    affine_data_->SetScaling(x,y,z);
  }




 private:
   AffineData* affine_data_ = nullptr;
   FormatData* line_data_ = nullptr;
   FormatData* point_data_ = nullptr;
   GdkRGBA area_color_data_;
   int projection_data_;

   void InitData() {
     affine_data_ = new AffineData();
     line_data_ = new FormatData(1.0, {1,0,0,0}, 0);
     point_data_ = new FormatData(1.0, {0,1,0,0}, 0);
   }

   void ClearData() {
     delete affine_data_;
     delete line_data_;
     delete point_data_;
   }

};

}  // namespace s21

#endif
