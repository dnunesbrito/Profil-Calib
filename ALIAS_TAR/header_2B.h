#ifndef _2B_H
#define _2B_H

#include "IntervalVector.h"

void load(char* filename, REAL eps);

void set_epsilon(REAL eps);

int _2b(INTERVAL_VECTOR& box);

void clean();

#endif
