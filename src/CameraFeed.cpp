#include "CameraFeed.h"
#include <stdexcept>
#include <QtCore>
#include <QApplication>

CameraFeed::CameraFeed() {
//  is_capturing_ = false;
  timer_.setInterval(100);
  connect(&timer_, SIGNAL(timeout()),
          this, SLOT(Capture()));
}

void CameraFeed::StartCapturing() {
//  if (!device_.isOpened()) {
//    if (!device_.open(1)) {
//      throw std::runtime_error("Unable to capture from device id 1");
//    }
//  }

//  is_capturing_ = true;
  timer_.start();


//  while (is_capturing_) {
//    QApplication::processEvents();
//    device_ >> frame_buffer_;
//    emit HasNewFrame(frame_buffer_);
//  }
}

void CameraFeed::StartCapturing(int device_id) {
//  if (device_.isOpened()) {
//    device_.release();
//  }

//  if (!device_.open(device_id)) {
//    throw std::runtime_error("Unable to capture from device id " + device_id);
//  }

  StartCapturing();
}

void CameraFeed::StopCapturing() {
//  is_capturing_ = false;
  timer_.stop();
}

cv::Mat CameraFeed::CaptureOneShot() {
  if (!device_.isOpened()) {
    if (!device_.open(1)) {
      throw std::runtime_error("Unable to capture from device id 1");
    }
  }
  device_.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  device_.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

  device_ >> frame_buffer_;
  emit (FrameCaptured(frame_buffer_));
  return frame_buffer_.clone();
}

cv::Mat CameraFeed::CaptureOneShot( QColor color ) {
  if (!device_.isOpened()) {
    if (!device_.open(1)) {
      throw std::runtime_error("Unable to capture from device id 1");
    }
  }
  device_.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  device_.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

  device_ >> frame_buffer_;
  emit (FrameCaptured(frame_buffer_, color));
  return frame_buffer_.clone();
}

void CameraFeed::SetHomography(cv::Mat new_homography) {
  camera_to_scene_homography_ = new_homography.clone();
}

cv::Mat CameraFeed::GetHomography() const{
  return camera_to_scene_homography_;
}

void CameraFeed::Capture()
{
  if (!device_.isOpened()) {
    if (!device_.open(1)) {
      throw std::runtime_error("Unable to capture from device id 1");
    }
  }
  device_.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  device_.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

  QApplication::processEvents();
  device_ >> frame_buffer_;
  emit (HasNewFrame(frame_buffer_));
}

//void CameraFeed::StopCalibrating() {
//  is_calibrating_ = false;
//}
//void CameraFeed::Calibrating(cv::Size pattern_size) {

//}

//void CameraFeed::StartCalibrating() {
//  is_calibrating_ = true;
//  while(is_calibrating_) {
//    vector<cv::Point2f> corners;
//    bool patternfound = cv::findChessboardCorners(frame_buffer_, pattern_size, corners,
//                                                  cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

//    cv::TermCriteria criteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1);
//    if(patternfound)
//      cv::cornerSubPix(frame_buffer_, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);

//    cv::drawChessboardCorners(frame_buffer_, pattern_size, cv::Mat(corners), patternfound);
//  }
//}


