#include "CameraFeed.h"
#include "MainController.h"
#include "SceneManager.h"

#include <QtCore>
MainController::MainController() {
  main_camera_ = NULL;
  scene_ = new SceneManager();
}

MainController::~MainController() {
  delete scene_;
}

void MainController::AddCameraFeed(CameraFeed *camera_feed) {
  main_camera_ = camera_feed;
}

void MainController::SetWidth(int new_width) {
  scene_->GetSize().setWidth(new_width);
//  qDebug() << "Current scene size is" << scene_->GetSize();
}

void MainController::SetHeight(int new_height) {
  scene_->GetSize().setHeight(new_height);
//  qDebug() << "Current scene size is" << scene_->GetSize();
}

int MainController::GetRatio(const int &screen_width, const int &screen_height) {
  int gcd = screen_width;

  if (screen_width == 0)
    gcd = screen_height;
  int a(screen_width),b(screen_height);
  while (b != 0)
  {
    int t = b;
    b = a % b;
    a = t;
  }
  gcd = (a > 100)? a : 100;
  qDebug() << "Current tile size is" << gcd;

  return gcd;
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
