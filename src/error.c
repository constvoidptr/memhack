/*
 * Implementation of all error related functions.
 */

#include <memhack/error.h>

const char *
mh_error_resolve(mh_error_t error)
{
	switch (error) {
		case MH_SUCCESS:
			return "Operation successful";
		case MH_ERROR_GENERIC:
			return "Generic error";
		case MH_ERROR_PROCESS_NOT_FOUND:
			return "Process not found";
		default:
			return "Unknown error";
	}
}