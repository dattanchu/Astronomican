#include <QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QSize>
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QObject>
#include <QSettings>

#include "MainController.h"
#include "CameraFeed.h"
#include "MainWindow.h"
#include "MovableUnit.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
//  qmlRegisterType<MovableUnit>("Unit", 1, 0, "MovableUnit");
  QSettings *settings = new QSettings("Astronomican.ini", QSettings::IniFormat);

  MainController main_controller(settings);
  CameraFeed camera1;
  main_controller.AddCameraFeed(&camera1);

  MainWindow main_window(settings);
  main_controller.SetUpMainWindow(&main_window);

  main_controller.GetReady();
//  view.rootContext()->setContextProperty("camera_feed", &camera1);
//  view.rootContext()->setContextProperty("main_controller", &main_controller);
//  main_window.setGeometry(0, 0, 800, 600);
//  view.showFullScreen()

  main_window.show();
//  main_controller.CalibrateCamera();
  camera1.StartCapturing(1);
  //TODO tchu: signal MainWindow to change into calibrating mode,
  //then use the camera to detect the board


  app.exec();
  delete settings;
  return 0;
}
