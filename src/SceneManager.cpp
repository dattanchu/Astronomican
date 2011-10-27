#include "SceneManager.h"
#include "QtCore"

SceneManager::SceneManager(){
  size_ = QSize(800, 600);
  tile_size_ = 100;
}

void SceneManager::SetSize(const QSize &new_size) {
    size_ = new_size;
    qDebug() << "Current size is:" << size_;
}

QSize& SceneManager::GetSize() {
  return size_;
}

void SceneManager::SetTileSize(const int new_tile_size) {
  tile_size_ = new_tile_size;
}

int SceneManager::GetTileSize() const{
  return tile_size_;
}

std::vector<cv::Point2f> SceneManager::GetWindowViewLandmarks() const{
    return window_view_landmarks;
}

void SceneManager::SetWindowViewLandmarks(const std::vector<cv::Point2f>& new_landmarks) {
    window_view_landmarks = new_landmarks;
}

std::vector<cv::Point2f> SceneManager::GetCameraViewLandmarks() const{
    return camera_view_landmarks;
}

void SceneManager::SetCameraViewLandmarks(const std::vector<cv::Point2f>& new_landmarks) {
    window_view_landmarks = new_landmarks;
}

void SceneManager::SetCameraToDisplayHomo(const cv::Mat& new_homo) {
  camera_to_display_homography = new_homo;
}

cv::Mat SceneManager::GetHomo() const{
  return camera_to_display_homography;
}

void SceneManager::TrackNewMovableUnit(MovableUnit *new_unit) {
  movable_units.push_back(new_unit);
}

int SceneManager::TrackingUnitsNumber() {
  return movable_units.size();
}

void SceneManager::ClearTracker() {
  movable_units.clear();
}

void SceneManager::DrawAllUnits() {

}
