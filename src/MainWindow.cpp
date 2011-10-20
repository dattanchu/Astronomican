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
  connect(background, SIGNAL(sizeChanged(int, int)),
          this, SLOT(uiSizeChanged()));

  setCentralWidget(this->ui);
}

void MainWindow::uiSizeChanged() {
  QGraphicsObject *background = ui->rootObject();
  int a(background->property("width").toInt()), b(background->property("height").toInt());
  while (b != 0)
  {
    int t = b;
    b = a % b;
    a = t;
  }
  int gcd = (a > 100)? a : 100;

  qDebug() << "Current tile size is" << gcd;
  background->setProperty("tile_size",gcd);
}

MainWindow::~MainWindow()
{
  delete this->ui;
}


