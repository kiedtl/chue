#include <stdio.h>
#include <stdlib.h>

#include "result.h"

void *
__ccm_result_unwrap(struct ccm_result *r, char *expr, char *file, usize line, char *fn)
{
	if (!r->is_ok) {
		/* panic */
		fprintf(stderr, "fatal: function '%s': ", fn);
		fprintf(stderr, "unwrap '%s' on an error value: '%s'.\n",
			expr, errmsg);
		fprintf(stderr, "\tat %s:%s\n", file, line);
		exit(12);
	}

	return r->result;
}
