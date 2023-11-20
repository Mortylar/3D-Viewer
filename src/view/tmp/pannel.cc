#include "pannel.h"
#include <stdexcept>

void Pannel::PannelsAllocate() {
  pannels_ = new InputPannel [size_];
}

void Pannel::InitGrid() {
  grid_ = gtk_grid_new();
  for(size_t i = 0; i < size_; ++i) {
    gtk_grid_attach(GTK_GRID(grid_), pannels_[i].GetRoot(), 0, i, 1, 1);
  }
  gtk_frame_set_child(GTK_FRAME(GetFrame()), grid_);
}

void Pannel::SetLabel(size_t pos, const char* name) {
  pannels_[pos].SetLabelText(name);
}

void Pannel::SetLabels(const char** name_arr) {
  for(size_t i = 0; i < size_; ++i) {
    SetLabel(i, name_arr[i]);
  }
}

double Pannel::GetValue(size_t pos) {
  if (pos >= size_) {
    throw std::out_of_range("Out of range");
  }
  return pannels_[pos].GetValue();
}
