#ifndef ASTRONOMICAN_CAMERA_FEED_H_
#define ASTRONOMICAN_CAMERA_FEED_H_
#include <QObject>
#include <cv.h>
#include <highgui.h>
#include <QColor>

class CameraFeed : public QObject {
  Q_OBJECT
public:
  CameraFeed();
signals:
  void HasNewFrame(const cv::Mat& frame);
  void FrameCaptured(const cv::Mat& frame);
  void FrameCaptured(const cv::Mat& frame, QColor color);
public slots:
  void StartCapturing();
  void StartCapturing(int device_id);
  void StopCapturing();
  cv::Mat Capture();
  cv::Mat Capture(QColor color);
//  void StartCalibrating(cv::Size pattern_size);
//  void StopCalibrating();
  void SetHomography(cv::Mat new_homography);
  cv::Mat GetHomography() const;
private:
  cv::Mat frame_buffer_;
  cv::Mat camera_to_scene_homography_;
  bool is_capturing_;
//  bool is_calibrating_;
  cv::VideoCapture device_;

};

#endif
