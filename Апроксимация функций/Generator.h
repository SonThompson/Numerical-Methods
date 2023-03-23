#pragma once
#ifndef Generator_h
#define Generator_h

#include "Point.h"
#include <vector>

std::vector<Point> grid_partitions_generator(double a, double b, int parts, double charge = 1.0);

#endif