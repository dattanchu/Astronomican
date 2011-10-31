#include <QGraphicsObject>
#include <QtCore>
#include "MainWindow.h"

MainWindow::MainWindow() : QMainWindow()
{

  this->ui = new QDeclarativeView;
  this->ui->setSource(QUrl("qrc:///ui/MainWindow.qml"));
  this->ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);


  QGraphicsObject *background = ui->rootObject();

  connect(background, SIGNAL(sizeChanged(int, int)),
          this, SIGNAL(sizeChanged(int, int)));
  connect(background, SIGNAL(calibrate()),
          this, SIGNAL(calibrate()));
  connect(background, SIGNAL(sizeChanged(int,int)),
          this, SLOT(UiSizeChanged()));
  connect(background, SIGNAL(resize()),
          this, SLOT(Resize()));
  connect(background, SIGNAL(detect()),
          this, SIGNAL(detect()));
  connect(background, SIGNAL(screencap()),
          this, SLOT(TakeScreenshot()));

  emit(sizeChanged(
         background->property("width").toInt(),
         background->property("height").toInt()
         ));

  setCentralWidget(this->ui);
}

void MainWindow::DrawCircle(MovableUnit unit) {
  QGraphicsObject *background = ui->rootObject();
  QVariant returnedValue;
  QMetaObject::invokeMethod(background, "createCircle",
                            Q_RETURN_ARG(QVariant, returnedValue),
                            Q_ARG(QVariant, unit.location().x()),
                            Q_ARG(QVariant, unit.location().y()),
                            Q_ARG(QVariant, unit.radius())
                            );
}

void MainWindow::Resize() {
  if(!isMaximized())
    showFullScreen();
  else
    showNormal();
}

void MainWindow::UiSizeChanged() {
  QGraphicsObject *background = ui->rootObject();
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
  delete this->ui;
}

void MainWindow::ShowTheBoard() {
  QGraphicsObject *background = ui->rootObject();
  QMetaObject::invokeMethod(background, "createCheckerBoard");
}

void MainWindow::CleanBackGround() {
  QGraphicsObject *background = ui->rootObject();
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
  qDebug() << "coping screen buffer";
  QPixmap screenshot = QPixmap::grabWidget(ui);
  QImage screen_image = screenshot.toImage();
  screen_image.convertToFormat(QImage::Format_ARGB32);
//  screen_image.save("preformated_screen","png");
  cv::Mat screen_matrix(
        screenshot.height(),
        screenshot.width(),
        CV_8UC4,
        screen_image.bits());
  emit(NewScreenShot(screen_matrix));
}

void MainWindow::ClearColorBuffer(QColor color) {
  QGraphicsObject *background = ui->rootObject();
  QMetaObject::invokeMethod(background, "clearDrawObject");
  QMetaObject::invokeMethod(background, "deleteCheckerBoard");
  QMetaObject::invokeMethod(background, "clearColorBuffer",
                            Q_ARG(QVariant, color));
}
