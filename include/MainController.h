#ifndef ASTRONOMICAN_MAIN_CONTROLLER_H_
#define ASTRONOMICAN_MAIN_CONTROLLER_H_

#include <QObject>
#include <cv.h>

class CameraFeed;

class MainController: public QObject {
  Q_OBJECT
public:
  MainController();
  void AddCameraFeed(CameraFeed* camera_feed);
public slots:
  void GetReady();
  void HandleNewFrame(const cv::Mat& new_frame);
private:
  CameraFeed* main_camera_;
};

#endif
