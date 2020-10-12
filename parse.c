#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bool.h"
#include "color.h"
#include "list.h"
#include "parse.h"
#include "types.h"
#include "result.h"

static struct Color *try_parse_hexrgb(char *token);

struct ccm_list *
parse(struct ccm_list *tokens)
{
	struct ccm_list *colors = UNWRAP(ccm_list_create());

	/* this is not easy. we need to support the
	 * following formats:
	 *     1) blue, green, red, etc
	 *     2) #RGBA
	 *     3) #RRGGBBAA
	 *     4) #RRRRGGGGBBBBAA
	 *     5) RRR,GGG,BBB,AAA
	 *     6) oh, and the #RGB* variants must not require a hashbang
	 *     7) not to mention the HS(L|V) stuff
	 *
	 * thank goodness we're not going to
	 * support HS(L|V)
	 *
	 * note: alpha is ignored as we can't
	 * display it.
	 *
	 * :'(
	 */

	for (struct ccm_list *c = tokens->next; c != NULL; c = c->next) {
		struct Color *color = try_parse_hexrgb(c->data);

		if (color != NULL) {
			UNWRAP(ccm_list_push(colors, color));
		}
	}

	return colors;
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
