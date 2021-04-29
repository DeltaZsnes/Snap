#include <stdio.h>
#include <vector>

#include <Windows.h>

struct RectangleRectangle
{
	int al, at, ar, ab;
	int bl, bt, br, bb;
};

std::vector<RectangleRectangle> rectangles;
std::vector<HMONITOR> monitor_handles;

BOOL CALLBACK monitor_enumeration_process(
	_In_  HMONITOR hMonitor,
	_In_  HDC hdcMonitor,
	_In_  LPRECT lprcMonitor,
	_In_  LPARAM dwData
	)
{
	monitor_handles.push_back(hMonitor);
	return TRUE;
}

void construct_rectangles_for_monitor(HMONITOR monitor_handle)
{
	MONITORINFO monitor_info;
	monitor_info.cbSize = sizeof(MONITORINFO);
	if (!GetMonitorInfo(monitor_handle, &monitor_info))
		throw "GetMonitorInfo";

	//printf("%d %d %d %d\n", monitor_info.rcMonitor.left, monitor_info.rcMonitor.top, monitor_info.rcMonitor.right, monitor_info.rcMonitor.bottom);
	int horisontal_marginal = (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 20;
	int vertical_marginal = (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 20;;

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.left;
		rr.at = monitor_info.rcMonitor.top;
		rr.ar = monitor_info.rcMonitor.left + horisontal_marginal;
		rr.ab = monitor_info.rcMonitor.top + vertical_marginal;

		rr.bl = monitor_info.rcMonitor.left;
		rr.bt = monitor_info.rcMonitor.top;
		rr.br = monitor_info.rcMonitor.left + (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 2;
		rr.bb = monitor_info.rcMonitor.top + (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 2;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.right - horisontal_marginal;
		rr.at = monitor_info.rcMonitor.top;
		rr.ar = monitor_info.rcMonitor.right;
		rr.ab = monitor_info.rcMonitor.top + vertical_marginal;

		rr.bl = monitor_info.rcMonitor.right - (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 2;
		rr.bt = monitor_info.rcMonitor.top;
		rr.br = monitor_info.rcMonitor.right;
		rr.bb = monitor_info.rcMonitor.top + (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 2;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.left;
		rr.at = monitor_info.rcMonitor.bottom - vertical_marginal;
		rr.ar = monitor_info.rcMonitor.left + horisontal_marginal;
		rr.ab = monitor_info.rcMonitor.bottom;

		rr.bl = monitor_info.rcMonitor.left;
		rr.bt = monitor_info.rcMonitor.top + (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 2;;
		rr.br = monitor_info.rcMonitor.left + (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 2;
		rr.bb = monitor_info.rcMonitor.bottom;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.right - horisontal_marginal;
		rr.at = monitor_info.rcMonitor.bottom - vertical_marginal;
		rr.ar = monitor_info.rcMonitor.right;
		rr.ab = monitor_info.rcMonitor.bottom;

		rr.bl = monitor_info.rcMonitor.left + (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 2;
		rr.bt = monitor_info.rcMonitor.top + (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 2;
		rr.br = monitor_info.rcMonitor.right;
		rr.bb = monitor_info.rcMonitor.bottom;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.left;
		rr.at = monitor_info.rcMonitor.top + vertical_marginal;
		rr.ar = monitor_info.rcMonitor.left + horisontal_marginal;
		rr.ab = monitor_info.rcMonitor.bottom - vertical_marginal;

		rr.bl = monitor_info.rcMonitor.left;
		rr.bt = monitor_info.rcMonitor.top;
		rr.br = monitor_info.rcMonitor.left + (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 2;
		rr.bb = monitor_info.rcMonitor.bottom;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.right - horisontal_marginal;
		rr.at = monitor_info.rcMonitor.top + vertical_marginal;
		rr.ar = monitor_info.rcMonitor.right;
		rr.ab = monitor_info.rcMonitor.bottom - vertical_marginal;

		rr.bl = monitor_info.rcMonitor.right - (monitor_info.rcMonitor.right - monitor_info.rcMonitor.left) / 2;
		rr.bt = monitor_info.rcMonitor.top;
		rr.br = monitor_info.rcMonitor.right;
		rr.bb = monitor_info.rcMonitor.bottom;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.left + horisontal_marginal;
		rr.at = monitor_info.rcMonitor.top;
		rr.ar = monitor_info.rcMonitor.right - horisontal_marginal;
		rr.ab = monitor_info.rcMonitor.top + vertical_marginal;

		rr.bl = monitor_info.rcMonitor.left;
		rr.bt = monitor_info.rcMonitor.top;
		rr.br = monitor_info.rcMonitor.right;
		rr.bb = monitor_info.rcMonitor.bottom - (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 2;
		rectangles.push_back(rr);
	}

	{
		RectangleRectangle rr;
		rr.al = monitor_info.rcMonitor.left + horisontal_marginal;
		rr.at = monitor_info.rcMonitor.bottom - vertical_marginal;
		rr.ar = monitor_info.rcMonitor.right - horisontal_marginal;
		rr.ab = monitor_info.rcMonitor.bottom;

		rr.bl = monitor_info.rcMonitor.left;
		rr.bt = monitor_info.rcMonitor.top + (monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top) / 2;
		rr.br = monitor_info.rcMonitor.right;
		rr.bb = monitor_info.rcMonitor.bottom;
		rectangles.push_back(rr);
	}
}

void construct_rectangles()
{
	monitor_handles.clear();
	rectangles.clear();

	if (!EnumDisplayMonitors(NULL, NULL, monitor_enumeration_process, NULL))
		throw "EnumDisplayMonitors";

	//printf("number of monitors: %d\n", monitor_handles.size());
	for (int ia = 0; ia < monitor_handles.size(); ia++)
	{
		construct_rectangles_for_monitor(monitor_handles[ia]);
	}
}

void draw_rectangles()
{
	HDC device_context_handle;
	device_context_handle = GetDC(NULL);
	if (device_context_handle == 0)
		throw "GetDC";

	SelectObject(device_context_handle, GetStockObject(HOLLOW_BRUSH));
	//SetDCBrushColor(device_context_handle, RGB(0, 0, 255));
	SelectObject(device_context_handle, GetStockObject(DC_PEN));
	SetDCPenColor(device_context_handle, RGB(255, 0, 0));
	//Rectangle(device_context_handle, 1950, 0, 2000, 100);

	for (int ia = 0; ia < rectangles.size(); ia++)
	{
		Rectangle(device_context_handle, rectangles[ia].al, rectangles[ia].at, rectangles[ia].ar, rectangles[ia].ab);
	}

	//SelectObject(device_context_handle, GetStockObject(HOLLOW_BRUSH));
	//SelectObject(device_context_handle, GetStockObject(DC_PEN));
	//SetDCPenColor(device_context_handle, RGB(0, 255, 0));

	//for (int ia = 0; ia < rectangles.size(); ia++)
	//{
	//	Rectangle(device_context_handle, rectangles[ia].bl, rectangles[ia].bt, rectangles[ia].br, rectangles[ia].bb);
	//}
}

__declspec(dllexport) VOID CALLBACK hook_procedure(
	HWINEVENTHOOK window_event_hook_handle,
	DWORD event,
	HWND window_handle,
	LONG object_id,
	LONG child_id,
	DWORD event_thread_id,
	DWORD event_time_ms
	)
{
	printf("hook_procedure... %d %d %d %ld %ld %d %d\n", window_event_hook_handle, event, window_handle, object_id, child_id, event_thread_id, event_time_ms);

	try
	{
		if (event == EVENT_SYSTEM_MOVESIZESTART)
		{
			printf("EVENT_SYSTEM_MOVESIZESTART\n");
			construct_rectangles();
			draw_rectangles();
		}
		else if (event == EVENT_SYSTEM_MOVESIZEEND)
		{
			printf("EVENT_SYSTEM_MOVESIZEEND\n");
			InvalidateRect(NULL, NULL, FALSE);

			//gets the information of the monitor closest to where the mouse was released
			POINT mouse_point;
			if (!GetCursorPos(&mouse_point))
				throw "GetCursorPos";
			printf("mouse: %d %d\n", mouse_point.x, mouse_point.y);

			for (int ia = 0; ia < rectangles.size(); ia++)
			{
				if (rectangles[ia].al <= mouse_point.x && mouse_point.x <= rectangles[ia].ar && rectangles[ia].at <= mouse_point.y && mouse_point.y <= rectangles[ia].ab)
				{
					SetWindowPos(window_handle, HWND_TOP, rectangles[ia].bl, rectangles[ia].bt, rectangles[ia].br - rectangles[ia].bl, rectangles[ia].bb - rectangles[ia].bt, 0);
					break;
				}
			}
		}
	}
	catch (char* ex)
	{
		printf("hook32 exception: %s\n", ex);
	}
}

BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	printf("hook32.dll...\n");
	return TRUE;
}
