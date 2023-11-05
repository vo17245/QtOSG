#pragma once
#include "Widget/OsgViewerWidget.h"

class Sandbox :public OsgViewerWidget
{
public:
	Sandbox();
	~Sandbox(){}
private:
	osg::ref_ptr<osg::Geode> geode;
};