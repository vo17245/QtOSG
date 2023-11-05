#pragma once
#include "OpenGLWidget.h"
#include <osgViewer/Viewer>
#include <QInputEvent>
class OsgWidget :public OpenGLWidget
{
	Q_OBJECT
public:
    OsgWidget();
    ~OsgWidget();
    virtual void OnUpdate(float ds) {};
protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void moveEvent(QMoveEvent* event);
    virtual void timerEvent(QTimerEvent* event);
protected:
    osg::ref_ptr<osgViewer::GraphicsWindow> m_Window;
private:
    size_t m_Timestamp;
    void UpdateTimestamp();
};