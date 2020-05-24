/*
 * quick 'n dirty result
 */

#ifndef RESULT_H
#define RESULT_H

#include "assert.h"
#include "bool.h"
#include "types.h"

struct ccm_result {
	bool is_ok;
	union {
		void *result;
		char *errmsg;
	};
};

/* unwrap value, and abort if error */
#define UNWRAP(R) __ccm_result_unwrap((R), #R, __FILE__, __LINE__, __func__);

/* return OK in Result with Error null */
#define RESULT_OK(V)  &((struct ccm_result) { .is_ok = TRUE, .result  = (void*) V });

/* return Error in Result with value null */
#define RESULT_ERR(E) &((struct ccm_result) { .is_ok = FALSE, .errmsg = (char*) E });

/* prototype */
void *__ccm_result_unwrap(
	struct ccm_result *r,
	char *expr,
	char *file,
	usize line,
	const char *func
);

#endif
