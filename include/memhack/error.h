#ifndef MH_ERROR_H
#define MH_ERROR_H

enum mh_error {
	MH_SUCCESS,
	MH_ERROR_GENERIC,
	MH_ERROR_INVALID_PARAMETER,
	MH_ERROR_MEMORY_ALLOCATION,
	MH_ERROR_PROCESS_NOT_FOUND
};

const char * mh_resolve_error(enum mh_error error);

#endif