#include "OpenGLContextApi.h"
#ifdef WIN32
#include "WindowsOpenGLContextApi.h"
#endif
bool OpenGLContextApi::Init(DeviceContextHandle hdc)
{
#ifdef WIN32
	return WindowsOpenGLContextApi::Init(hdc);
#endif
}
bool OpenGLContextApi::CreateOpenGLContext(DeviceContextHandle hdc, int major, int minor, OpenGLContextHandle& oglch)
{
#ifdef WIN32
	HGLRC hglrc;
	if (!WindowsOpenGLContextApi::CreateContext(hdc, major, minor, hglrc))
	{
		return false;
	}
	oglch = hglrc;
	return true;
#endif
}
bool OpenGLContextApi::MakeCurrent(DeviceContextHandle hdc, OpenGLContextHandle oglch)
{
#ifdef WIN32
	return WindowsOpenGLContextApi::MakeCurrent(hdc, oglch);
#endif
}
bool OpenGLContextApi::SwapBuffers(DeviceContextHandle hdc)
{
#ifdef WIN32
	return WindowsOpenGLContextApi::SwapBuffers(hdc);
#endif
}
bool OpenGLContextApi::Init(WindowHandle wh)
{
#ifdef WIN32
	HDC hdc = GetDC(wh);
	bool ret=WindowsOpenGLContextApi::Init(hdc);
	ReleaseDC(wh, hdc);
	return ret;
#endif

}
bool OpenGLContextApi::CreateOpenGLContext(WindowHandle wh, int major, int minor, OpenGLContextHandle& oglch)
{
#ifdef WIN32
	HDC hdc=GetDC(wh);
	HGLRC hglrc;
	if (!WindowsOpenGLContextApi::CreateContext(hdc, major, minor, hglrc))
	{
		ReleaseDC(wh, hdc);
		return false;
	}
	oglch = hglrc;
	ReleaseDC(wh, hdc);
	return true;
#endif
	
}

bool OpenGLContextApi::MakeCurrent(WindowHandle wh, OpenGLContextHandle oglch)
{
#ifdef WIN32
	HDC hdc = GetDC(wh);
	bool ret = WindowsOpenGLContextApi::MakeCurrent(hdc, oglch);
	ReleaseDC(wh, hdc);
	return ret;
#endif
}

bool OpenGLContextApi::DeleteOpenGLContext(OpenGLContextHandle oglch)
{
#ifdef WIN32
	
	return WindowsOpenGLContextApi::DeleteOpenGLContext(oglch);
#endif 
}

DeviceContextHandle OpenGLContextApi::GetDeviceContext(WindowHandle wh)
{
#ifdef WIN32
	return WindowsOpenGLContextApi::GetDeviceContext(wh);
#endif
}

void OpenGLContextApi::ReleaseDeviceContext(WindowHandle wh, DeviceContextHandle dc)
{
#ifdef WIN32
	return WindowsOpenGLContextApi::ReleaseDeviceContext(wh,dc);
#endif
}



const char* OpenGLContextApi::CurrentContextVersion()
{
#ifdef WIN32
	return WindowsOpenGLContextApi::CurrentContextVersion();
#endif
	
}

void OpenGLContextApi::Vsync(bool flag)
{
#ifdef WIN32
	WindowsOpenGLContextApi::Vsync(flag);
#endif
}

bool OpenGLContextApi::SwapBuffers(WindowHandle wh)
{
#ifdef WIN32
	HDC hdc = GetDC(wh);
	bool ret=WindowsOpenGLContextApi::SwapBuffers(hdc);
	ReleaseDC(wh, hdc);
	return ret;
#endif
}
