#ifndef ASTRONOMICAN_CAMERA_FEED_H_
#define ASTRONOMICAN_CAMERA_FEED_H_
#include <QObject>
#include <cv.h>
#include <highgui.h>
#include <QColor>
#include <QTimer>
#include <QSize>

class CameraFeed : public QObject {
  Q_OBJECT
public:
  CameraFeed();
  virtual ~CameraFeed();
  QSize GetSize();

signals:
  void HasNewFrame(const cv::Mat& frame);
  void FrameCaptured(const cv::Mat& frame);
  void FrameCaptured(const cv::Mat& frame, QColor color);
public slots:
  void StartCapturing();
  void StartCapturing(int device_id);
  void StopCapturing();
  void Capture();
  cv::Mat CaptureOneShot();
  cv::Mat CaptureOneShot(QColor color);
//  void StartCalibrating(cv::Size pattern_size);
//  void StopCalibrating();
  void SetHomography(cv::Mat new_homography);
  cv::Mat GetHomography() const;
private:
  cv::Mat frame_buffer_;
  cv::Mat camera_to_scene_homography_;
//  bool is_capturing_;
//  bool is_calibrating_;
  cv::VideoCapture device_;
  QTimer timer_;
  QSize size_;


};

#endif
