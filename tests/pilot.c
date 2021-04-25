/* usage: pilot [v|l] [f|t] [a] [b] [c] */

#include <stdio.h>
#include <stdlib.h>
#include "color.c"

int
main(int argc, char **argv)
{
	if (argc < 4) {
		fprintf(stderr, "can't make bricks without clay\n");
		return 1;
	}

	if (argv[1][0] == 'f') {
		struct RGB *rgb = NULL;

		double h    = strtod(argv[3], NULL);
		double s    = strtod(argv[4], NULL);
		double vorl = strtod(argv[5], NULL);

		if (argv[2][0] == 'v') {
			rgb = rgb_from_hsv(h, s, vorl);
		} else if (argv[2][0] == 'l') {
			rgb = rgb_from_hsl(h, s, vorl);
		} else {
			fprintf(stderr, "dumbass, just what do you think you're doing\n");
			return 1;
		}

		printf("%x%x%x", rgb->r, rgb->g, rgb->b);
		free(rgb);
	} else if (argv[1][0] == 't') {
		int r = strtol(argv[3], NULL, 16);
		int g = strtol(argv[4], NULL, 16);
		int b = strtol(argv[5], NULL, 16);
		struct RGB rgb = { r, g, b };

		if (argv[2][0] == 'v') {
			struct HSV *hsv = hsv_from_rgb(&rgb);
			printf("%.0f %.0f %.0f",
				round(hsv->h), round(hsv->s), round(hsv->v));
			free(hsv);
		} else if (argv[2][0] == 'l') {
			struct HSL *hsl = hsl_from_rgb(&rgb);
			printf("%.0f %.0f %.0f",
				round(hsl->h), round(hsl->s), round(hsl->l));
			free(hsl);
		}
	}
}
