#include <stdio.h>

#include <Windows.h>

HMODULE hook_module_handle;
HWINEVENTHOOK window_event_hook_handle;

void install_hook()
{
	printf("install_hook...\n");

	hook_module_handle = LoadLibrary(TEXT("Hook32.dll"));

	if (hook_module_handle == 0)
		throw "LoadLibrary";

	WINEVENTPROC hook_process_handle;
	hook_process_handle = (WINEVENTPROC)GetProcAddress(hook_module_handle, "hook_procedure");

	if (hook_process_handle == 0)
		throw "GetProcAddress";

	window_event_hook_handle = SetWinEventHook(
		EVENT_SYSTEM_MOVESIZESTART,
		EVENT_SYSTEM_MOVESIZEEND,
		hook_module_handle,
		hook_process_handle,
		0, //all processes
		0, //all threads
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
		);

	if (window_event_hook_handle == 0)
		throw "SetWinEventHook";
}

void uninstall_hook()
{
	printf("uninstall_hook...\n");

	if (!UnhookWinEvent(window_event_hook_handle))
		throw "UnhookWinEvent";

	if (!FreeLibrary(hook_module_handle))
		throw "FreeLibrary";
}

int main()
{
	printf("main: start\n");

	try
	{
		install_hook();

		MSG message;
		while (GetMessage(&message, NULL, 0, 0))
		{
			printf("message\n");
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		uninstall_hook();
	}
	catch (char* ex)
	{
		printf("exception: %s\n", ex);
		getchar();
	}

	printf("main: end\n");
	getchar();

	return 0;
}
