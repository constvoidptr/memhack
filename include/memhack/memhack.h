/*
 * This file defines all library function calls. It is written in a
 * system-agnostic way, so there are no system specific types except inside
 * macros guards. Furthermore, all functions return an enum mh_error to provide
 * a consistent API.
 */

#ifndef MH_MEMHACK_H
#define MH_MEMHACK_H

#include <inttypes.h>

#include "error.h"
#include "linkage.h"

// Opaque struct that abstracts the system specific implementation
typedef struct mh_process mh_process_t;

/*
 * mh_process_attach_by_pid - Attach to your target process given the process
 * id. Attaching to the process is required before using any other API call.
 *
 * @process: Double pointer to the mh_process struct
 * @pid:     Process id of the target process
 *
 * Returns:  Enum of type mh_error_t
 */
DECLSPEC mh_error_t
mh_process_attach_by_pid(mh_process_t **process, int32_t pid);

/*
 * Only available under Windows, the Linux kernel does not provide an API get
 * all processes by name. Would have to parse /proc. This will probably be
 * added later.
 */
#if defined(_WIN32)

/*
 * mh_process_attach_by_name - Attach to your target process given the process
 * name. Attaching to the process is required before using any other API call.
 *
 * @process: Double pointer to the mh_process struct
 * @name:    Name of the target process
 *
 * Returns:  Enum of type mh_error_t
 */
DECLSPEC mh_error_t
mh_process_attach_by_name(mh_process_t **process, const char *name);

#endif

/*
 * mh_process_detach - Detaches from your target process and frees memory. Every
 * API call using a mh_process after detaching will result in undefined
 * behaviour.
 *
 * @process: Pointer to the mh_process struct
 *
 * Returns:  Enum of type mh_error_t
 */
DECLSPEC mh_error_t
mh_process_detach(mh_process_t *process);

/*
 * mh_memory_read - Copies memory out of the virtual address space of the target
 * process into your process.
 *
 * @process: Pointer to the mh_process struct
 * @src:     Source location from where the memory is being copied
 * @dst:     Destination of the buffer where the memory is written to
 * @size:    Amount of bytes you want to copy. This SHOULD NOT exceed the size
 *           your buffer - would result in an overflow.
 *
 * Returns:  Enum of type mh_error_t
 */
DECLSPEC mh_error_t
mh_memory_read(const mh_process_t *process, void *src, void *dst, uint32_t size);

/*
 * mh_memory_read - Copies memory from your process into the targets' memory,
 * considering the virtual address space.
 *
 * @process: Pointer to the mh_process struct
 * @src:     Source location from where the memory is being copied
 * @dst:     Destination of where the memory should be copied to
 * @size:    Amount of bytes you want to copy. This SHOULD NOT exceed the size
 *           of the targets process buffer - would result in an overflow.
 *
 * Returns: Enum of type mh_error_t
 */
DECLSPEC mh_error_t
mh_memory_write(const mh_process_t *process, void *src, void *dst, uint32_t size);

#endif
