cmake_minimum_required(VERSION 2.6)
project(Astronomican)
find_package(OpenCV REQUIRED)
find_package(Qt4 REQUIRED)
set(QT_USE_QTOPENGL 1)
set(QT_USE_QTSVG 1)
include(${QT_USE_FILE})
file(GLOB HDRS include/*.h)
file(GLOB SRCS src/*.cpp)
file(GLOB TEST_SRCS test/*.cpp)
qt4_wrap_cpp(MOCSRC ${HDRS})
include_directories(
    ${OpenCV_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
add_executable(Astronomican ${SRCS} ${HDRS} ${MOCSRC} src/Astronomican_main.cxx)
target_link_libraries(Astronomican ${QT_LIBRARIES} ${OpenCV_LIBS})
