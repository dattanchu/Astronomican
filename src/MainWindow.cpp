#include <QGraphicsObject>
#include <QtCore>
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/video/tracking.hpp"

MainWindow::MainWindow() : QMainWindow()
{
  ui.setupUi(this);
  qml_page = new QDeclarativeView;
  qml_page->setSource(QUrl("qrc:///ui/Checkerboard.qml"));
  qml_page->setResizeMode(QDeclarativeView::SizeRootObjectToView);

  this->game_page = new SceneWidget;


  QGraphicsObject *background = qml_page->rootObject();

//  connect(background, SIGNAL(sizeChanged(int, int)),
//          this, SIGNAL(sizeChanged(int, int)));
//  connect(background, SIGNAL(calibrate()),
//          this, SIGNAL(calibrate()));
//  connect(background, SIGNAL(sizeChanged(int,int)),
//          this, SLOT(UiSizeChanged()));
//  connect(background, SIGNAL(resize()),
//          this, SLOT(Resize()));
//  connect(background, SIGNAL(detect()),
//          this, SIGNAL(detect()));
//  connect(background, SIGNAL(screencap()),
//          this, SLOT(TakeScreenshot()));
  connect(ui.Detect, SIGNAL(clicked()),
          this, SIGNAL(detect()));
  connect(ui.Calibration, SIGNAL(clicked()),
          this, SIGNAL(calibrate()));
  connect(ui.Toggle, SIGNAL(clicked()),
          this, SLOT(Toggle()));
  connect(background, SIGNAL(sizeChanged(int,int)),
          this, SIGNAL(sizeChanged(int,int)));
  connect(background, SIGNAL(sizeChanged(int,int)),
          this, SLOT(UiSizeChanged()));

  emit ( sizeChanged( this->width()/170, this->height()/170));

//  setCentralWidget(this->qml_page);
  ui.stackedWidget->addWidget(qml_page);
  ui.stackedWidget->addWidget(game_page);
  ui.stackedWidget->setCurrentWidget(qml_page);
}

void MainWindow::DrawCircle(MovableUnit unit) {
//  QGraphicsObject *background = qml_page->rootObject();
//  QVariant returnedValue;
//  QMetaObject::invokeMethod(background, "createCircle",
//                            Q_RETURN_ARG(QVariant, returnedValue),
//                            Q_ARG(QVariant, unit.location().x()),
//                            Q_ARG(QVariant, unit.location().y()),
//                            Q_ARG(QVariant, unit.radius())
//                            );
}

void MainWindow::Resize() {
  if(!isMaximized())
    showFullScreen();
  else
    showNormal();
}

void MainWindow::UiSizeChanged() {
  QGraphicsObject *background = qml_page->rootObject();
  int a(background->property("width").toInt()),
      b(background->property("height").toInt());

  while (b != 0)
  {
    int t = b;
    b = a % b;
    a = t;
  }
  int new_size = (a > 170)? a : 170;

  qDebug() << "Current tile size is" << new_size;
  background->setProperty("tile_size",new_size);
  emit (tileSizeChanged(new_size));
}

//void MainWindow::SetTileSize(int new_size) {
//  QGraphicsObject *background = ui->rootObject();
//  background->setProperty("tile_size",new_size);
//}

MainWindow::~MainWindow()
{
  delete this->qml_page;
}

void MainWindow::ShowTheBoard() {
  QGraphicsObject *background = qml_page->rootObject();
  QMetaObject::invokeMethod(background, "createCheckerBoard");
}

void MainWindow::CleanBackGround() {
  QGraphicsObject *background = qml_page->rootObject();
  QMetaObject::invokeMethod(background, "clearDrawObject");
}

//cv::Size MainWindow::getCheckerBoardSize() {
//  QGraphicsObject *background = ui->rootObject();
//  int background_height(background->property("height").toInt());
//  int background_width(background->property("width").toInt());
//  int tile_size(background->property("tile_size").toInt());
//  return cv::Size(background_width/tile_size,background_height/tile_size);
//}

cv::Mat MainWindow::TakeScreenshot() {
//  qDebug() << "coping screen buffer";
  QPixmap screenshot = QPixmap::grabWidget(ui.stackedWidget->currentWidget());
  QImage screen_image = screenshot.toImage();
  screen_image.convertToFormat(QImage::Format_ARGB32);
//  screen_image.save("preformated_screen","png");
  cv::Mat screenshot_ = cv::Mat(
        screenshot.height(),
        screenshot.width(),
        CV_8UC4,
        screen_image.bits()).clone();
//  cv::imwrite("test.png",*screen_matrix);
//  emit(NewScreenShot(screen_matrix));
  return screenshot_;

}

void MainWindow::ClearColorBuffer(QColor color) {

}

void MainWindow::Toggle() {
  if (ui.stackedWidget->currentIndex() == ui.stackedWidget->indexOf(qml_page))
  {
    ui.stackedWidget->setCurrentWidget(game_page);
  }
  else
  {
    ui.stackedWidget->setCurrentWidget(qml_page);
  }
}
