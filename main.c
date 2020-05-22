#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "color.h"
#include "display.h"
#include "lex.h"
#include "list.h"
#include "read.h"
#include "parse.h"
#include "types.h"

int
main(int argc, char **argv)
{
	/* TODO: move this whole thing to arg parsing section */
	/* get list of files */
	struct CCMList *paths = ccm_list_create(); // TODO: err checking

	if (argc < 2) {
		/* just push stdin if no paths provided */
		ccm_list_push(paths, (void*) "-"); // TODO: err checking
	} else {
		/* otherwise... */
		for (int i = 1; i < argc; ++i)
			ccm_list_push(paths, (void*) argv[i]); // TODO: err checking
	}

	/* foreach path, read, lex, parse, and display */
	for (struct CCMList *c = paths->next; c != NULL; c = c->next) {
		u8 *buf = NULL;
		usize read = read_to_end(c->data, &buf); // TODO: handle err
		struct CCMList *tokens = lex(buf, read); // TODO: handle err
		struct CCMList *colors = parse(tokens);  // TODO: handle err
		display(colors);
		free(buf);
	}

	return 0;
}
