#ifndef SRC_LIBS_DATA_SAVER_H_
#define SRC_LIBS_DATA_SAVER_H_

//#include <stdio>
#include "data.h"


namespace s21 {
class DataSaver {
 public:
  DataSaver(Data* data): data_(data) {};

  void LoadData() {}

	void SaveData() {}

 private:
  Data* data_ = nullptr;
	char* config_file = ".3d_conf";
	//char* state_ = nullptr;
	//size_t state_length_;

/*	size_t InitStateLength {
		//projection line point types and line and point size is int
		// line point and area color is GdkRGBA (means float[4])
	  state_length_ = 5 * sizeof(int) + 3 * 4 * sizeof(float);
	}*/

  size_t GetFileLength(const char* file_name) {
	  size_t file_length = -1;
		FILE* fp = fopen(file_name, "rb");
		if (fp) {
			fseek(fp, 0, SEEK_END);
		  file_length = ftell(fp);
			fclose(fp);
		}
		return file_length;
	}

	void WriteProjectionData() {}
	void Write AreaColorData() {}

	void WriteLineData() {}
	void WritePointData() {}



};
}

//projection type - int
//area color - float[4]

//line type - int
//line size - int
//line color - float[4]

//point type - int
//point size - int
//point color - float[4]

#endif
