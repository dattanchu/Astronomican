#include <QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include "MainController.h"
#include "CameraFeed.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  MainController main_controller;
  CameraFeed camera1;
  main_controller.AddCameraFeed(&camera1);
  main_controller.GetReady();

  QDeclarativeView view;
  view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
  view.rootContext()->setContextProperty("camera_feed", &camera1);
  view.setSource(QUrl("qrc:///ui/MainWindow.qml"));
  view.setGeometry(0, 0, 800, 600);
  view.show();

  camera1.StartCapturing(1);

  app.exec();
}
