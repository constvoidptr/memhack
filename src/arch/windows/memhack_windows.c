/*
 * Implementation of all windows specific API functions.
 */

#include <memhack/memhack.h>

#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <TlHelp32.h>

struct mh_process {
	DWORD pid;
	HANDLE handle;
};

enum mh_error mh_process_attach_by_pid(struct mh_process **process, const int pid)
{
	struct mh_process *tmp_process = malloc(sizeof (*tmp_process));
	if (!tmp_process)
		return MH_ERROR_MEMORY_ALLOCATION;
	memset(tmp_process, 0, sizeof (*tmp_process));

	tmp_process->pid = pid;
	tmp_process->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (tmp_process->handle == INVALID_HANDLE_VALUE)
	{
		free(tmp_process);
		return MH_ERROR_GENERIC;
	}

	*process = tmp_process;
	return MH_SUCCESS;
}

enum mh_error mh_process_attach_by_name(struct mh_process **process, const char *name)
{
	if (!name)
		return MH_ERROR_INVALID_PARAMETER;

	DWORD pid = 0;
	HANDLE snapshot;
	PROCESSENTRY32 entry;

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

enum mh_error mh_process_detach(struct mh_process *process)
{
	if (!process)
		return MH_ERROR_INVALID_PARAMETER;

	if (!CloseHandle(process->handle))
		return MH_ERROR_GENERIC;

	free(process);
	return MH_SUCCESS;
}

enum mh_error mh_memory_read(const struct mh_process *process, void *src, void *dst, unsigned int size)
{
	if (!process || !src || !dst || !size)
		return MH_ERROR_INVALID_PARAMETER;

	SIZE_T num_bytes_read;

	if (!ReadProcessMemory(process->handle, src, dst, size, &num_bytes_read) || num_bytes_read != size)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}

enum mh_error mh_memory_write(const struct mh_process *process, void *src, void *dst, unsigned int size)
{
	if (!process || !src || !dst || !size)
		return MH_ERROR_INVALID_PARAMETER;

	SIZE_T num_bytes_written;

	if (!WriteProcessMemory(process->handle, dst, src, size, &num_bytes_written) || num_bytes_written != size)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}
