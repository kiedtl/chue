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

const char *optstr  = "Vhcxdvl";
const char *helpstr = "usage: chue [-Vhcxdvl] [FILE]...\n"
			 "Copyright (c) 2020 Kiëd Llaentenn\n\n"
			 "If no FILE, read colors from stdin.\n\n"
			 "Options:\n"
			 "    -V    Print version.\n"
			 "    -h    Print this help message.\n"
			 "    -c    Do not print the color bar.\n"
			 "    -x    Do not print the color value.\n"
			 "    -d    Print the color in decimal RGB form.\n"
			 "    -v    Print the color in HSV form.\n"
			 "    -l    Print the color in HSL form.\n\n"
			 "Examples:\n"
			 "    echo '#ababab' | ./chue\n"
			 "    echo 'hsl(23,0.04,0.02)' | ./chue -v\n"
			 "    echo '234,29,65' | ./chue -x\n";

int
main(int argc, char **argv)
{
	struct Options opts;
	opts.display_color  = TRUE;
	opts.display = HEXRGB;

	/* parse arguments */
	isize opt = 0;
        while ((opt = getopt(argc, argv, "Vhcxdvl")) != -1) {
		switch (opt) {
		case 'c': /* disable color */
			opts.display_color = FALSE;
			break;
		case 'v': /* enable hsv */
			opts.display = HSV;
			break;
		case 'l': /* enable hsl */
			opts.display = HSL;
			break;
		case 'x': /* disable printing colors */
			opts.display = NONE;
			break;
		case 'd': /* enable decimal rgb */
			opts.display = DECRGB;
			break;
		case 'V': /* show version */
			printf("chue v%s\n", VERSION);
			return 0;
			break;
		case 'h':
			printf("%s", helpstr); return 0;
			break;
		default:
			fprintf(stderr, "usage: %s [-%s]\n", argv[0], optstr);
			return 1;
			break;
		}
	}

	struct ccm_list *paths = UNWRAP(ccm_list_create());

	if (optind >= argc) {
		/* just push stdin if no paths provided */
		UNWRAP(ccm_list_push(paths, (void*) "-"));
	} else {
		while (optind < argc)
			UNWRAP(ccm_list_push(paths, (void*) argv[++optind]));
	}

	/* foreach path, read, lex, parse, and display */
	for (struct ccm_list *c = paths->next; c != NULL; c = c->next) {
		u8 *buf = NULL;
		usize read = read_to_end(c->data, &buf); // TODO: handle err
		struct ccm_list *tokens = lex(buf, read); // TODO: handle err
		struct ccm_list *colors = parse(tokens);  // TODO: handle err
		display(colors, &opts);
		free(buf);
		UNWRAP(ccm_list_destroy(tokens));
		UNWRAP(ccm_list_destroy(colors));
	}

	UNWRAP(ccm_list_destroy(paths));
	return 0;
}
