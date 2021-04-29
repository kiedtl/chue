#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

enum ColorblindnessFlavor {
    Protanopia = 1, Deuteranopia = 2, Tritanopia = 3
};

struct RGB { uint8_t r, g, b; };
void rgb_to_hsv(struct RGB *, struct HSV *);
void rgb_to_hsl(struct RGB *, struct HSL *);
void rgb_to_xyz(struct RGB *, struct XYZ *);

struct HSV { double h, s, v; };
void hsv_to_rgb(struct HSV *, struct RGB *);

struct HSL { double h, s, l; };
void hsl_to_rgb(struct HSL *, struct RGB *);

struct XYZ { double x, y, z; };
void xyz_to_rgb(struct XYZ *, struct RGB *);
void xyz_to_lms(struct XYZ *, struct LMS *);

struct LMS { double l, m, s; };
void lms_adjust_for_colorblindness(struct LMS *, enum ColorblindnessFlavor, struct LMS *);
void lms_to_xyz(struct LMS *, struct XY *);

#endif
