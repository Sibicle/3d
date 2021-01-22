#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#define fmin(a,b)  (((a) < (b)) ? (a) : (b))
#define fmax(a,b)  (((a) > (b)) ? (a) : (b))

int rand_int(int lower, int upper);

#endif
