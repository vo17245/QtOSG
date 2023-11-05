#include "OsgViewerWidget.h"
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
OsgViewerWidget::OsgViewerWidget()
{
    InitViewer();
    InitCamera();
}

OsgViewerWidget::~OsgViewerWidget()
{
}

void OsgViewerWidget::OnRender()
{
    m_Viewer->frame();
    SwapBuffers();
    
}

void OsgViewerWidget::InitViewer()
{
    m_Viewer = new osgViewer::Viewer;
    m_Viewer->setCameraManipulator(new osgGA::TrackballManipulator);
    m_Viewer->addEventHandler(new osgViewer::StatsHandler);
    m_Viewer->addEventHandler(new osgViewer::ThreadingHandler);
    m_Viewer->addEventHandler(new osgViewer::HelpHandler);
    m_Viewer->addEventHandler(new osgGA::StateSetManipulator(m_Viewer->getCamera()->getOrCreateStateSet()));
    m_Viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
}

void OsgViewerWidget::InitCamera()
{
    m_Viewer->getCamera()->setGraphicsContext(m_Window);
    m_Viewer->getCamera()->setViewport(0, 0, width(), height());
    m_Viewer->getCamera()->setClearColor(osg::Vec4(0.4, 0.5, 0.6, 0.1));
    m_Viewer->getCamera()->getGraphicsContext()->getState()->setUseModelViewAndProjectionUniforms(true);
    
    m_Viewer->getCamera()->getGraphicsContext()->getState()->setUseVertexAttributeAliasing(true);
    
}
