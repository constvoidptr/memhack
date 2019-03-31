#ifndef MH_MEMHACK_H
#define MH_MEMHACK_H

#include "error.h"

struct mh_process;

enum mh_error mh_process_attach(struct mh_process **process, const char *target_name);
enum mh_error mh_process_detach(struct mh_process *process);

enum mh_error mh_memory_read(const struct mh_process *process, void *src, void *dst, unsigned int size);

#endif