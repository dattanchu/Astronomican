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

//TODO: automate the flip camera flag and add the calibration function to
//the application pipeline instead of activating it manually
void MainController::CalibrateCamera() {

    //reserved flag to automatically flip the camera view so the corner are
    //found correctly

    FLIP_CAMERA_VIEW = true;

    qDebug() << "calibrating";
    vector<cv::Point2f> corners;

    cv::Mat view = main_camera_->Capture(), viewgray;

    if(FLIP_CAMERA_VIEW)
        cv::flip(view, view, -1);
    cv::imwrite("view.png",view);


    int tile_size = scene_->GetTileSize();
    QSize scene_size = scene_->GetSize();

    //board size is 2 tile smaller than the total (screen_size)/(tile_size)
    //instead of 1 because of the margins
    cv::Size board_size(std::floor(scene_size.width()/tile_size-2),
                        std::floor(scene_size.height()/tile_size)-2);

    cv::cvtColor(view,viewgray,CV_BGR2GRAY);
    cv::imwrite("viewgray.png", viewgray);

    bool found = cv::findChessboardCorners(view, board_size, corners,
                                           CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

    if(found)
    {
        cv::cornerSubPix(viewgray, corners, cv::Size(11, 11),
                         cv::Size(-1,-1), cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
        cv::drawChessboardCorners( view, board_size, corners, found);
        cv::imwrite("calibration_result.png", view);
        qDebug() << "finished calibration";
    }
    else
    {
        qDebug() << "calibration failed";
    }
}

void MainController::TileSizeChanged(int new_tile_size) {
  scene_->SetTileSize(new_tile_size);
  int offset = new_tile_size + new_tile_size/2;
  std::vector<cv::Point2f> checkerboard_inner_corners;
  QSize scene_size = scene_->GetSize();

  for(int i = 0; i < std::floor(scene_size.width()/new_tile_size)-2; i++)

  {
      for(int j = 0; j < std::floor(scene_size.height()/new_tile_size-2); j++)
      {
          checkerboard_inner_corners.push_back(cv::Point2f(
                                                    (float)(offset + i*new_tile_size),
                                                    (float)(offset + j*new_tile_size)
                                                   ));
      }
  }
  scene_->SetWindowViewLandmarks(checkerboard_inner_corners);
}
