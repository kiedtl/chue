#ifndef COLOR_H
#define COLOR_H
#include "types.h"

struct Color { u8 r, g, b; };

struct Color *color_from_hsl(double h, double s, double l);
struct Color *color_from_hsv(double h, double s, double v);
#endif
