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

void MainController::SetSize(int new_width, int new_height) {
  scene_->SetSize(QSize(new_width,new_height));

  int a(new_width), b(new_height);
  while (b != 0)
  {
    int t = b;
    b = a % b;
    a = t;
  }
  int new_tile_size = (a > 100)? a : 100;
  scene_->SetTileSize(new_tile_size);
  emit TileSizeChanged(new_tile_size);
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

void MainController::CalibrateCamera() {
  cv::Mat camera_frame = main_camera_->Capture();
}
