#ifndef COLOR_H
#define COLOR_H
#include "types.h"

struct RGB { u8 r, g, b; };
struct HSV { double h, s, v; };
struct HSL { double h, s, l; };

struct RGB *rgb_from_hsl(double h, double s, double l);
struct RGB *rgb_from_hsv(double h, double s, double v);

struct HSV *hsv_from_rgb(struct RGB *rgb);
#endif
