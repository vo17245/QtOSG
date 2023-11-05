cmake_minimum_required(VERSION 3.9)
project(QtOSG)
set(CMAKE_PREFIX_PATH $ENV{QT_5_14_2_X8664})
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
file(GLOB_RECURSE SOURCE_FILE "src/*.cpp" "src/*.h" "src/*.ui" "src/*.qrc")
include("CMake/vs_config.cmake")
include_directories(
    "dependencies/OpenSceneGraph-3.6.5-VC2022-64-Debug-2023-01/include"
    "dependencies/glew-2.1.0-windows/include"
    "vendor"
)

find_package(Qt5 COMPONENTS Core Gui Qml Quick Widgets REQUIRED)

add_definitions(-DDEBUG)
add_definitions(-DGLEW_STATIC)

link_directories(
    "dependencies/OpenSceneGraph-3.6.5-VC2022-64-Debug-2023-01/lib"
    "dependencies/glew-2.1.0-windows/lib/Release/x64"
)
add_executable (${PROJECT_NAME}  ${SOURCE_FILE})
target_link_libraries(${PROJECT_NAME}  
    "glew32s"
    "OpenGL32"
    Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::Widgets
    "osgd"
    "osgViewerd"
    "osgDBd"
    "osgAnimationd"
    "OpenThreadsd"
    "osgAnimationd"
    "osgd"
    "osgDBd"
    "osgFXd"
    "osgGAd"
    "osgManipulatord"
    "osgParticled"
    "osgPresentationd"
    "osgShadowd"
    "osgSimd"
    "osgTerraind"
    "osgTextd"
    "osgUId"
    "osgUtild"
    "osgViewerd"
    "osgVolumed"
    "osgWidgetd"

)

