#include "OSGWidget.h"

OsgWidget::OsgWidget()
    :OpenGLWidget(4,6)
{
    m_Window = new osgViewer::GraphicsWindowEmbedded(0, 0, width(), height());
    
}

OsgWidget::~OsgWidget()
{
}
void OsgWidget::keyPressEvent(QKeyEvent* event)
{
    m_Window->getEventQueue()->keyPress(event->key());
    
    
}

void OsgWidget::keyReleaseEvent(QKeyEvent* event)
{
    m_Window->getEventQueue()->keyRelease(event->key());
}

void OsgWidget::mousePressEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button()) {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    
    m_Window->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
    
}

void OsgWidget::mouseReleaseEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button()) 
    {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    m_Window->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
}

void OsgWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button()) {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    m_Window->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);
}

void OsgWidget::mouseMoveEvent(QMouseEvent* event)
{
    m_Window->getEventQueue()->mouseMotion(event->x(), event->y());
}

void OsgWidget::wheelEvent(QWheelEvent* event)
{
    osgGA::GUIEventAdapter::ScrollingMotion motion = event->angleDelta().y() > 0 ?
        osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
    m_Window->getEventQueue()->mouseScroll(motion);
}

void OsgWidget::resizeEvent(QResizeEvent* event)
{
    const QSize& size = event->size();
    m_Window->resized(x(), y(), size.width(), size.height());
    m_Window->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
    m_Window->requestRedraw();
}

void OsgWidget::moveEvent(QMoveEvent* event)
{
    const QPoint& pos = event->pos();
    m_Window->resized(pos.x(), pos.y(), width(), height());
    m_Window->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());
}

void OsgWidget::timerEvent(QTimerEvent* event)
{
    size_t old = m_Timestamp;
    UpdateTimestamp();
    float ds = float(m_Timestamp - old) / 1000000000;//nanoSec to sec 10^9
    OnUpdate(ds);
}

void OsgWidget::UpdateTimestamp()
{
    auto t = std::chrono::high_resolution_clock::now();
    m_Timestamp = std::chrono::time_point_cast<std::chrono::nanoseconds>(t).time_since_epoch().count();
}
