// Like all good code, this one was stolen directly from SO:
// https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion

#include "color.h"

#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX(A, B)       (((A) > (B)) ? A : B)
#define MAX3(A, B, C)   MAX(A, MAX(B, C))

#define MIN(A, B)       (((A) < (B)) ? A : B)
#define MIN3(A, B, C)   MIN(A, MIN(B, C))

static double
_hue_to_rgb(double p, double q, double t)
{
	if (t < 0.0) t += 1.0;
	if (t > 1.0) t -= 1.0;

	if (t < 1.0/6.0)
		return p + (q - p) * 6.0 * t;
	if (t < 1.0/2.0)
		return q;
	if (t < 2.0/3.0)
		return p + (q - p) * (2.0/3.0 - t) * 6.0;

	return p;
}

struct RGB *
rgb_from_hsl(double h, double s, double l)
{
	h /= 360.0, s /= 100.0, l /= 100.0;
	double r = 0.0, g = 0.0, b = 0.0;

	if (s == 0.0) {
		r = g = b = l; // achromatic
	} else {
		double q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
		double p = 2.0 * l - q;

		r = _hue_to_rgb(p, q, h + (1.0 / 3.0));
		g = _hue_to_rgb(p, q, h);
		b = _hue_to_rgb(p, q, h - (1.0 / 3.0));
	}

	struct RGB *rgb = calloc(1, sizeof(struct RGB));
	if (rgb == NULL) perror("chue: error: could not calloc");

	rgb->r = (u8)round(r * 255.0);
	rgb->g = (u8)round(g * 255.0);
	rgb->b = (u8)round(b * 255.0);

	return rgb;
}

struct RGB *
rgb_from_hsv(double h, double s, double v)
{
	s /= 100, v /= 100;

	struct RGB *rgb = calloc(1, sizeof(struct RGB));
	if (rgb == NULL) perror("chue: error: could not calloc");

	if (s <= 0.0) {
		rgb->r = rgb->g = rgb->b = v;
		return rgb;
	}

	double hh = (h >= 360.0 ? 0.0 : h) / 60.0;
	double i  = (usize)hh;
	double ff = hh - i;
	double p  = v * (1.0 - s);
	double q  = v * (1.0 - (s * ff));
	double t  = v * (1.0 - (s * (1.0 - ff)));

	double tr, tg, tb;

	switch ((usize)round(h / 60.0)) {
	break; case 0:  tr = v; tg = t; tb = p;
	break; case 1:  tr = q; tg = v; tb = p;
	break; case 2:  tr = p; tg = v; tb = t;
	break; case 3:  tr = p; tg = q; tb = v;
	break; case 4:  tr = t; tg = p; tb = v;
	break; default: tr = v; tg = p; tb = q;
	}

	rgb->r = (u8)round(tr * 255.0);
	rgb->g = (u8)round(tg * 255.0);
	rgb->b = (u8)round(tb * 255.0);

	return rgb;
}

struct HSV *
hsv_from_rgb(struct RGB *rgb)
{
	struct HSV *hsv = calloc(1, sizeof(struct HSV));
	if (hsv == NULL) perror("chue: error: could not calloc");

	double tr = ((double)rgb->r) / 255.0;
	double tg = ((double)rgb->g) / 255.0;
	double tb = ((double)rgb->b) / 255.0;

	double Xmax = MAX3(tr, tg, tb);
	double Xmin = MIN3(tr, tg, tb);
	double C    = Xmax - Xmin;

	hsv->v = Xmax;
	hsv->s = Xmax == 0 ? 0 : C / Xmax;

	if (C == 0.0) {
		hsv->h = 0;
	} else if (Xmax == tr) {
		hsv->h = 60.0 * (((tg - tb) / C) + 0.0);
	} else if (Xmax == tg) {
		hsv->h = 60.0 * (((tb - tr) / C) + 2.0);
	} else if (Xmax == tb) {
		hsv->h = 60.0 * (((tr - tg) / C) + 4.0);
	}

	if (hsv->h < 0.0)
		hsv->h += 360.0;

	hsv->s *= 100, hsv->v *= 100;
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

	double h, s, l;

	double max = MAX3(tr, tg, tb);
	double min = MIN3(tr, tg, tb);
	l = (max + min) / 2;

	if (max == min) {
		h = s = 0.0; // achromatic
	} else {
		double d = max - min;
		s = l > 0.5 ? d / (2.0 - max - min) : d / (max + min);

#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic push
		if (max == tr) {
			h = (tg - tb) / d + (tg < tb ? 6.0 : 0.0);
		} else if (max == tg) {
			h = (tb - tr) / d + 2.0;
		} else if (max == tb) {
			h = (tr - tg) / d + 4.0;
		} else {
			fprintf(stderr, "the sky is falling~\n");
			abort();
		}
#pragma GCC diagnostic pop
	
		h /= 6.0;
	}

	hsl->h = (h * 360.0), hsl->s = (s * 100.0), hsl->l = (l * 100.0);
	return hsl;
}
