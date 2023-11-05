#pragma once
#include "OsgWidget.h"
#include <iostream>
class OsgViewerWidget :public OsgWidget
{
public:
	OsgViewerWidget();
	~OsgViewerWidget();
	void OnRender()override;
protected:
	void InitViewer();
	void InitCamera();
	osg::ref_ptr<osgViewer::Viewer> m_Viewer;
};