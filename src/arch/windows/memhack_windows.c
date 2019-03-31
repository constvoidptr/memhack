#include <memhack/memhack.h>

#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <TlHelp32.h>


struct mh_process {
	DWORD pid;
	HANDLE handle;
};

enum mh_error mh_process_attach(struct mh_process **process, const char *target_name)
{
	if (!target_name)
		return MH_ERROR_INVALID_PARAMETER;

	struct mh_process *tmp_process = malloc(sizeof(*tmp_process));
	if (!tmp_process)
		return MH_ERROR_MEMORY_ALLOCATION;
	memset(tmp_process, 0, sizeof(*tmp_process));

	HANDLE snapshot;
	PROCESSENTRY32 entry;

	// Take a snapshot of all running processes
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE)
	{
		free(tmp_process);
		return MH_ERROR_GENERIC;
	}

	// Set entry size before use, required by Microsoft
	entry.dwSize = sizeof(entry);

	// Step over processes and set pid, if found
	while (Process32Next(snapshot, &entry) && !tmp_process->pid)
	{
		if (strcmp(entry.szExeFile, target_name) == 0)
			tmp_process->pid = entry.th32ProcessID;
	}

	if (CloseHandle(snapshot) == FALSE)
	{
		free(tmp_process);
		return MH_ERROR_GENERIC;
	}

	if (!tmp_process->pid)
	{
		free(tmp_process);
		return MH_ERROR_PROCESS_NOT_FOUND;
	}

	// Open process
	tmp_process->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, tmp_process->pid);
	if (tmp_process->handle == INVALID_HANDLE_VALUE)
	{
		free(tmp_process);
		return MH_ERROR_GENERIC;
	}

	*process = tmp_process;
	return MH_SUCCESS;
}

enum mh_error mh_process_detach(struct mh_process *process)
{
	if (!process)
		return MH_ERROR_INVALID_PARAMETER;

	if (CloseHandle(process->handle) == FALSE)
		return MH_ERROR_GENERIC;

	free(process);
	return MH_SUCCESS;
}

enum mh_error mh_memory_read(const struct mh_process *process, void *src, void *dst, unsigned int size)
{
	if (!process || !src || !dst || !size)
		return MH_ERROR_INVALID_PARAMETER;

	SIZE_T num_bytes_read;

	if (!ReadProcessMemory(process->handle, src, dst, size, &num_bytes_read) || size != num_bytes_read)
		return MH_ERROR_GENERIC;

	return MH_SUCCESS;
}