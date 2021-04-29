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
		.display_color_norm = true,
	};

	/* parse arguments */
	ssize_t opt = 0;
        while ((opt = getopt(argc, argv, "Vc:f:")) != -1) {
		switch (opt) {
		case 'c': /* enable/disable color */
			if (!strncmp("norm", optarg, 4))
				opts.display_color_norm = !opts.display_color_norm;
			if (!strncmp("trit", optarg, 4))
				opts.display_color_trit = !opts.display_color_trit;
			if (!strncmp("deut", optarg, 4))
				opts.display_color_deut = !opts.display_color_deut;
			if (!strncmp("prot", optarg, 4))
				opts.display_color_prot = !opts.display_color_prot;
			break;
		case 'f': /* enable/disable format */
			if (!strcmp("hex", optarg))
				opts.display_hex = !opts.display_hex;
			if (!strcmp("dec", optarg))
				opts.display_dec = !opts.display_dec;
			if (!strcmp("hsv", optarg))
				opts.display_hsv = !opts.display_hsv;
			if (!strcmp("hsl", optarg))
				opts.display_hsl = !opts.display_hsl;
			if (!strcmp("xyz", optarg))
				opts.display_xyz = !opts.display_xyz;
			if (!strcmp("lms", optarg))
				opts.display_lms = !opts.display_lms;
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
