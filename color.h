#ifndef COLOR_H
#define COLOR_H
#include "types.h"

struct Color { u8 r, g, b; };

struct Color *color_from_hsv(u8 h, u8 s, u8 v);
#endif
