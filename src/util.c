#include "util.h"

int rand_int(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}
