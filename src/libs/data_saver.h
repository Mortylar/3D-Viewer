#ifndef SRC_LIBS_DATA_SAVER_H_
#define SRC_LIBS_DATA_SAVER_H_

#include "data.h"

namespace s21 {
class DataSaver {
 public:
  explicit DataSaver(Data* data) : data_(data){};

  void LoadData() {
    if (IsValidConfigFile()) {
      FILE* fp = fopen(config_file_, "rb");
      if (fp) {
        ReadProjectionData(fp);
        ReadAreaColorData(fp);
        ReadLineData(fp);
        ReadPointData(fp);
      }
    }
  }

  void SaveData() {
    FILE* fp = fopen(config_file_, "wb");
    if (fp) {
      WriteProjectionData(fp);
      WriteAreaColorData(fp);
      WriteLineData(fp);
      WritePointData(fp);
    }
  }

 private:
  Data* data_ = nullptr;
  const char* config_file_ = ".3d_conf";

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

  void WriteProjectionData(FILE* fp) {
    int projection = data_->GetProjection();
    WriteIntegerData(fp, projection);
  }

  void WriteAreaColorData(FILE* fp) {
    GdkRGBA data = *(data_->GetAreaColor());
    WriteGdkRGBAData(fp, data);
  }

  void WriteLineData(FILE* fp) {
    int type = data_->GetLineType();
    float size = data_->GetLineWidth();
    GdkRGBA color = *(data_->GetLineColor());

    WriteIntegerData(fp, type);
    WriteFloatData(fp, size);
    WriteGdkRGBAData(fp, color);
  }

  void WritePointData(FILE* fp) {
    int type = data_->GetPointType();
    float size = data_->GetPointSize();
    GdkRGBA color = *(data_->GetPointColor());

    WriteIntegerData(fp, type);
    WriteFloatData(fp, size);
    WriteGdkRGBAData(fp, color);
  }

  void WriteGdkRGBAData(FILE* fp, GdkRGBA data) {
    fwrite(&data, sizeof(data), 1, fp);
  }

  void WriteIntegerData(FILE* fp, int data) {
    fwrite(&data, sizeof(data), 1, fp);
  }

  void WriteFloatData(FILE* fp, float data) {
    fwrite(&data, sizeof(data), 1, fp);
  }

  void ReadProjectionData(FILE* fp) {
    data_->SetProjection(ReadIntegerData(fp));
  }

  void ReadAreaColorData(FILE* fp) { data_->SetAreaColor(ReadGdkRGBAData(fp)); }

  void ReadLineData(FILE* fp) {
    data_->SetLineType(ReadIntegerData(fp));
    data_->SetLineWidth(ReadFloatData(fp));
    data_->SetLineColor(ReadGdkRGBAData(fp));
  }

  void ReadPointData(FILE* fp) {
    data_->SetPointType(ReadIntegerData(fp));
    data_->SetPointSize(ReadFloatData(fp));
    data_->SetPointColor(ReadGdkRGBAData(fp));
  }

  GdkRGBA ReadGdkRGBAData(FILE* fp) {
    GdkRGBA color;
    fread(&color, sizeof(color), 1, fp);
    return color;
  }

  int ReadIntegerData(FILE* fp) {
    int data;
    fread(&data, sizeof(data), 1, fp);
    return data;
  }

  float ReadFloatData(FILE* fp) {
    float data;
    fread(&data, sizeof(data), 1, fp);
    return data;
  }

  bool IsValidConfigFile() {
    bool is_valid = false;
    size_t size = GetFileLength(config_file_);
    size_t expected_size = 3 * 4 * sizeof(float) + 5 * sizeof(int);
    if (size == expected_size) is_valid = true;
    return is_valid;
  }
};
}  // namespace s21

// projection type - int
// area color - float[4]

// line type - int
// line size - int
// line color - float[4]

// point type - int
// point size - int
// point color - float[4]

#endif
