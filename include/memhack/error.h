/*
 * Defines the library error type and all functions in relation with that.
 */

#ifndef MH_ERROR_H
#define MH_ERROR_H

#include "linkage.h"

/* 
 * The library return type. MH_SUCCESS and MH_ERROR_GENERIC are guaranteed to
 * be 0 and 1 the order of the others is not.
 */
enum mh_error {
	MH_SUCCESS,
	MH_ERROR_GENERIC,
	MH_ERROR_INVALID_PARAMETER,
	MH_ERROR_MEMORY_ALLOCATION,
	MH_ERROR_PROCESS_NOT_FOUND
};

/*
 * mh_resolve_error - Resolves error type into a string.
 *
 * @error: The type of error
 *
 * Returns: A constant error message string
 */
DECLSPEC const char * mh_resolve_error(enum mh_error error);

#endif
