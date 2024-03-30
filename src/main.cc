#include "model/model.h"
#include "controller/controller.h"
#include "view/view.h"

int main (void) {
 // s21::Model* m = new s21::Model();
  
  s21::Model m;
  s21::Controller c(&m);
  s21::View v(&c);
  v.RunWindow();
  //delete m;
  return 0;
}
