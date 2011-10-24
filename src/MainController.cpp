#include "CameraFeed.h"
#include "MainController.h"
#include "SceneManager.h"
#include "math.h";
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <QtCore>
#include <vector>

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

//  int a(new_width), b(new_height);
//  while (b != 0)
//  {
//    int t = b;
//    b = a % b;
//    a = t;
//  }
//  int new_tile_size = (a > 100)? a : 100;
//  scene_->SetTileSize(new_tile_size);
//  emit TileSizeChanged(new_tile_size);
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

  cv::Mat view = main_camera_->Capture(), viewgray;
  cv::imwrite("view.png",view);


  int tile_size = scene_->GetTileSize();
  QSize scene_size = scene_->GetSize();

  //board size is 2 tile smaller than the total (screen_size)/(tile_size)
  //because of the margins
  cv::Size board_size(std::floor(scene_size.width()/tile_size-2),
                             std::floor(scene_size.height()/tile_size)-2);

  cv::cvtColor(view,viewgray,CV_BGR2GRAY);
  cv::imwrite("viewgray.png",viewgray);

  bool found = cv::findChessboardCorners(view, board_size, corners,
                                                CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

  if(found)
    qDebug() << "calibration passed with" << corners.size() << "corners founded";
  else
    qDebug() << "calibration failed";
}

void MainController::TileSizeChanged(int new_tile_size) {
  scene_->SetTileSize(new_tile_size);
}
