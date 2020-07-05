#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "display.h"
#include "types.h"

void
display(struct ccm_list *colors)
{
	for (struct ccm_list *c = colors->next; c != NULL; c = c->next) {
		printf(
			"#%02x%02x%02x\t\033[48;2;%i;%i;%im\033[K\033[0m\n",
			((struct Color *) c->data)->red,
			((struct Color *) c->data)->green,
			((struct Color *) c->data)->blue,
			((struct Color *) c->data)->red,
			((struct Color *) c->data)->green,
			((struct Color *) c->data)->blue
		);
	}
}
