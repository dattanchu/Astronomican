#include "CameraFeed.h"
#include "MainController.h"
#include "SceneManager.h"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/video/tracking.hpp"
#include "MovableUnit.h"

#include <QtAlgorithms>
#include <iostream>
#include <QtCore>
#include <vector>

using namespace std;

MainController::MainController(QSettings *settings) {
  main_camera_ = NULL;
  settings_ = settings;
  scene_ = new SceneManager(settings_);
  scene_->setBackgroundBrush(Qt::black);
}

MainController::~MainController() {
//  delete main_window_;

  main_camera_->StopCapturing();
//  delete main_camera_;
  delete scene_;
}

void MainController::AddCameraFeed(CameraFeed *camera_feed) {
  main_camera_ = camera_feed;
}

void MainController::SetUpMainWindow(MainWindow *window) {
  main_window_ = window;
  main_window_->SetUpSceneView(scene_);
}

void MainController::SetSize(int new_width, int new_height) {
  scene_->SetSize(QSize(new_width,new_height));
}

// Does the connection of slots and signals
void MainController::GetReady() {
  connect(main_camera_, SIGNAL(HasNewFrame(cv::Mat)),
          this, SLOT(HandleNewFrame(cv::Mat)));
  connect(main_window_, SIGNAL(sizeChanged(int, int)),
          this, SLOT(SetSize(int, int)));
  connect(main_window_, SIGNAL(tileSizeChanged(int)),
          this, SLOT(TileSizeChanged(int)));
  connect(main_window_, SIGNAL(Calibrate()),
          this, SLOT(CalibrateCamera()));
  connect(main_window_, SIGNAL(Detect()),
          this, SLOT(DetectNewObject()));
  connect(main_window_, SIGNAL(Quit()),
          this, SLOT(Exit()));
  connect(main_window_, SIGNAL(DiceRegisterSetup()),
          this, SLOT(DiceRegisterSetup()));
  connect(main_window_, SIGNAL(DiceRegisterMain()),
          this, SLOT(DiceRegisterMain()));
//  connect(main_window_, SIGNAL(NewScreenShot(cv::Mat*)),
//          this, SLOT(HandleNewScreenshot(cv::Mat*)));
//  connect(scene_, SIGNAL(DrawUnit(MovableUnit)),
//          main_window_, SLOT(DrawCircle(MovableUnit)));
}

void MainController::HandleNewFrame(const cv::Mat& new_frame) {
  cv::imshow("Current frame", new_frame);
  cv::waitKey(10);
}

//TODO: automate the flip camera flag and add the calibration function to
//the application pipeline instead of activating it manually
void MainController::CalibrateCamera() {

  //reserved flag to automatically flip the camera view so the corner are
  //found correctly
  //Step 1: detect the landmark and tell the camera if it is rotated or not
  FLIP_CAMERA_VIEW = true;

  qDebug() << "calibrating";
  vector<cv::Point2f> corners;

  cv::Mat capture = main_camera_->CaptureOneShot();
  cv::Mat view = main_window_->TakeScreenshot().clone();

  cv::Mat capture_gray;

  if(FLIP_CAMERA_VIEW)
    cv::flip(capture, capture, -1);

  cv::imwrite("capture.png",capture);

  //Step 2: detect the checkerboard and return the land marks coordinate in
  //camera plane
//  int tile_size = scene_->GetTileSize();
  QSize scene_size = scene_->GetSize();

  //board size is 2 tile smaller than the total (screen_size)/(tile_size)
  //instead of 1 because of the margins
//  int board_w = floor(scene_size.width()/tile_size)-2;
//  int board_h = floor(scene_size.height()/tile_size)-2;
//  cv::Size board_size(board_w, board_h);
  cv::Size board_size(scene_size.width() - 1, scene_size.height() - 1);
  cv::cvtColor(capture,capture_gray,CV_BGR2GRAY);
  cv::imwrite("capture_gray.png", capture_gray);

  bool found = cv::findChessboardCorners(capture, board_size, corners,
                                         CV_CALIB_CB_ADAPTIVE_THRESH |
                                         CV_CALIB_CB_FAST_CHECK |
                                         CV_CALIB_CB_NORMALIZE_IMAGE);

  if(found)
  {
    cv::cornerSubPix(capture_gray, corners,
                     cv::Size(11, 11),
                     cv::Size(-1,-1),
                     cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,
                                       30, 0.1 ));
    cv::Mat temp = capture.clone();
    cv::drawChessboardCorners(temp, board_size, corners, found);
    cv::imwrite("calibration_result.png", temp);
    scene_->SetCameraViewLandmarks(corners);
    qDebug() << "found chessboard";
  }
  else
  {
    qDebug() << "can not find chessboard";
  }

  //Step 3: Using the camera landmarks coordinate and our scene coordinates
  //find the homography matrix between camera plane and display plane
  if(found)
  {
    vector<cv::Point2f> display_points = scene_->GetWindowViewLandmarks();
    cv::Mat H = cv::findHomography(
          cv::Mat(corners),
          cv::Mat(display_points),
          CV_RANSAC,
          3.0);
    main_camera_->SetHomography(H);

    //Step 3-1: Test the homography matrix
    cv::Mat test_points;
    cv::Mat temp = view.clone();
    cv::perspectiveTransform(cv::Mat(corners), test_points, H);
    cv::drawChessboardCorners(temp, board_size, test_points, found);
    cv::imwrite("homography_test.png", temp);

    //Step 3-2: Test invert homography matrix
    cv::Mat H_i = H.inv();
    cv::Mat test_points1;
    cv::perspectiveTransform(cv::Mat(display_points), test_points1, H_i);
    temp = capture.clone();
    cv::drawChessboardCorners(temp, board_size, test_points1, found);
    cv::imwrite("homography_inverse_test.png", temp);

    //Step 3-3: Test homography by drawing the
    //captured chessboard to the vitural view
    cv::Mat output;
    cv::warpPerspective(
          capture,
          output,
          H,
          cv::Size(view.cols,view.rows),
          (CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS)
          );
    cv::drawChessboardCorners(output, board_size, test_points, found);
    cv::imwrite("homography_test2.png", output);

  }


//  //Step 4: display saturated color screen to detect the view area
//  if(found) {
//  main_window_->Toggle();
//  connect(this->main_window_, SIGNAL(ViewColorCleared(QColor)),
//          this, SLOT(GetScreenAreaPicture(QColor)));
////  connect(this->scene_, SIGNAL(ScreenColorCleared(QColor)),
////          this, SLOT(GetScreenAreaPicture(QColor)));

//  this->scene_->ClearScreenColor(QColor("green"));
//  this->main_window_->RepaintGamePage(QColor("green"));
//  this->scene_->ClearScreenColor(QColor("blue"));
//  this->main_window_->RepaintGamePage(QColor("blue"));
//  this->scene_->ClearScreenColor(QColor("white"));
//  this->main_window_->RepaintGamePage(QColor("white"));

////  disconnect(this->scene_, SIGNAL(ScreenColorCleared(QColor)),
////          this, SLOT(GetScreenAreaPicture(QColor)));
//  disconnect(this->main_window_, SIGNAL(ViewColorCleared(QColor)),
//          this, SLOT(GetScreenAreaPicture(QColor)));
//  main_window_->Toggle();

//  }

}

void MainController::TileSizeChanged(int new_tile_size) {
  scene_->SetTileSize(new_tile_size);
  int offset = new_tile_size + new_tile_size/2;
  vector<cv::Point2f> checkerboard_inner_corners;
  QSize scene_size = scene_->GetSize();


//  int columns = floor(scene_size.width()/new_tile_size) - 2;
//  int rows = floor(scene_size.height()/new_tile_size) - 2;
  int columns = scene_size.width() - 1;
  int rows = scene_size.height() - 1;

  for(int j = 0; j < rows; j++)
  {
    for(int i = 0; i < columns; i++)
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

  cv::Mat capture  = main_camera_->CaptureOneShot(), captureGray, edges;
  cv::Mat view = main_window_->TakeScreenshot();
  cv::Mat CVM; //capture to view matrix
//  cv::Mat H = main_camera_->GetHomography().clone();

  if(FLIP_CAMERA_VIEW)
    cv::flip(capture, capture, -1);

  //Step 0:background substraction
  //0-1 transform the capture image to view space
//  cv::warpPerspective(
//        capture,
//        CVM,
//        H,
//        cv::Size(view.cols,view.rows),
//        (CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS)
//        );
  ProjectToVirtualScene(capture, CVM);
  cv::imwrite("CVM.png", CVM);
  //0-2 Substract the CVM to current window view
  cv::Mat CVM_gray;
  cv::Mat blur_view;
//  cv::Mat foreground_gray;
  cv::Mat foreground;
//  cv::Mat blur_view_gray;

  cv::GaussianBlur(view, blur_view, cv::Size(45, 55), 0, 0 );

  cv::cvtColor(CVM, CVM_gray, CV_BGR2GRAY);
//  cv::cvtColor(blur_view, blur_view_gray, CV_BGR2GRAY);
//  cv::imwrite("CVM_gray.png", CVM_gray);
//  cv::imwrite("blur_view_gray.png", blur_view_gray);

  cv::cvtColor(blur_view, blur_view, CV_BGRA2BGR);
  cv::cvtColor(CVM, CVM, CV_BGRA2BGR);

  cv::imwrite("CVM.png", CVM);
  cv::imwrite("blur_view.png", blur_view);

//  cv::subtract(blur_view_gray, CVM_gray, foreground_gray);
  cv::subtract(blur_view, CVM, foreground);
  cv::imwrite("foreground.png", foreground);
//  cv::imwrite("foreground_gray.png", foreground_gray);

  cv::cvtColor(foreground, foreground, CV_BGR2GRAY);
  cv::threshold(foreground, foreground, 90, 220, CV_THRESH_BINARY);
  cv::imwrite("foregroundThr.png", foreground);

//  cv::threshold(foreground_gray, foreground_gray, 90, 250, CV_THRESH_BINARY);
//  cv::imwrite("foreground_grayThr.png", foreground_gray);

  //Step 1: find the circles
//  cv::cvtColor(capture, captureGray, CV_BGR2GRAY);
//  cv::GaussianBlur(captureGray, captureGray, cv::Size(9,9), 2, 2);
//  cv::imwrite("gaussianBlur.png", captureGray);

//  cv::Canny(captureGray, edges, 100.0, 30.0, 3);
//  cv::imwrite ("edges.png", edges);
    cv::Canny(CVM_gray, edges, 100.0, 30.0, 3);
    cv::imwrite ("edges.png", edges);
//  vector<cv::Vec3f> circles;
//  cv::HoughCircles(captureGray,
//                   circles,
//                   CV_HOUGH_GRADIENT,
//                   1,
//                   captureGray.rows/64,
//                   100,
//                   30.0,
//                   5,
//                   35
//                   );
  vector<cv::Vec3f> circles;
  cv::HoughCircles(CVM_gray,
                   circles,
                   CV_HOUGH_GRADIENT,
                   1,
                   CVM_gray.rows/12,
                   100,
                   30.0,
                   50,
                   200
                   );

  //Step 2: print out the camera image with circles marked
  cv::Mat CVM_detect_result = CVM.clone();
  if(circles.size() > 0)
  {
    qDebug() << "found" << circles.size() << "in the screen";
    for( size_t i = 0; i < circles.size(); i++ )
    {
      cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // draw the circle center
      circle( CVM_detect_result, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
      // draw the circle outline
      circle( CVM_detect_result, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
    }
    cv::imwrite("CVM_detect_result.png", CVM_detect_result);
  }
  else
  {
    qDebug() << "no circles found";
  }


//  //Step 3: apply homogrpahy to transform the coordination from
//  //camera view to computer display view
  vector<cv::Point2f> points;
  for( int i = 0; i < circles.size(); i++)
  {
    points.push_back(cv::Point2f(circles[i][0], circles[i][1]));
  }
  cv::Mat view_plane_points(points);
  cv::Mat display_plane_points;

//  cv::perspectiveTransform(view_plane_points, display_plane_points, H);

  //Step 4: Make sure the found units are all unique
  //for now it just clean the scene manager tracking unit vector
  qDeleteAll( scene_->items() );

  //Step 5: Adding the found units into the scene manager
  for( int i = 0; i < display_plane_points.rows ;i++ )
  {
    MovableUnit *unit = new MovableUnit();

    QPoint unit_pos(display_plane_points.at<cv::Point2f>(i).x,
                    display_plane_points.at<cv::Point2f>(i).y);
    unit->setPos(unit_pos);
    //    scene_->TrackNewMovableUnit(unit);
    unit->setRadius(circles[i][2]);
    scene_->addItem(unit);
  }
  qDebug() << "tracking" << scene_->items().count();
  //Step 7: call the draw function for found units
//  scene_->DrawAllUnits();
  main_window_->update();
  return;
}

void MainController::HandleNewScreenshot(cv::Mat* new_screenshot) {
  qDebug() << "pint out new screenshot";
  cv::imwrite("screenshot.png", *new_screenshot);
}

//void MainController::readSettings()
//{
////  QSettings settings("Tri Chu", "Astronomican");
//  QPoint pos = settings_.value("pos", QPoint(200, 200)).toPoint();
//  QSize size = settings_.value("size", QSize(800, 600)).toSize();
//  main_window_->resize(size);
//  main_window_->move(pos);
//}
//void MainController::writeSettings()
//{
//}

void MainController::Exit()
{
  main_camera_->StopCapturing();
  QApplication::exit(0);
}

void MainController::TemplateMatching(cv::Mat img, vector<cv::Mat> templates, int match_method)
{
  cv::Mat img_display;
  img.copyTo(img_display);


  for(vector<cv::Mat>::iterator it = templates.begin(); it < templates.end(); it++)
  {
    int result_cols = img.cols - it->cols + 1;
    int result_rows = img.rows - it->rows + 1;

    cv::Mat result(result_rows, result_cols, CV_32FC1);

    cv::matchTemplate(img, *it, result, match_method);
    cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1 );

    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::Point matchLoc;

    cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
        { matchLoc = minLoc; }
      else
        { matchLoc = maxLoc; }

    cv::rectangle( img_display,
                   matchLoc,
                   cv::Point( matchLoc.x + it->cols , matchLoc.y + it->rows ),
                   cv::Scalar::all(0),
                   2, 8, 0 );

    cv::rectangle( result,
                   matchLoc,
                   cv::Point( matchLoc.x + it->cols , matchLoc.y + it->rows ),
                   cv::Scalar::all(0),
                   2, 8, 0 );


//    cv::imshow( result_window, result );
    cv::imwrite("template_search_result.png", result);
  }
  cv::imwrite("img_display.png", img_display);

}

void MainController::DiceRegisterSetup()
{
  main_window_->SwitchToGamePage();
  int offset = scene_->GetTileSize();
  scene_->clear();
  diceSpots_.clear();

  QBrush brush(Qt::red, Qt::SolidPattern);
  QPen pen(brush, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

  for(int i = 0; i < 6; i++)
  {
    QGraphicsEllipseItem *diceSpot;
    QRect rect((i%3)*offset,
               (i/3)*offset,
               50,
               50);
    diceSpot = scene_->addEllipse(
          rect,
          pen,
          QBrush());
    diceSpots_.push_back(diceSpot);
  }
}

void MainController::DiceRegisterMain()
{
  cv::Mat capture = main_camera_->CaptureOneShot();
  cv::Mat CVM;
  DiceSet newDiceSet;

  ProjectToVirtualScene(capture, CVM);
  cv::imwrite("dice_register_CVM.PNG", CVM);
  int tileSize = scene_->GetTileSize();

  vector<cv::Mat> ROIs;
  int count = 0;
  foreach(QGraphicsItem *spot, diceSpots_)
  {
    cv::Mat ROI;
    int x_offset = (count%3)*tileSize + CVM.size().width/2;
    int y_offset = (count/3)*tileSize + CVM.size().height/2;
//    qDebug() << x_offset << y_offset;
//    qDebug() << CVM.size().width << CVM.size().height;
    ROI = CVM(cv::Range( y_offset - 20, y_offset + 70),
        cv::Range( x_offset - 20, x_offset + 70));
    ROIs.push_back(ROI);
//    QString temp = "dice";
//    temp.append(QString::number(count));
//    temp.append(".PNG");
//    cv::imwrite(temp.toStdString(), ROI);
    count++;
  }
  newDiceSet.RegisterTempls("newDiceSet", ROIs);
  newDiceSet.SaveTemplate();
}

void MainController::ProjectToVirtualScene(const cv::Mat& input, cv::Mat& output)
{
  cv::Mat H = main_camera_->GetHomography().clone();
  cv::Mat flipped_input;
  if(FLIP_CAMERA_VIEW)
    cv::flip(input, flipped_input, -1);
  else
    flipped_input = input;

  QSize view_size = main_window_->GetUISize();

  cv::warpPerspective(
        flipped_input,
        output,
        H,
        cv::Size(view_size.width(),view_size.height()),
        (CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS)
        );

}
//void MainController::GetScreenAreaPicture(QColor color)
//{
//  QString filename = color.name() + "_screen.png";
//  cv::Mat frame = this->main_camera_->Capture();
//  cv::imwrite(filename.toStdString(), frame);
//}
