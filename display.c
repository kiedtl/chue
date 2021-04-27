#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "display.h"
#include "options.h"

void
display(struct RGB *c, struct Options *opts)
{
	if (opts->display == HEXRGB) {
		printf("#%02x%02x%02x\t", c->r, c->g, c->b);
	} else if (opts->display == DECRGB) {
		printf("%03i,%03i,%03i\t", c->r, c->g, c->b);
	} else if (opts->display == HSV) {
		struct HSV hsv = hsv_from_rgb(*c);
		printf("hsv(%.2f,%.2f,%.2f)\t", hsv.h, hsv.s, hsv.v);
	} else if (opts->display == HSL) {
		struct HSL hsl = hsl_from_rgb(*c);
		printf("hsl(%.2f,%.2f,%.2f)\t", hsl.h, hsl.s, hsl.l);
	}

	if (opts->display_color) {
		printf("\033[48;2;%i;%i;%im\033[K\033[0m\n", c->r, c->g, c->b);
	}
}
