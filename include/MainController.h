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
  //return the size of a tile in the checkerboard given the width and height of the
  //screen as parameters
  Q_INVOKABLE int GetRatio(const int &screen_width, const int &screen_height);
public slots:
  void GetReady();
  void HandleNewFrame(const cv::Mat& new_frame);
private:
  CameraFeed* main_camera_;
  SceneManager* scene_;
};

#endif
