#ifndef ASTRONOMICAN_MAIN_CONTROLLER_H_
#define ASTRONOMICAN_MAIN_CONTROLLER_H_

#include <QObject>
#include <cv.h>
#include <QSize>
#include <QPair>

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
  Q_INVOKABLE void SetWidth(int new_width);
  Q_INVOKABLE void SetHeight(int new_height);
  Q_INVOKABLE QPair<int,int> GetRatio(int a, int b);
public slots:
  void GetReady();
  void HandleNewFrame(const cv::Mat& new_frame);
private:
  CameraFeed* main_camera_;
  SceneManager* scene_;
};

#endif
