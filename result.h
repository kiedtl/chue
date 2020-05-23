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

/* error messages */
#define CCM_RES_ALLOC_ERROR    "Allocation failure"
#define CCM_RES_UNKNOWN_ERROR  "Unknown error"
#define CCM_RES_SYSTEM_ERROR   strerror(errno)
#define CCM_RES_NULL_ERROR     "Unexpected NULL value"

/* unwrap value, and abort if error */
#define CCM_RES_UNWRAP(R) __ccm_result_unwrap((R), #R, __FILE__, __LINE__, __func__);

/* return OK in Result with Error null */
#define CCM_RES_OK(V)  (struct ccm_result) { .is_ok = TRUE; .result  = (void*) V; };

/* return Error in Result with value null */
#define CCM_RES_ERR(E) (struct ccm_result) { .is_ok = FALSE; .errmsg = (char*) E; };

/* prototype */
void *__ccm_result_unwrap(
	struct ccm_result *r,
	char *expr,
	char *file,
	usize line,
	char *func
);

#endif
