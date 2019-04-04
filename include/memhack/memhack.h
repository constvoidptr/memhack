#ifndef MH_MEMHACK_H
#define MH_MEMHACK_H

#include "error.h"

#ifndef DECLSPEC
#	ifdef _WIN32
#		ifdef BUILD_MH
#			define DECLSPEC __declspec(dllexport)
#		else
#			define DECLSPEC __declspec(dllimport)
#		endif
#	else
#		error "Unsupported system!"
#	endif
#endif

struct mh_process;

DECLSPEC enum mh_error mh_process_attach(struct mh_process **process, const char *target_name);
DECLSPEC enum mh_error mh_process_detach(struct mh_process *process);

DECLSPEC enum mh_error mh_memory_read(const struct mh_process *process, void *src, void *dst, unsigned int size);
DECLSPEC enum mh_error mh_memory_write(const struct mh_process *process, void *src, void *dst, unsigned int size);

#endif