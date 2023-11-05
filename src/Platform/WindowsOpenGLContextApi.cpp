#ifdef WIN32
#include "WindowsOpenGLContextApi.h"
#include "GL/glew.h"
#include "GL/wglew.h"


bool WindowsOpenGLContextApi::SetPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	/*
	* This function takes a device context and PFD struct and returns a pixel format number. 
	* If it returns 0, then it could not find a pixel format that matches the description,
	* or the PFD was not filled out correctly.
	*/
	int format=ChoosePixelFormat(hdc, &pfd);
	if (format == 0)
	{
		return false;
	}
	/*
	* This function takes the DC, the pixel format number, and a PFD struct pointer.
	* Don't get excited about being able to supply the PFD struct; 
	* it doesn't read any important information out of it 
	* to set the pixel format into the context.
	*/
	if (!::SetPixelFormat(hdc, format, &pfd))
	{
		return false;
	}
	return true;
}
void WindowsOpenGLContextApi::CreateOpenGLContext(HDC hdc, HGLRC& hglrc)
{
	hglrc=wglCreateContext(hdc);
	
}
bool WindowsOpenGLContextApi::MakeCurrent(HDC hdc, HGLRC hglrc)
{
	/*
	* The current context is thread - specific; 
	* each thread can have a different context current, 
	* and it's dangerous to have the same context current in multiple threads. 
	*/
	return wglMakeCurrent(hdc, hglrc);
}
bool WindowsOpenGLContextApi::DeleteOpenGLContext(HGLRC hglrc)
{
	if (!wglMakeCurrent(nullptr, nullptr))
	{
		return false;
	}
	if (!wglDeleteContext(hglrc))
	{
		return false;
	}
	
	return true;
}
bool WindowsOpenGLContextApi::CreateDummyContext(HDC hdc, HGLRC& hglrc)
{
	if (!SetPixelFormat(hdc))
	{
		return false;
	}
	CreateOpenGLContext(hdc,hglrc);
	if (!MakeCurrent(hdc, hglrc))
	{
		return false;
	}
	return true;
}
bool WindowsOpenGLContextApi::LoadOpenGLFunctions()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
		return false;
	err = wglewInit();
	if (GLEW_OK != err)
		return false;
	
	return true;
}

bool WindowsOpenGLContextApi::Init(HDC hdc)
{
	
	HGLRC dummy_hglrc;
	if (!CreateDummyContext(hdc, dummy_hglrc))
	{
		return false;
	}
	if (!LoadOpenGLFunctions())
	{
		return false;
	}
	if (!DeleteOpenGLContext(dummy_hglrc))
	{
		return false;
	}
	return true;
}

bool WindowsOpenGLContextApi::CreateContext(HDC hdc, int major, int minor, HGLRC& hglrc)
{
	
	
	const int attribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0, // End
	};

	int pixelFormat[256];
	UINT numFormats;
	wglChoosePixelFormatARB(hdc, attribList, NULL, 256, pixelFormat, &numFormats);
	PIXELFORMATDESCRIPTOR pfd = {0};
	DescribePixelFormat(hdc, pixelFormat[0], sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	::SetPixelFormat(hdc, pixelFormat[0], &pfd);
	GLint attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,   
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,   
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		//WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0, // End
	};
	
	hglrc = wglCreateContextAttribsARB(hdc, nullptr, attribs);
	if (hglrc == NULL) 
	{
		return false;
	}
	return true;
}
const char* WindowsOpenGLContextApi::CurrentContextVersion()
{
	const char* p = (const char*)glGetString(GL_VERSION);
	return p;
}
void WindowsOpenGLContextApi::Vsync(bool flag)
{
	wglSwapIntervalEXT(flag);
}
bool WindowsOpenGLContextApi::SwapBuffers(HDC dc)
{
	return ::SwapBuffers(dc);
}
HDC WindowsOpenGLContextApi::GetDeviceContext(HWND wh)
{
	return GetDC(wh);
}
void WindowsOpenGLContextApi::ReleaseDeviceContext(HWND hwnd, HDC dc)
{
	ReleaseDC(hwnd,dc);
}
#endif