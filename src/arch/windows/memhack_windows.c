/*
 * Implementation of all windows specific API functions.
 */

#include <memhack/memhack.h>
#include <memhack/debug.h>

#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <TlHelp32.h>

struct mh_process {
	DWORD pid;
	HANDLE handle;
};

mh_error_t
mh_process_attach_by_pid(mh_process_t **process, int32_t pid)
{
	mh_process_t *tmp_process;

	tmp_process = malloc(sizeof(*tmp_process));
	ASSERT(tmp_process != NULL);

	tmp_process->pid = pid;
	tmp_process->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (tmp_process->handle == NULL || tmp_process->handle == INVALID_HANDLE_VALUE)
	{
		free(tmp_process);
		// TODO Return concrete error type
		return MH_ERROR_GENERIC;
	}

	*process = tmp_process;
	return MH_SUCCESS;
}

mh_error_t
mh_process_attach_by_name(mh_process_t **process, const char *name)
{
	DWORD pid = 0;
	HANDLE snapshot;
	PROCESSENTRY32 entry;

	ASSERT(name != NULL);

	// Take a snapshot of all running processes
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
		return MH_ERROR_GENERIC;

	// Set entry size before use, required by Microsoft
	entry.dwSize = sizeof(entry);

	// Step over processes and set pid, if found
	while (Process32Next(snapshot, &entry) && !pid)
	{
		if (strcmp(entry.szExeFile, name) == 0)
			pid = entry.th32ProcessID;
	}

	if (!CloseHandle(snapshot))
		return MH_ERROR_GENERIC;

	if (!pid)
		return MH_ERROR_PROCESS_NOT_FOUND;

	return mh_process_attach_by_pid(process, pid);
}

mh_error_t
mh_process_detach(mh_process_t *process)
{
	ASSERT(process != NULL);

	if (!CloseHandle(process->handle))
		return MH_ERROR_GENERIC;

	free(process);
	return MH_SUCCESS;
}

mh_error_t
mh_memory_read(const mh_process_t *process, void *src, void *dst, uint32_t size)
{
	SIZE_T num_bytes_read;

	ASSERT(process != NULL);
	ASSERT(src != NULL);
	ASSERT(dst != NULL);
	ASSERT(size > 0);

	if (!ReadProcessMemory(process->handle,
						   src,
						   dst,
						   size,
						   &num_bytes_read) || num_bytes_read != size)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}

mh_error_t
mh_memory_write(const mh_process_t *process, void *src, void *dst, uint32_t size)
{
	SIZE_T num_bytes_written;

	ASSERT(process != NULL);
	ASSERT(src != NULL);
	ASSERT(dst != NULL);
	ASSERT(size > 0);

	if (!WriteProcessMemory(process->handle,
							dst,
							src,
							size,
							&num_bytes_written) || num_bytes_written != size)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}
