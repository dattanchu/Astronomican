#include "CameraFeed.h"
#include "MainController.h"
#include "SceneManager.h"
#include "math.h";
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <iostream>
#include <QtCore>
#include <vector>

using namespace std;

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
  //Step 1: detect the landmark and tell the camera if it is rotated or not
  FLIP_CAMERA_VIEW = true;

  qDebug() << "calibrating";
  vector<cv::Point2f> camera_points;

  cv::Mat view = main_camera_->Capture(), viewgray;

  if(FLIP_CAMERA_VIEW)
    cv::flip(view, view, -1);
  cv::imwrite("view.png",view);

  //Step 2: detect the checkerboard and return the land marks coordinate in
  //camera plane
  int tile_size = scene_->GetTileSize();
  QSize scene_size = scene_->GetSize();

  //board size is 2 tile smaller than the total (screen_size)/(tile_size)
  //instead of 1 because of the margins
  cv::Size board_size(floor(scene_size.width()/tile_size-2),
                      floor(scene_size.height()/tile_size)-2);

  cv::cvtColor(view,viewgray,CV_BGR2GRAY);
  cv::imwrite("viewgray.png", viewgray);

  bool found = cv::findChessboardCorners(view, board_size, camera_points,
                                         CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

  if(found)
  {
    cv::cornerSubPix(viewgray, camera_points, cv::Size(11, 11),
                     cv::Size(-1,-1), cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
    cv::drawChessboardCorners( view, board_size, camera_points, found);
    cv::imwrite("calibration_result.png", view);
    scene_->SetCameraViewLandmarks(camera_points);
    qDebug() << "finished calibration";
  }
  else
  {
    qDebug() << "calibration failed";
  }

  //Step 3: using the camera landmarks coordinate and our scene coordinates
  //find the homography matrix between camera plane and display plane
  if(found)
  {
    vector<cv::Point2f> display_points = scene_->GetWindowViewLandmarks();
    cv::Mat H = cv::findHomography(
          cv::Mat(camera_points),
          cv::Mat(display_points),
          CV_RANSAC,
          3.0);
    scene_->SetCameraToDisplayHomo(H);
  }
}

void MainController::TileSizeChanged(int new_tile_size) {
  scene_->SetTileSize(new_tile_size);
  int offset = new_tile_size + new_tile_size/2;
  vector<cv::Point2f> checkerboard_inner_corners;
  QSize scene_size = scene_->GetSize();

  for(int i = 0; i < floor(scene_size.width()/new_tile_size)-2; i++)

  {
    for(int j = 0; j < floor(scene_size.height()/new_tile_size-2); j++)
    {
      checkerboard_inner_corners.push_back(cv::Point2f(
                                             (float)(offset + i*new_tile_size),
                                             (float)(offset + j*new_tile_size)
                                             ));
    }
  }
  scene_->SetWindowViewLandmarks(checkerboard_inner_corners);
}

void MainController::DetectNewObject() {
  cv::Mat img  = main_camera_->Capture(), gray, edges;

  cv::cvtColor(img, gray, CV_BGR2GRAY);
  cv::GaussianBlur(gray, gray, cv::Size(9,9), 2, 2);
  cv::imwrite("gaussianBlur.png", gray);

  cv::Canny(gray, edges, 100.0, 30.0, 3);
  cv::imwrite ("edges.png", edges);

  vector<cv::Vec3f> circles;
  cv::HoughCircles(gray,
                   circles,
                   CV_HOUGH_GRADIENT,
                   1,
                   gray.rows/10,
                   100,
                   30.0,
                   5,
                   50
                   );
  if(circles.size() > 0)
  {
    qDebug() << "found" << circles.size() << "in the screen";
    for( size_t i = 0; i < circles.size(); i++ )
    {
      cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // draw the circle center
      circle( img, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
      // draw the circle outline
      circle( img, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
    }
    cv::imwrite("detect_result.png", img);
  }
  else
  {
    qDebug() << "no circles found";
  }
  return;
}
