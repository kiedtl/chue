#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "color.h"
#include "list.h"
#include "parse.h"
#include "types.h"
#include "result.h"

static struct RGB *
try_parse_hsvhsl(char *token) /* hsv(H, S, V) */
{
	bool hsv;

	if (strncmp((const char *) token, "hsv(", 4) == 0) {
		token += 4;
		hsv = TRUE;
	} else if (strncmp((const char *) token, "hsl(", 4) == 0) {
		token += 4;
		hsv = FALSE;
	} else {
		return NULL;
	}

	/* we only need 3 values, the last is ignored */
	double vals[3];
	usize ctr;

	for (ctr = 0; ctr < 3; ++ctr) {
		char *val = strsep(&token, ",");
		vals[ctr] = strtod(val, NULL);
	}

	if (ctr < 2) {
		/* not enough fields in hsv() */
		return NULL;
	}

	if (hsv)
		return rgb_from_hsv(vals[0], vals[1], vals[2]);
	else
		return rgb_from_hsl(vals[0], vals[1], vals[2]);
}

static struct RGB *
try_parse_decrgb(char *token) /* RRR,GGG,BBB */
{
	if (token[0] < '0' || token[0] > '9') {
		return NULL;
	}

	/* we only need 3 values, the last is ignored */
	u8 vals[3];
	usize ctr;

	for (ctr = 0; ctr < 3; ++ctr) {
		char *val = strsep(&token, ",");
		if (val[0] < '0' || val[0] > '9')
			return NULL;
		vals[ctr] = strtol(val, NULL, 10);
	}

	if (ctr < 2) {
		/* not enough fields */
		return NULL;
	}

	struct RGB *rgb = calloc(1, sizeof(struct RGB));
	rgb->r = vals[0];
	rgb->g = vals[1];
	rgb->b = vals[2];
	return rgb;
}

static struct RGB *
try_parse_hexrgb(char *token) /* #R[R]G[G]B[B] */
{
	while (isspace(*token)) ++token;
	if (*token == '#') ++token;

	struct RGB *rgb = calloc(1, sizeof(struct RGB));
	rgb->r = rgb->g = rgb->b = 0;

	usize hex  = (usize) strtol(token, NULL, 16);

	if (strlen(token) == 3) {
		rgb->r = ((hex >> 8) & 0xF) << 4 | ((hex >> 8) & 0xF);
		rgb->g = ((hex >> 4) & 0xF) << 4 | ((hex >> 4) & 0xF);
		rgb->b = ((hex >> 0) & 0xF) << 4 | ((hex >> 0) & 0xF);
	} else if (strlen(token) == 6) {
		rgb->r = (hex >> 16) & 0xFF;
		rgb->g = (hex >>  8) & 0xFF;
		rgb->b = (hex)       & 0xFF;
	} else {
		/* unexpected token size, unexpected format */
		free(rgb);
		return NULL;
	}

	return rgb;
}

_Bool
parse(struct RGB *rgb, char *str)
{
	struct RGB *color;

	if ((color = try_parse_hexrgb(str)) == NULL &&
		(color = try_parse_decrgb(str)) == NULL &&
		(color = try_parse_hsvhsl(str)) == NULL) {
		return false;
	} else {
		rgb->r = color->r;
		rgb->g = color->g;
		rgb->b = color->b;
		return true;
	}
}

