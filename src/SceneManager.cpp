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

int SceneManager::GetTileSize() {
  return tile_size_;
}

std::vector<cv::Point2f> SceneManager::GetWindowViewLandmarks() {
    return window_view_landmarks;
}

void SceneManager::SetWindowViewLandmarks(std::vector<cv::Point2f> new_landmarks) {
    window_view_landmarks = new_landmarks;
}

std::vector<cv::Point2f> SceneManager::GetCameraViewLandmarks() {
    return camera_view_landmarks;
}

void SceneManager::SetCameraViewLandmarks(std::vector<cv::Point2f> new_landmarks) {
    window_view_landmarks = new_landmarks;
}
