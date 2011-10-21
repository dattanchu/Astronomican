#include "CameraFeed.h"
#include "MainController.h"
#include "SceneManager.h"
#include "math.h";
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

  qDebug() << "calibrating";
  vector<cv::Point2f> corners;
  bool patternfound = false;
  cv::Mat camera_frame = main_camera_->Capture();


  int tile_size = scene_->GetTileSize();
  QSize scene_size = scene_->GetSize();
  cv::Size checkerboard_size(std::floor(scene_size.width()/tile_size),
                             std::floor(scene_size.height()/tile_size));

  patternfound = cv::findChessboardCorners(camera_frame,
                                                checkerboard_size,
                                                corners,
                                                cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

  if(patternfound && corners.size() > 1)
    qDebug() << "calibration passed with" << corners.size() << "founds";
  else
    qDebug() << "calibration failed";
}
