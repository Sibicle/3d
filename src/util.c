#include "util.h"

int rand_int(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

void swapi(int * a, int * b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapf(float * a, float * b) {
  float tmp = *a;
  *a = *b;
  *b = tmp;
}
