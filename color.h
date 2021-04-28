#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

enum ColorblindnessFlavor {
    Protanopia, Deuteranopia, Tritanopia
};

struct RGB { uint8_t r, g, b; };
struct HSV rgb_to_hsv(struct RGB *);
struct HSL rgb_to_hsl(struct RGB *);
struct XYZ rgb_to_xyz(struct RGB *);

struct HSV { double h, s, v; };
struct RGB hsv_to_rgb(struct HSV *);

struct HSL { double h, s, l; };
struct RGB hsl_to_rgb(struct HSL *);

struct XYZ { double x, y, z; };
struct RGB xyz_to_rgb(struct XYZ *);
struct LMS xyz_to_lms(struct XYZ *);

struct LMS { double l, m, s; };
struct XYZ lms_to_xyz(struct LMS *);

#endif
