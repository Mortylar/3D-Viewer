#include "pannel.h"


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

void Pannel::SetLabels(const char** name_arr) {
  for(size_t i = 0; i < size_; ++i) {
    pannels_[i].SetLabelText(name_arr[i]);
  }
}
