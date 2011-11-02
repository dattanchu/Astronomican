cmake_minimum_required(VERSION 2.6)
project(Astronomican)
find_package(OpenCV REQUIRED)
find_package(Qt4 REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
set(QT_USE_QTOPENGL 1)
set(QT_USE_QTSVG 1)
set(QT_USE_QTDECLARATIVE 1)
include(${QT_USE_FILE})
file(GLOB HDRS include/*.h)
file(GLOB SRCS src/*.cpp)
file(GLOB TEST_SRCS test/*.cpp)
file(GLOB UI_SRCS ui/*)
file(GLOB UI_FILE ui/*.ui)
qt4_wrap_ui(MOCUI ${UI_FILE})
qt4_wrap_cpp(MOCSRC ${HDRS})
qt4_add_resources(QRC Astronomican.qrc)
include_directories(
    ${OpenCV_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
)
add_executable(Astronomican ${SRCS} ${HDRS} ${MOCSRC} ${UI_SRCS} ${QRC} ${MOCUI}
 src/Astronomican_main.cxx)
target_link_libraries(Astronomican ${QT_LIBRARIES} ${OpenCV_LIBS})
