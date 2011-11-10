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
//  settings_ = settings;
  ui.setupUi(this);
  qml_Page_ = new QDeclarativeView;
  qml_Page_->setSource(QUrl("qrc:///ui/Checkerboard.qml"));
  qml_Page_->setResizeMode(QDeclarativeView::SizeRootObjectToView);

  this->game_page_ = new ViewManager();

  QGraphicsObject *background = qml_Page_->rootObject();

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
          this, SIGNAL(Detect()));
  connect(ui.Calibration, SIGNAL(clicked()),
          this, SIGNAL(Calibrate()));
  connect(ui.Toggle, SIGNAL(clicked()),
          this, SLOT(Toggle()));
  connect(ui.DiceRegister, SIGNAL(clicked()),
          this, SIGNAL(DiceRegister()));

  connect(background, SIGNAL(sizeChanged(int,int)),
          this, SIGNAL(sizeChanged(int,int)));
  connect(background, SIGNAL(sizeChanged(int,int)),
          this, SLOT(UiSizeChanged()));

  this->readSettings();
  emit ( sizeChanged( this->width()/150, this->height()/150));

//  setCentralWidget(this->qml_page);
  ui.stackedWidget->addWidget(qml_Page_);
  ui.stackedWidget->addWidget(game_page_);
  ui.stackedWidget->setCurrentWidget(qml_Page_);
}

//void MainWindow::DrawCircle(MovableUnit unit) {
//  QGraphicsObject *background = qml_page->rootObject();
//  QVariant returnedValue;
//  QMetaObject::invokeMethod(background, "createCircle",
//                            Q_RETURN_ARG(QVariant, returnedValue),
//                            Q_ARG(QVariant, unit.location().x()),
//                            Q_ARG(QVariant, unit.location().y()),
//                            Q_ARG(QVariant, unit.radius())
//                            );
//}

MainWindow::~MainWindow()
{
  this->writeSettings();
  delete this->qml_Page_;
  delete this->game_page_;
}

void MainWindow::SetUpSceneView(SceneManager *scene) {
  game_page_->setScene(scene);
}

void MainWindow::UiSizeChanged() {
  QGraphicsObject *background = qml_Page_->rootObject();
  int a(background->property("width").toInt()),
      b(background->property("height").toInt());

  while (b != 0)
  {
    int t = b;
    b = a % b;
    a = t;
  }
  int new_size = (a > 150)? a : 150;

  qDebug() << "Current main window size is" << this->size();
  qDebug() << "Current tile size is" << new_size;
  background->setProperty("tile_size",new_size);
  emit (tileSizeChanged(new_size));
}

//void MainWindow::SetTileSize(int new_size) {
//  QGraphicsObject *background = ui->rootObject();
//  background->setProperty("tile_size",new_size);
//}


//void MainWindow::ShowTheBoard() {
//  QGraphicsObject *background = qml_page->rootObject();
//  QMetaObject::invokeMethod(background, "createCheckerBoard");
//}

//void MainWindow::CleanBackGround() {
//  QGraphicsObject *background = qml_page->rootObject();
//  QMetaObject::invokeMethod(background, "clearDrawObject");
//}

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

//void MainWindow::ClearColorBuffer(QColor color) {

//}

void MainWindow::Toggle() {
  if (ui.stackedWidget->currentIndex() == ui.stackedWidget->indexOf(qml_Page_))
  {
    ui.stackedWidget->setCurrentWidget(game_page_);
  }
  else
  {
    ui.stackedWidget->setCurrentWidget(qml_Page_);
  }
}

void MainWindow::RepaintGamePage(QColor color)
{
  game_page_->repaint();
  emit (ViewColorCleared(color));
}

void MainWindow::readSettings()
{
//  QSettings settings(QSettings::IniFormat, QSettings::UserScope,
//                    "Tri Chu", "Astronomican");
  QSettings settings("Astronomican.ini", QSettings::IniFormat);

 settings.beginGroup("MainWindow");
 resize(settings.value("size", QSize(800, 600)).toSize());
 move(settings.value("pos", QPoint(200, 200)).toPoint());
 settings.endGroup();
}

void MainWindow::writeSettings()
{

//  QSettings settings(QSettings::IniFormat, QSettings::UserScope,
//                     "Tri Chu", "Astronomican");
  QSettings settings("Astronomican.ini", QSettings::IniFormat);

  settings.beginGroup("MainWindow");
  settings.setValue("size", this->size());
  settings.setValue("pos", this->pos());
  settings.endGroup();
}

//void MainWindow::repaintGamePage() {
//  game_page->repaint();
//}

void MainWindow::closeEvent(QCloseEvent *event) {
  writeSettings();
  emit(Quit());
  //  event->accept();
}

void MainWindow::SwitchToGamePage()
{
  if(ui.stackedWidget->currentIndex() != ui.stackedWidget->indexOf(game_page_))
    ui.stackedWidget->setCurrentWidget(game_page_);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  switch( e->key() )
  {
  case Qt::Key_Escape:
    close();
    break;
  case Qt::Key_C:
    emit(Calibrate());
    break;
  case Qt::Key_D:
    emit(Detect());
    break;
  case Qt::Key_R:
    if(this->isMaximized())
      resize(800, 600);
    else
      this->showMaximized();
    break;
  case Qt::Key_T:
    this->Toggle();
    break;
  case Qt::Key_1:
    emit(DiceRegisterSetup());
    break;
  case Qt::Key_2:
    emit(DiceRegisterMain());
    break;
  }
}

QSize MainWindow::GetUISize()
{
  QPixmap screenshot = QPixmap::grabWidget
      (ui.stackedWidget->currentWidget());
  return screenshot.size();
}
