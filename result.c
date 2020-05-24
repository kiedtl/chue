#include <stdio.h>
#include <stdlib.h>

#include "result.h"

void *
__ccm_result_unwrap(struct ccm_result *r, char *expr, char *file, usize line, const char *fn)
{
	if (!r->is_ok) {
		/* panic */
		fprintf(stderr, "fatal: attempt to unwrap result '%s' on error:\n",
			expr);
		fprintf(stderr, "\t\t'%s'\n", r->errmsg);
		fprintf(stderr, "\tat %s:%d in %s\n", file, line, fn);
		exit(12);
	}

	return r->result;
}
