/*
 * This file defines all library function calls. It is written in a
 * system-agnostic way, so there are no system specific types except inside
 * macros guards. Furthermore, all functions return an enum mh_error to provide
 * a consistant API.
 */

#ifndef MH_MEMHACK_H
#define MH_MEMHACK_H

#include "error.h"

/*
 * Export/import function calls from/to dynamic link libraries based on whether
 * library ist build statically or dynamically is defined. MH_BUILD_STATIC for
 * static linkage, MH_BUILD_DYNAMIC for dynamic linkage. Omit both if you are
 * not building the library.
 */
#if !defined(DECLSPEC)

#if defined(MH_BUILD_STATIC) && defined(MH_BUILD_DYNAMIC)
#	error "Cannot build for static and dynamic linkage at the same time"
#endif

#if defined(_WIN32)
#	if defined(MH_BUILD_STATIC)
#		define DECLSPEC
#	elif defined(MH_BUILD_DYNAMIC)
#		define DECLSPEC __declspec(dllexport)
#	else
#		define DECLSPEC __declspec(dllimport)
#	endif
#else
#	define DECLSPEC
#endif

#endif

// Opaque struct that abstracts the system specific implementation
struct mh_process;

/*
 * mh_process_attach_by_pid - Attach to your target process given the process
 * id. Attaching to the process is required before using any other API call.
 *
 * @process: Double pointer to the mh_process struct
 * @pid:     Process id of the target process
 *
 * Returns:  Enum of type mh_error
 */
DECLSPEC enum mh_error mh_process_attach_by_pid(struct mh_process **process, const int pid);

/*
 * mh_process_attach_by_name - Attach to your target process given the process
 * name. Attaching to the process is required before using any other API call.
 *
 * @process: Double pointer to the mh_process struct
 * @name:    Name of the target process
 *
 * Returns:  Enum of type mh_error
 */
DECLSPEC enum mh_error mh_process_attach_by_name(struct mh_process **process, const char *name);

/*
 * mh_process_detach - Detaches from your target process and frees memory. Every
 * API call using a mh_process after detaching will result in undefined
 * behaviour.
 *
 * @process: Pointer to the mh_process struct
 *
 * Returns:  Enum of type mh_error
 */
DECLSPEC enum mh_error mh_process_detach(struct mh_process *process);

/*
 * mh_memory_read - Copies memory out of the virtual address space of the target
 * process into your process.
 *
 * @process: Pointer to the mh_process struct
 * @src:     Source location from where the memory is beeing copied
 * @dst:     Destination of the buffer where the memory is written to
 * @size:    Amount of bytes you want to copy. This SHOULD NOT exceed the size
 *           your buffer - would result in an overflow.
 *
 * Returns:  Enum of type mh_error
 */
DECLSPEC enum mh_error mh_memory_read(const struct mh_process *process, void *src, void *dst, unsigned int size);

/*
 * mh_memory_read - Copies memory from your process into the targets memory,
 * considering the virtual addess space.
 *
 * @process: Pointer to the mh_process struct
 * @src:     Source location from where the memory is beeing copied
 * @dst:     Destination of where the memory should be copied to
 * @size:    Amount of bytes you want to copy. This SHOULD NOT exceed the size
 *           of the targets process buffer - would result in an overflow.
 *
 * Returns: Enum of type mh_error
 */
DECLSPEC enum mh_error mh_memory_write(const struct mh_process *process, void *src, void *dst, unsigned int size);

#endif
