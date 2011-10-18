#include "CameraFeed.h"
#include <stdexcept>

CameraFeed::CameraFeed() {
  is_capturing_ = false;
}

void CameraFeed::StartCapturing() {
  if (!device_.isOpened()) {
    if (!device_.open(1)) {
      throw std::runtime_error("Unable to capture from device id 1");
    }
  }

  is_capturing_ = true;
  device_.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  device_.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

  while (is_capturing_) {
    device_ >> frame_buffer_;
    emit HasNewFrame(frame_buffer_);
  }
}

void CameraFeed::StartCapturing(int device_id) {
  if (device_.isOpened()) {
    device_.release();
  }

  if (!device_.open(device_id)) {
    throw std::runtime_error("Unable to capture from device id " + device_id);
  }

  StartCapturing();
}

void CameraFeed::StopCapturing() {
  is_capturing_ = false;
}
