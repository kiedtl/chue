#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "display.h"
#include "options.h"

void
display(struct RGB *c, struct Options *opts)
{
	if (opts->display_hex) {
		printf("#%02x%02x%02x\t", c->r, c->g, c->b);
	}

	if (opts->display_dec) {
		printf("%03i,%03i,%03i\t", c->r, c->g, c->b);
	}

	if (opts->display_hsv) {
		struct HSV hsv = rgb_to_hsv(c);
		printf("hsv(%.2f,%.2f,%.2f)\t", hsv.h, hsv.s, hsv.v);
	}

	if (opts->display_hsl) {
		struct HSL hsl = rgb_to_hsl(c);
		printf("hsl(%.2f,%.2f,%.2f)\t", hsl.h, hsl.s, hsl.l);
	}

	if (opts->display_xyz) {
		struct XYZ xyz = rgb_to_xyz(c);
		printf("xyz(%.2f,%.2f,%.2f)\t", xyz.x, xyz.y, xyz.z);
	}

	if (opts->display_lms) {
		struct XYZ xyz = rgb_to_xyz(c);
		struct LMS lms = xyz_to_lms(&xyz);
		printf("lms(%.2f,%.2f,%.2f)\t", lms.l, lms.m, lms.s);
	}

	if (opts->display_color) {
		printf("\033[48;2;%i;%i;%im\033[K\033[0m\n", c->r, c->g, c->b);
	}
}
