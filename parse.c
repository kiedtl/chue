#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "color.h"
#include "parse.h"

static _Bool
try_parse_hsvhsl(char *token, struct RGB *out) /* hsv(H, S, V) */
{
	_Bool hsv;

	if (strncmp((const char *) token, "hsv(", 4) == 0) {
		token += 4;
		hsv = true;
	} else if (strncmp((const char *) token, "hsl(", 4) == 0) {
		token += 4;
		hsv = false;
	} else {
		return false;
	}

	/* we only need 3 values, the last is ignored */
	double vals[3];
	size_t ctr;

	for (ctr = 0; ctr < 3; ++ctr) {
		char *val = strsep(&token, ",");
		vals[ctr] = strtod(val, NULL);
	}

	if (ctr < 2) {
		/* not enough fields in hsv() */
		return false;
	}

	if (hsv) {
		struct HSV h = { vals[0], vals[1], vals[2] };
		hsv_to_rgb(&h, out);
	} else {
		struct HSL h = { vals[0], vals[1], vals[2] };
		hsl_to_rgb(&h, out);
	}

	return true;
}

static _Bool
try_parse_decrgb(char *token, struct RGB *out) /* RRR,GGG,BBB */
{
	static struct RGB rgb = {0};

	if (token[0] < '0' || token[0] > '9') {
		return false;
	}

	/* we only need 3 values, the last is ignored */
	uint8_t vals[3];
	size_t ctr;

	for (ctr = 0; ctr < 3; ++ctr) {
		char *val = strsep(&token, ",");
		if (val[0] < '0' || val[0] > '9')
			return false;
		vals[ctr] = strtol(val, NULL, 10);
	}

	if (ctr < 2) {
		/* not enough fields */
		return false;
	}

	out->r = vals[0], out->g = vals[1], out->b = vals[2];
	return true;
}

static _Bool
try_parse_hexrgb(char *token, struct RGB *out) /* #R[R]G[G]B[B] */
{
	while (isspace(*token)) ++token;
	if (*token == '#') ++token;

	size_t hex  = (size_t)strtol(token, NULL, 16);

	if (strlen(token) == 3) {
		out->r = ((hex >> 8) & 0xF) << 4 | ((hex >> 8) & 0xF);
		out->g = ((hex >> 4) & 0xF) << 4 | ((hex >> 4) & 0xF);
		out->b = ((hex >> 0) & 0xF) << 4 | ((hex >> 0) & 0xF);
	} else if (strlen(token) == 6) {
		out->r = (hex >> 16) & 0xFF;
		out->g = (hex >>  8) & 0xFF;
		out->b = (hex)       & 0xFF;
	} else {
		/* unexpected token size, unexpected format */
		return false;
	}

	return true;
}

_Bool
parse(struct RGB *rgb, char *str)
{
	struct RGB color = {0};

	if ((try_parse_hexrgb(str, &color)) == NULL &&
		(try_parse_decrgb(str, &color)) == NULL &&
		(try_parse_hsvhsl(str, &color)) == NULL) {
		return false;
	} else {
		rgb->r = color.r;
		rgb->g = color.g;
		rgb->b = color.b;
		return true;
	}
}

