#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "display.h"
#include "options.h"

void
display(struct RGB *c, struct Options *opts)
{
	struct XYZ xyz = {0};
	struct LMS lms = {0};

	rgb_to_xyz(c, &xyz);
	xyz_to_lms(&xyz, &lms);

	if (opts->display_hex) {
		printf("#%02x%02x%02x\t", c->r, c->g, c->b);
	}

	if (opts->display_dec) {
		printf("%03i,%03i,%03i\t", c->r, c->g, c->b);
	}

	if (opts->display_hsv) {
		struct HSV hsv = {0};
		rgb_to_hsv(c, &hsv);
		printf("hsv(%.2f,%.2f,%.2f)\t", hsv.h, hsv.s, hsv.v);
	}

	if (opts->display_hsl) {
		struct HSL hsl = {0};
		rgb_to_hsl(c, &hsl);
		printf("hsl(%.2f,%.2f,%.2f)\t", hsl.h, hsl.s, hsl.l);
	}

	if (opts->display_xyz) {
		struct XYZ xyz = {0};
		rgb_to_xyz(c, &xyz);
		printf("xyz(%.2f,%.2f,%.2f)\t", xyz.x, xyz.y, xyz.z);
	}

	if (opts->display_lms) {
		printf("lms(%.2f,%.2f,%.2f)\t", lms.l, lms.m, lms.s);
	}

	if (opts->display_color_norm) {
		printf("\033[48;2;%i;%i;%im\033[K\033[0m\t", c->r, c->g, c->b);
	}

	if (opts->display_color_trit) {
		struct LMS ladj = {0};
		struct XYZ xadj = {0};
		struct RGB radj = {0};

		lms_adjust_for_colorblindness(&lms, Tritanopia, &ladj);
		lms_to_xyz(&ladj, &xadj);
		xyz_to_rgb(&xadj, &radj);

		printf("\033[48;2;%i;%i;%im\033[K\033[0m\t", radj.r, radj.g, radj.b);
	}

	printf("\n");
}
