#ifndef SRC_VIEW_WIDGET_DATA_DATA_H_
#define SRC_VIEW_WIDGET_DATA_DATA_H_

namespace s21 {
class VectorData {
  public:
    VectorData() {
      size_ = 1;
	  Allocate();
	}

	VectorData(size_t size):size_(size) {
	  Allocate();
	}

	VectorData(std::initializer_list<float> const& items) {
	  size_ = items.size();
	  Allocate();
	  auto it = items.begin();
	  for(size_t i = 0; i < size_; ++i) {
	    data_[i] = *it++;
	  }
	}

	VectorData(const VectorData& other) {
      if(this != &other) {
	    size_ = other.size_;
		Allocate();
		for(size_t i = 0; i < size_; ++i) {
		  this->data_[i] = other.data_[i];
		}
	  }
	}

	VectorData(VectorData&& other) {
      if(this != &other) {
	    std::swap(size_, other.size_);
		std::swap(data_, other.data_);
	  } else {
	    size_ = 1;
		Allocate();
	  }
	}

	VectorData& operator=(const VectorData& other) {
	}//TODO

	VectorData& operator=(VectorData&& other) {
	} //TODO

	~VectorData() {
	  delete[] data_;
	}

  private:
	float* data_ = nullptr;
	size_t size_ = 0;

	void Allocate() {
	  data_ = new float[size_]();
	}
};
}

#endif
