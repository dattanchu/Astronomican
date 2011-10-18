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

QPair<int,int> MainController::GetRatio(int a, int b) {
  int gcd = a;
  if (a = 0)
    gcd = b;
  while (b != 0)
  {
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  gcd = a;
  return QPair((int)a/gcd,(int)b/gcd);
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
