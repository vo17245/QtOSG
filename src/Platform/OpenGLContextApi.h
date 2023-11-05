#pragma once
#ifdef WIN32
#include <Windows.h>
using WindowHandle = HWND;
using OpenGLContextHandle = HGLRC;
using DeviceContextHandle = HDC;
#else
#errro("unknown os")
#endif

class OpenGLContextApi
{
public:
	static bool Init(DeviceContextHandle hdc);
	static bool CreateOpenGLContext(DeviceContextHandle hdc, int major, int minor,
		OpenGLContextHandle& oglch);
	static bool MakeCurrent(DeviceContextHandle hdc,
		OpenGLContextHandle oglch);
	static bool SwapBuffers(DeviceContextHandle hdc);
public:
	//get dc per call
	static bool Init(WindowHandle wh);
	static bool CreateOpenGLContext(WindowHandle wh,int major,int minor,
		OpenGLContextHandle& oglch);
	static bool MakeCurrent(WindowHandle wh,
		OpenGLContextHandle oglch);
	static bool SwapBuffers(WindowHandle wh);
public:
	static void Vsync(bool flag);
	static const char* CurrentContextVersion();
	static bool DeleteOpenGLContext(OpenGLContextHandle oglch);
	static DeviceContextHandle GetDeviceContext(WindowHandle wh);
	static void ReleaseDeviceContext(WindowHandle wh, DeviceContextHandle dc);
};