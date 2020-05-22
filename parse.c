#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "color.h"
#include "list.h"
#include "parse.h"
#include "types.h"

static struct Color *try_parse_oldrgb(char *token);
static struct Color *try_parse_hexrgb(char *token);

struct CCMList *
parse(struct CCMList *tokens)
{
	struct CCMList *colors = ccm_list_create(); // TODO: err handling

	/* this is not easy. we need to support the
	 * following formats:
	 *     1) #RGBA
	 *     2) #RRGGBBAA
	 *     3) #RRRRGGGGBBBBAA
	 *     4) RRR,GGG,BBB,AAA
	 *     5) blue, green, red, etc
	 *     6) oh, and the #RGB* variants
	 *        must not require a
	 *        hashbang
	 *
	 * thank goodness we're not going to
	 * support HS(L|V)
	 *
	 * note: alpha is ignored as we can't
	 * display it.
	 *
	 * :'(
	 */

	for (struct CCMList *c = tokens->next; c != NULL; c = c->next) {
		struct Color *color;

		/* try parsing in all formats,
		 * if they all fail then throw an error */

		/* note: the order in which formats are tried
		 * really does matter. Here be dragons! */

		if (
			(color = try_parse_oldrgb(c->data)) == NULL &&
			(color = try_parse_hexrgb(c->data)) == NULL
		) {
			fprintf(stderr, "chue: warning: "
				"ignoring malformed color: '%s'\n",
				(char*) c->data);
		} else {
			ccm_list_push(colors, color);
		}
	}

	return colors;
}

static struct Color *
try_parse_oldrgb(char *token) /* RRR,GGG,BBB */
{
	usize len = strlen(token);

	/* if token doesn't contain commas
	 * then it's not in this format */
	bool hascomma = FALSE;
	for (usize i = 0; i < len; ++i) {
		if (token[i] == ',') {
			hascomma = TRUE;
			break;
		}
	}

	if (!hascomma) return NULL;

	struct Color *rgb = calloc(1, sizeof(struct Color));
	rgb->red = rgb->green = rgb->blue = 0;

	char *eptr = token;
	rgb->red   = strtol(token, &eptr, 10); token = eptr + 1;
	rgb->green = strtol(token, &eptr, 10); token = eptr + 1;
	rgb->blue  = strtol(token, &eptr, 10);

	return rgb;
}

static struct Color *
try_parse_hexrgb(char *token) /* [#]R[RRR]G[GGG]B[BBB]A[AAA] */
{
	while (isspace(*token)) ++token;
	if (*token == '#') ++token;

	/* TODO: allow numbers of format other than #RRGGBB */
	if (strlen(token) != 6) return NULL;

	struct Color *rgb = calloc(1, sizeof(struct Color));
	rgb->red = rgb->green = rgb->blue = 0;

	usize hex  = (usize) strtol(token, NULL, 16);
	rgb->red   = (hex >> 16) & 0xFF;
	rgb->green = (hex >>  8) & 0xFF;
	rgb->blue  = (hex      ) & 0xFF;

	return rgb;
}
