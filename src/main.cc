#include "controller/controller.h"
#include "model/model.h"
#include "view/view.h"

int main(int argc, char** argv) {
  s21::Model m;
  s21::Controller c(&m);
  s21::View v(&c);
  v.RunWindow(argv[0]);
  return 0;
}
