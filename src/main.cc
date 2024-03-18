#include "model/model.h"
#include "controller/controller.h"
#include "view/view.h"

int main (void) {
  s21::Model m;
  s21::Controller c(&m);
  s21::View v(&c);
  v.RunWindow();
  return 0;
}
