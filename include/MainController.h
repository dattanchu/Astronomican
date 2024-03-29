#ifndef ASTRONOMICAN_MAIN_CONTROLLER_H_
#define ASTRONOMICAN_MAIN_CONTROLLER_H_

#include <QObject>
#include <cv.h>
#include <QSize>
#include <QPair>
#include <QPixmap>
#include <QString>
#include <QSettings>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QList>

#include <MainWindow.h>
#include <DiceSet.h>

class CameraFeed;
class SceneManager;
/**
  \class MainController
  */
class MainController: public QObject {
  Q_OBJECT

public:
  MainController(QSettings *settings);
  ~MainController();
  void AddCameraFeed(CameraFeed* camera_feed);
  void SetUpMainWindow(MainWindow *window);
//  void readSettings();
//  void writeSettings();

  void ProjectToVirtualScene(const cv::Mat& input, cv::Mat& output);
signals:
  void Quit();

public slots:
  void TileSizeChanged(int new_tile_size);
  void CalibrateCamera();
  void DetectNewObject();
  void DiceRegisterSetup();
  void DiceRegisterMain();
  void SetSize(int new_width, int new_height);
  void GetReady();
  void HandleNewFrame(const cv::Mat& new_frame);
  void HandleNewScreenshot(cv::Mat* new_screenshot);
  void CalGamePoint(int number_of_dices);
//  void GetScreenAreaPicture(QColor color);
  void Exit();

private:
  QSettings* settings_;
  QList<QGraphicsItem*> diceSpots_;
//  cv::Mat BackgroundSubstraction();
  CameraFeed* main_camera_;
  SceneManager* scene_;
  MainWindow* main_window_;
  QPixmap screenshot;
  std::vector<DiceSet*> registered_dice_sets_;
  bool FLIP_CAMERA_VIEW;
};

#endif
