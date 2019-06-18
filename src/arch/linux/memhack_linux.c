/*
 * Implementation of all linux specific API functions.
 */

#include <memhack/memhack.h>

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

// Defined so that sys/uio.h includes bits/uio-ext.h
#define __USE_GNU
#include <sys/uio.h>

struct mh_process {
	pid_t pid;
};

enum mh_error mh_process_attach_by_pid(struct mh_process **process, int32_t pid)
{
	/*
	 * Check if the process with the specified pid is running by issuing a kill
	 * system call with signal 0
	 */
	if (kill(pid, 0))
		return MH_ERROR_PROCESS_NOT_FOUND;
	
	struct mh_process *tmp_process = malloc(sizeof (*tmp_process));
	if (!tmp_process)
		return MH_ERROR_MEMORY_ALLOCATION;
	memset(tmp_process, 0, sizeof (*tmp_process));

	tmp_process->pid = pid;
	
	*process = tmp_process;
	return MH_SUCCESS;
}

enum mh_error mh_process_detach(struct mh_process *process)
{
	if (!process)
		return MH_ERROR_INVALID_PARAMETER;

	free(process);
	return MH_SUCCESS;
}

enum mh_error mh_memory_read(const struct mh_process *process, void *src, void *dst, uint32_t size)
{
	if (!process || !src || !dst || !size)
		return MH_ERROR_INVALID_PARAMETER;

	struct iovec iovec[2];

	iovec[0].iov_base = dst;
	iovec[0].iov_len  = size;
	iovec[1].iov_base = src;
	iovec[1].iov_len  = size;

	ssize_t num_bytes_read;
	num_bytes_read = process_vm_readv(process->pid, &iovec[0], 1, &iovec[1], 1, 0);

	if (num_bytes_read < 0 || num_bytes_read != size)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}

enum mh_error mh_memory_write(const struct mh_process *process, void *src, void *dst, uint32_t size)
{
	if (!process || !src || !dst || !size)
		return MH_ERROR_INVALID_PARAMETER;

	struct iovec iovec[2];

	iovec[0].iov_base = src;
	iovec[0].iov_len  = size;
	iovec[1].iov_base = dst;
	iovec[1].iov_len  = size;

	ssize_t num_bytes_written;
	num_bytes_written = process_vm_writev(process->pid, &iovec[0], 1, &iovec[1], 1, 0);

	if (num_bytes_written < 0 || num_bytes_written != size)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}
