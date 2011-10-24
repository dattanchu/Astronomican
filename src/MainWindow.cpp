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
  connect(background, SIGNAL(draw()),
          this, SLOT(Draw()));
  connect(background, SIGNAL(calibrate()),
          this, SIGNAL(calibrate()));
  connect(background, SIGNAL(sizeChanged(int,int)),
          this, SLOT(uiSizeChanged()));


  emit(sizeChanged(
         background->property("width").toInt(),
         background->property("height").toInt()
         ));

  setCentralWidget(this->ui);
}

void MainWindow::Draw() {
  this->ui->repaint();
}

void MainWindow::uiSizeChanged() {
  QGraphicsObject *background = ui->rootObject();
  int a(background->property("width").toInt()),
      b(background->property("height").toInt());

  while (b != 0)
  {
    int t = b;
    b = a % b;
    a = t;
  }
  int new_size = (a > 200)? a : 200;

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
  background->setProperty("showing_board",true);
}

void MainWindow::CleanBackGround() {
  QGraphicsObject *background = ui->rootObject();
}

//cv::Size MainWindow::getCheckerBoardSize() {
//  QGraphicsObject *background = ui->rootObject();
//  int background_height(background->property("height").toInt());
//  int background_width(background->property("width").toInt());
//  int tile_size(background->property("tile_size").toInt());
//  return cv::Size(background_width/tile_size,background_height/tile_size);
//}

