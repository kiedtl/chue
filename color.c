#include "color.h"

#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

struct Color *
color_from_hsl(double h, double s, double l)
{
	struct Color *rgb = calloc(1, sizeof(struct Color));
	if (rgb == NULL) perror("chue: error: could not calloc");

	u8 region = round(h / 60);
	double C = (1 - abs(round((2 * l) - 1))) * s;
	double X = C * (1 - abs(region % 2 - 1));
	double m = l - C / 2;

	struct Color tmp;

	switch (region) {
	case 0:
		tmp.r = C; tmp.g = X; tmp.b = 0;
		break;
	case 1:
		tmp.r = X; tmp.g = C; tmp.b = 0;
		break;
	case 2:
		tmp.r = 0; tmp.g = C; tmp.b = X;
		break;
	case 3:
		tmp.r = 0; tmp.g = X; tmp.b = C;
		break;
	case 4:
		tmp.r = X; tmp.g = 0; tmp.b = C;
		break;
	default:
		tmp.r = C; tmp.g = 0; tmp.b = X;
		break;
	}

	rgb->r = (tmp.r + m) * 255;
	rgb->g = (tmp.g + m) * 255;
	rgb->b = (tmp.b + m) * 255;

	return rgb;
}

struct Color *
color_from_hsv(double h, double s, double v)
{
	struct Color *rgb = calloc(1, sizeof(struct Color));
	if (rgb == NULL) perror("chue: error: could not calloc");

	u8 region = round(h / 60);
	double C = v * s;
	double X = C * (1 - abs(region % 2 - 1));
	double m = v - C;

	struct Color tmp;

	switch (region) {
	case 0:
		tmp.r = C; tmp.g = X; tmp.b = 0;
		break;
	case 1:
		tmp.r = X; tmp.g = C; tmp.b = 0;
		break;
	case 2:
		tmp.r = 0; tmp.g = C; tmp.b = X;
		break;
	case 3:
		tmp.r = 0; tmp.g = X; tmp.b = C;
		break;
	case 4:
		tmp.r = X; tmp.g = 0; tmp.b = C;
		break;
	default:
		tmp.r = C; tmp.g = 0; tmp.b = X;
		break;
	}

	rgb->r = (tmp.r + m) * 255;
	rgb->g = (tmp.g + m) * 255;
	rgb->b = (tmp.b + m) * 255;

	return rgb;
}
