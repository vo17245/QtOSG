#include "Sandbox.h"
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>

class FindGeometriesVisitor : public osg::NodeVisitor
{
public:
    FindGeometriesVisitor()
        : osg::NodeVisitor(TraversalMode::TRAVERSE_ALL_CHILDREN)
    {}

    virtual void apply(osg::Geode& geode)
    {
        for (size_t i = 0; i < geode.getNumDrawables(); ++i)
        {
            osg::Geometry* geom = geode.getDrawable(i)->asGeometry();
            if (geom)
                geometries.push_back(geom);
        }

        traverse(geode);
    }

    std::vector<osg::ref_ptr<osg::Geometry>> geometries;
};
void configureShaders(osg::StateSet* stateSet)
{
    const std::string vertexSource =
        "#version 460\n"
        "\n"
        "layout (location = 0) in vec3 a_Pos;\n"
        "layout (location = 0) in vec3 a_Norm;\n"
        "uniform mat3 osg_NormalMatrix;\n"
        "uniform mat4 osg_ViewMatrix;\n"
        "uniform mat4 osg_ProjectionMatrix;\n"
        "uniform mat4 osg_ModelViewProjectionMatrix;\n"
        "out vec3 v_Norm;\n"
        "out vec3 v_FragPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = osg_ModelViewProjectionMatrix*vec4(a_Pos,1);\n"
        //"   v_Norm=osg_NormalMatrix*a_Norm;\n"
        "   v_Norm=a_Norm;\n"
        "   v_FragPos=a_Pos;"  
        //"    v_Normal=a_Normal;"
        "} \n";
    osg::Shader* vShader = new osg::Shader(osg::Shader::VERTEX, vertexSource);
    const std::string fragmentSource =
        "#version 460 \n"
        "out vec4 color;\n"
        "in vec3 v_Norm;\n"
        "in vec3 v_FragPos;\n"
        "void main() \n"
        "{ \n"
        "   vec3 lightDir=vec3(0,0,-1);\n"
        "   vec3 objColor=vec3(1,1,1);\n"
        "   vec3 lightColor=vec3(1,1,1);\n"  
        "   float diff = max(dot(normalize(v_Norm),normalize(-lightDir) ), 0.0)*0.8;\n"
        "   vec3 viewDir = normalize(v_FragPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, normalize(v_Norm));\n"
        "   float spec = max(dot(-viewDir, reflectDir), 0.0)*0.1;"
        "   color = vec4((diff+spec+0.2)*lightColor*objColor,1); \n"
        "} \n";
    osg::Shader* fShader = new osg::Shader(osg::Shader::FRAGMENT, fragmentSource);
    osg::Program* program = new osg::Program;
    program->addShader(vShader);
    program->addShader(fShader);
    stateSet->setAttribute(program);
}


Sandbox::Sandbox()
{
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF 
        | osg::StateAttribute::OVERRIDE);
    root->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON
        | osg::StateAttribute::OVERRIDE);
    configureShaders(root->getStateSet());
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("../res/cow.osg");
    FindGeometriesVisitor findGeometries;
    node->accept(findGeometries);

    for (osg::Geometry* geom : findGeometries.geometries)
    {
        geom->setVertexAttribArray(0, geom->getVertexArray());
        geom->setVertexAttribArray(1, geom->getNormalArray());
    }
    root->addChild(node);
    m_Viewer->setSceneData(root.get());
    
}
