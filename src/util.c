#include "util.h"

int rand_int(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

void int_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
