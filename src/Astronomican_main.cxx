#include <QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QSize>
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QObject>


#include "MainController.h"
#include "CameraFeed.h"
#include "MainWindow.h"
#include "MovableUnit.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  qmlRegisterType<MovableUnit>("Unit", 1, 0, "MovableUnit");


  MainController main_controller;
  CameraFeed camera1;
  main_controller.AddCameraFeed(&camera1);
  main_controller.GetReady();


  MainWindow main_window;
//  view.rootContext()->setContextProperty("camera_feed", &camera1);
//  view.rootContext()->setContextProperty("main_controller", &main_controller);
  main_window.setGeometry(0, 0, 800, 600);
//  view.showFullScreen()

  QObject::connect(&main_window, SIGNAL(sizeChanged(int, int)),
                   &main_controller, SLOT(SetSize(int, int)));
  QObject::connect(&main_window, SIGNAL(tileSizeChanged(int)),
                   &main_controller, SLOT(TileSizeChanged(int)));
  QObject::connect(&main_window, SIGNAL(calibrate()),
                   &main_controller, SLOT(CalibrateCamera()));
  QObject::connect(&main_window, SIGNAL(detect()),
                   &main_controller, SLOT(DetectNewObject()));
  QObject::connect(&main_window, SIGNAL(NewScreenShot(cv::Mat)),
                   &main_controller, SLOT(HandleNewScreenshot(cv::Mat)));

  main_window.show();
//  main_controller.CalibrateCamera();
  camera1.StartCapturing(1);
  //TODO tchu: signal MainWindow to change into calibrating mode,
  //then use the camera to detect the board


  app.exec();
}
