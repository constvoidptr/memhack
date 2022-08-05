/*
 * Defines the library error type and all functions in relation with that.
 */

#ifndef MH_ERROR_H
#define MH_ERROR_H

#include "linkage.h"

/* 
 * The library return type. MH_SUCCESS and MH_ERROR_GENERIC are guaranteed to
 * be at position 0 and 1 respectively. The order of the other variants is not specified.
 */
typedef enum {
	MH_SUCCESS = 0,
	MH_ERROR_GENERIC = 1,
	MH_ERROR_INVALID_PARAMETER,
	MH_ERROR_MEMORY_ALLOCATION,
	MH_ERROR_PROCESS_NOT_FOUND
} mh_error_t;

/*
 * mh_error_resolve - Resolves the error type into a string.
 *
 * @error: The type of error
 *
 * Returns: A string describing the error
 */
DECLSPEC const char * mh_error_resolve(mh_error_t error);

#endif
