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
	  //model_->Centring(model_->GetVertex());
	  //model_->Normalize(model_->GetVertex());
	}

	const std::vector<double>& GetVertex() {
	  return model_->GetVertex();
	}

	const std::vector<int>& GetSurfaces(size_t n) {
	  return model_->GetSurface(n);
	}

	void Translation(std::vector<double>& v, double x, double y, double z) {
	  model_->Translation(v,x,y,z);
	}

	void Rotation(std::vector<double>& v, double x, double y, double z) {
	  model_->Rotation(v,x,y,z);
	}

	void Scaling(std::vector<double>& v, double x, double y, double z) {
	  model_->Scaling(v,x,y,z);
	}

  private:
	s21::Model* model_ = nullptr;

	Controller(const Controller&);
	Controller(Controller&&);
	Controller& operator=(const Controller&);

};
}
#endif
