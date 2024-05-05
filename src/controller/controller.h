#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
  public:
   explicit Controller(s21::Model* model):model_(model){};
	~Controller() = default;

	void ReadFile(const char* file_name) {
	  model_->ReadFile(file_name);
	}

	const std::vector<float>& GetVertex() {
	  return model_->GetVertex();
	}

	size_t GetVertexCount() {
	  return model_->GetVertexCount();
	}

	const std::vector<unsigned int>& GetSurfaces(size_t n) {
	  return model_->GetSurface(n);
	}

  size_t GetSurfacesCount() {
	  return model_->GetSurfacesCount();
	}
/*
	void Translation(std::vector<float>& v, float x, float y, float z) {
	  model_->Translation(v,x,y,z);
	}

	void Rotation(std::vector<float>& v, float x, float y, float z) {
	  model_->Rotation(v,x,y,z);
	}

	void Scaling(std::vector<float>& v, float x, float y, float z) {
	  model_->Scaling(v,x,y,z);
	}
*/
	void SetGLArea(GtkGLArea* area) {
	  model_->SetGLArea(area);
	}

	void ConnectData(s21::Data* data) {
	  model_->ConnectData(data);
	}

	void SetBuffer() {
	  model_->SetBuffers();
	}

	void Draw() {
	  model_->Draw();
	}

	void SavePicture(size_t width, size_t height) {
	  model_->SavePicture(width, height);
	}

  private:
	s21::Model* model_ = nullptr;

	Controller(const Controller&);
	Controller(Controller&&);
	Controller& operator=(const Controller&);

};
}
#endif
