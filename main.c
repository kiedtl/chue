#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "color.h"
#include "display.h"
#include "options.h"
#include "parse.h"

#define VERSION "0.1.0"


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

static void
chue(struct Options *opts, char *color)
{
	struct RGB rgb = {0};

	if (!parse(&rgb, color)) {
		fprintf(stderr, "chue: ignore invalid color '%s'.", color);
	} else {
		display(&rgb, opts);
	}
}

int
main(int argc, char **argv)
{
	struct Options opts = {
		.display_hex = true,
		.display_dec = false,
		.display_hsl = false,
		.display_hsv = false,
		.display_xyz = false,
		.display_lms = false,
		.display_color = true,
	};

	/* parse arguments */
	ssize_t opt = 0;
        while ((opt = getopt(argc, argv, "Vhcxdvl")) != -1) {
		switch (opt) {
		case 'c': /* disable color */
			opts.display_color = !opts.display_color;
			break;
		case 'v': /* enable hsv */
			opts.display_hsv = !opts.display_hsv;
			break;
		case 'l': /* enable hsl */
			opts.display_hsl = !opts.display_hsl;
			break;
		case 'x': /* enable xyz */
			opts.display_xyz = !opts.display_xyz;
			break;
		case 'd': /* enable decimal rgb */
			opts.display_dec = !opts.display_dec;
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

	if (optind >= argc) {
		/* just read from stdin if no colors provided */
		char buf[4096] = {0}, *p = (char *)&buf;
		ssize_t ch = -1;
	
		while ((ch = fgetc(stdin)) != EOF) {
			switch (ch) {
			break; case '\n': case ' ':
				*p = '\0';
				chue(&opts, buf);
				buf[0] = '\0', p = (char *)&buf;
			break; default:
				*p = ch, ++p;
			}
		}
	} else {
		while (optind < argc)
			chue(&opts, argv[++optind]);
	}

	return 0;
}
