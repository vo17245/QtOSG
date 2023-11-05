#include <QApplication>
#include <QWidget.h>
#include "Platform/OpenGLContextApi.h"
#include <assert.h>
#include <iostream>
#include "Widget/OpenGLWidget.h"
#include "GL/glew.h"
#include "Widget/OsgViewerWidget.h"
#include "Sandbox.h"
int main(int argc,char** argv)
{
	QApplication app(argc,argv);
	//init opengl extension api
	QWidget dummyWindow;
	bool ret=OpenGLContextApi::Init((WindowHandle)dummyWindow.winId());
	assert(ret);
	Sandbox widget;
	//OpenGLWidget widget(4,6);
	widget.show();
	std::cout << OpenGLContextApi::CurrentContextVersion() << std::endl;
	return app.exec();
}