#pragma once
#include <QWidget>
#include "../Platform/OpenGLContextApi.h"
#include <QEvent>

class OpenGLWidget :public QWidget
{
	Q_OBJECT
public:
	OpenGLWidget(int major,int minor,QWidget* parent=nullptr);
	virtual ~OpenGLWidget() ;
	virtual void OnRender() {}
	void SwapBuffers();
	
protected:
	virtual bool event(QEvent* event)override;
	virtual QPaintEngine* paintEngine() const override { return nullptr; }
	WindowHandle m_WindowHandle;
	OpenGLContextHandle m_OpenGLContextHandle;
	DeviceContextHandle m_DC;
};