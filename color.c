#include "color.h"

#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX(A, B)       (((A) > (B)) ? A : B)
#define MAX3(A, B, C)   MAX(A, MAX(B, C))

#define MIN(A, B)       (((A) < (B)) ? A : B)
#define MIN3(A, B, C)   MIN(A, MIN(B, C))

struct RGB *
rgb_from_hsl(double h, double s, double l)
{
	struct RGB *rgb = calloc(1, sizeof(struct RGB));
	if (rgb == NULL) perror("chue: error: could not calloc");

	double C = (1 - fabs((2 * l) - 1)) * s;
	double X = C * (1 - fabs(fmod(h / 60, 2) - 1));
	double m = l - C / 2;

	double tr = ((double) rgb->r) / 255.0;
	double tg = ((double) rgb->g) / 255.0;
	double tb = ((double) rgb->b) / 255.0;

	switch ((usize) round(h / 60)) {
	case 0:
		tr = C; tg = X; tb = 0;
		break;
	case 1:
		tr = X; tg = C; tb = 0;
		break;
	case 2:
		tr = 0; tg = C; tb = X;
		break;
	case 3:
		tr = 0; tg = X; tb = C;
		break;
	case 4:
		tr = X; tg = 0; tb = C;
		break;
	default:
		tr = C; tg = 0; tb = X;
		break;
	}

	rgb->r = (u8) round((tr + m) * 255.0);
	rgb->g = (u8) round((tg + m) * 255.0);
	rgb->b = (u8) round((tb + m) * 255.0);

	return rgb;
}

struct RGB *
rgb_from_hsv(double h, double s, double v)
{
	struct RGB *rgb = calloc(1, sizeof(struct RGB));
	if (rgb == NULL) perror("chue: error: could not calloc");

	double C = v * s;
	double X = C * (1 - fabs(fmod(h / 60, 2) - 1));
	double m = v - C;

	double tr = ((double) rgb->r) / 255.0;
	double tg = ((double) rgb->g) / 255.0;
	double tb = ((double) rgb->b) / 255.0;

	switch ((usize) round(h / 60)) {
	case 0:
		tr = C; tg = X; tb = 0;
		break;
	case 1:
		tr = X; tg = C; tb = 0;
		break;
	case 2:
		tr = 0; tg = C; tb = X;
		break;
	case 3:
		tr = 0; tg = X; tb = C;
		break;
	case 4:
		tr = X; tg = 0; tb = C;
		break;
	default:
		tr = C; tg = 0; tb = X;
		break;
	}

	rgb->r = (u8) round((tr + m) * 255.0);
	rgb->g = (u8) round((tg + m) * 255.0);
	rgb->b = (u8) round((tb + m) * 255.0);

	return rgb;
}

struct HSV *
hsv_from_rgb(struct RGB *rgb)
{
	struct HSV *hsv = calloc(1, sizeof(struct HSV));
	if (hsv == NULL) perror("chue: error: could not calloc");

	double tr = ((double) rgb->r) / 255.0;
	double tg = ((double) rgb->g) / 255.0;
	double tb = ((double) rgb->b) / 255.0;

	double Cmax = MAX3(tr, tg, tb);
	double Cmin = MIN3(tr, tg, tb);
	double delt = Cmax - Cmin;

	/* comparing floating points with == or != should
	 * be completely safe here */
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic push
	if (delt == 0.0) {
		hsv->h = 0;
	} else if (Cmax == tr) {
		hsv->h = 60 * fmod(((tg - tb) / delt), 6.0);
	} else if (Cmax == tg) {
		hsv->h = 60 * (((tb - tr) / delt) + 2.0);
	} else if (Cmax == tb) {
		hsv->h = 60 * (((tr - tg) / delt) + 4.0);
	}
#pragma GCC diagnostic pop

	if (Cmax == 0) {
		hsv->s = 0;
	} else {
		hsv->s = delt / Cmax;
	}

	hsv->v = Cmax;

	return hsv;
}

struct HSL *
hsl_from_rgb(struct RGB *rgb)
{
	struct HSL *hsl = calloc(1, sizeof(struct HSL));
	if (hsl == NULL) perror("chue: error: could not calloc");

	double tr = ((double) rgb->r) / 255.0;
	double tg = ((double) rgb->g) / 255.0;
	double tb = ((double) rgb->b) / 255.0;

	double Cmax = MAX3(tr, tg, tb);
	double Cmin = MIN3(tr, tg, tb);
	double delt = Cmax - Cmin;

	/* comparing floating points with == or != should
	 * be completely safe here */
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic push
	if (delt == 0.0) {
		hsl->h = 0;
	} else if (Cmax == tr) {
		hsl->h = 60 * fmod(((tg - tb) / delt), 6.0);
	} else if (Cmax == tg) {
		hsl->h = 60 * (((tb - tr) / delt) + 2.0);
	} else if (Cmax == tb) {
		hsl->h = 60 * (((tr - tg) / delt) + 4.0);
	}
#pragma GCC diagnostic pop

	hsl->l = Cmax - Cmin;

	if (Cmax == 0) {
		hsl->s = 0;
	} else {
		hsl->s = delt / (1 - fabs(2 * hsl->l - 1));
	}

	return hsl;
}
