/*
* 参考文档: https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
*/
#pragma once
#ifdef WIN32
#include <Windows.h>
class WindowsOpenGLContextApi
{
private://for create dummy context
	static bool SetPixelFormat(HDC hdc);
	static void CreateOpenGLContext(HDC hdc,  HGLRC& hglrc);
	static bool CreateDummyContext(HDC hdc, HGLRC& hglrc);
private:
	static bool LoadOpenGLFunctions();	
public:
	static bool MakeCurrent(HDC hdc, HGLRC hglrc);
	static bool DeleteOpenGLContext(HGLRC hglrc);
public:
	static bool Init(HDC hdc);
	static bool CreateContext(HDC hdc,int major,int minor,HGLRC& hglrc);
	static const char* CurrentContextVersion();
	static void Vsync(bool flag);
	static bool SwapBuffers(HDC dc);
	static HDC GetDeviceContext(HWND wh);
	static void ReleaseDeviceContext(HWND hwnd,HDC dc);
};
#endif