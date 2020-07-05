#include <stdio.h>
#include <stdlib.h>

#include "result.h"

struct ccm_result *
__ccm_result_ok(void *val)
{
	struct ccm_result *r = malloc(sizeof(struct ccm_result));
	if (r == NULL) return NULL;

	r->is_ok = TRUE;
	r->result = val;
	return r;
}

struct ccm_result *
__ccm_result_err(char *errs)
{
	struct ccm_result *r = malloc(sizeof(struct ccm_result));
	if (r == NULL) return NULL;

	r->is_ok = FALSE;
	r->errmsg = errs;
	return r;
}

void *
__ccm_result_unwrap(struct ccm_result *r, char *expr, char *file, usize line, const char *fn)
{
	if (r == NULL || !r->is_ok) {
		/* the only case in which r could be null
		 * was if it wasn't allocated properly */
		char *errmsg = "(allocation failure)";
		if (r != NULL) errmsg = r->errmsg;

		/* panic */
		/* TODO: nicer output */
		fprintf(stderr, "fatal: attempt to unwrap result '%s' on error:\n",
			expr);
		fprintf(stderr, "\t\t'%s'\n", errmsg);
		fprintf(stderr, "\tat %s:%d in %s\n", file, line, fn);
		exit(12);
	}

	void *result = r->result;
	free(r);
	return result;
}
