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

public slots:
  void SetSize(int new_width, int new_height);
  void GetReady();
  void HandleNewFrame(const cv::Mat& new_frame);
private:
  CameraFeed* main_camera_;
  SceneManager* scene_;
};

#endif
