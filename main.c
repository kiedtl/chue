#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bool.h"
#include "color.h"
#include "die.h"
#include "display.h"
#include "lex.h"
#include "list.h"
#include "read.h"
#include "options.h"
#include "parse.h"
#include "types.h"

int
main(int argc, char **argv)
{
	struct Options opts;
	opts.display_color  = TRUE;
	opts.display_hexrgb = TRUE;
	opts.display_decrgb = FALSE;
	opts.display_hsl    = FALSE;
	opts.display_hsv    = FALSE;

	/* parse arguments */
	isize opt = 0;
        while ((opt = getopt(argc, argv, "cxdlvhV") != -1)) {
		switch (opt) {
		case 'c': /* disable color */
			opts.display_color = FALSE;
			break;
		case 'x': /* disable hex rgb */
			opts.display_hexrgb = FALSE;
			break;
		case 'd': /* enable decimal rgb */
			opts.display_decrgb = TRUE;
			break;
		case 'l': /* enable hsl */
			opts.display_hsl = TRUE;
			break;
		case 'v': /* enable hsv */
			opts.display_hsv = TRUE;
			break;
		case 'h': /* show help */
			printf("usage: chue [-xcdlvhV]\n");
			return 0;
			break;
		case 'V': /* show version */
			printf("chue v%s\n", VERSION);
			return 0;
			break;
		default:
			die("chue: error: invalid argument.");
			break;
		}
	}

	struct ccm_list *paths = ccm_list_create(); // TODO: err checking

	if (optind >= argc) {
		/* just push stdin if no paths provided */
		ccm_list_push(paths, (void*) "-"); // TODO: err checking
	} else {
		while (optind < argc)
			ccm_list_push(paths, (void*) argv[++optind]); // TODO: err checking
	}

	/* foreach path, read, lex, parse, and display */
	for (struct ccm_list *c = paths->next; c != NULL; c = c->next) {
		u8 *buf = NULL;
		usize read = read_to_end(c->data, &buf); // TODO: handle err
		struct ccm_list *tokens = lex(buf, read); // TODO: handle err
		struct ccm_list *colors = parse(tokens);  // TODO: handle err
		display(colors);
		free(buf);
	}

	return 0;
}
