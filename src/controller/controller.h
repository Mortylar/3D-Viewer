#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(s21::Model* model) : model_(model){};
  ~Controller() = default;

  void ReadFile(const char* file_name) { model_->ReadFile(file_name); }

  size_t GetVertexCount() { return model_->GetVertexCount(); }

  size_t GetSurfacesCount() {
    return model_->GetEdgesCount();
    // return model_->GetSurfacesCount();
  }

  void SetGLArea(GtkGLArea* area) { model_->SetGLArea(area); }

  void ConnectData(s21::Data* data) { model_->ConnectData(data); }

  void SetBuffer() { model_->SetBuffers(); }

  void Draw() { model_->Draw(); }

 private:
  s21::Model* model_ = nullptr;

  Controller(const Controller&);
  Controller(Controller&&);
  Controller& operator=(const Controller&);
};
}  // namespace s21
#endif
