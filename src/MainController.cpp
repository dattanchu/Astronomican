#include "CameraFeed.h"
#include "MainController.h"

#include <QtCore>
MainController::MainController() {
  main_camera_ = NULL;
}

void MainController::AddCameraFeed(CameraFeed *camera_feed) {
  main_camera_ = camera_feed;
}

// Does the connection of slots and signals
void MainController::GetReady() {
  connect(main_camera_, SIGNAL(HasNewFrame(cv::Mat)),
          this, SLOT(HandleNewFrame(cv::Mat)));
}

void MainController::HandleNewFrame(const cv::Mat& new_frame) {
  cv::imshow("Current frame", new_frame);
  cv::waitKey(1);
}
