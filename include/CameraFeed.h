#ifndef ASTRONOMICAN_CAMERA_FEED_H_
#define ASTRONOMICAN_CAMERA_FEED_H_
#include <QObject>
#include <cv.h>
#include <highgui.h>
class CameraFeed : public QObject {
  Q_OBJECT
public:
  CameraFeed();
signals:
  void HasNewFrame(const cv::Mat& frame);
public slots:
  void StartCapturing();
  void StartCapturing(int device_id);
  void StopCapturing();
private:
  cv::Mat frame_buffer_;
  bool is_capturing_;
  cv::VideoCapture device_;
};

#endif
