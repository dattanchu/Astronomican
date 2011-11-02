#ifndef ASTRONOMICAN_MAIN_CONTROLLER_H_
#define ASTRONOMICAN_MAIN_CONTROLLER_H_

#include <QObject>
#include <cv.h>
#include <QSize>
#include <QPair>
#include <QPixmap>

#include <MainWindow.h>
class CameraFeed;
class SceneManager;
/**
  \class MainController
  */
class MainController: public QObject {
  Q_OBJECT
public:
  MainController();
  ~MainController();
  void AddCameraFeed(CameraFeed* camera_feed);
  void SetUpMainWindow(MainWindow *window);

signals:

public slots:
  void TileSizeChanged(int new_tile_size);
  void CalibrateCamera();
  void DetectNewObject();
  void SetSize(int new_width, int new_height);
  void GetReady();
  void HandleNewFrame(const cv::Mat& new_frame);
  void HandleNewScreenshot(cv::Mat* new_screenshot);

private:
  cv::Mat BackgroundSubstraction();
  CameraFeed* main_camera_;
  SceneManager* scene_;
  MainWindow* main_window_;
  QPixmap screenshot;
  bool FLIP_CAMERA_VIEW;
};

#endif
