#include "SceneManager.h"
#include "QtCore"

SceneManager::SceneManager(QSettings *settings){
  settings_ = settings;
  this->readSettings();
}
SceneManager::~SceneManager() {
  this->writeSettings();
}

void SceneManager::SetSize(const QSize &new_size) {
    size_ = new_size;
    qDebug() << "Current board size is:" << size_;
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

void SceneManager::SetWindowViewLandmarks(
    const std::vector<cv::Point2f>& new_landmarks)
{
    window_view_landmarks = new_landmarks;
}

std::vector<cv::Point2f> SceneManager::GetCameraViewLandmarks() const{
    return camera_view_landmarks;
}

void SceneManager::SetCameraViewLandmarks(
    const std::vector<cv::Point2f>& new_landmarks)
{
  camera_view_landmarks = new_landmarks;
}

void SceneManager::writeSettings()
{
//  QSettings settings(QSettings::IniFormat, QSettings::UserScope,
//                     "Tri Chu", "Astronomican");
  QSettings settings("Astronomican.ini", QSettings::IniFormat);

  settings.beginGroup("SceneManager");
  settings.setValue("size", this->GetSize());
  settings.setValue("tileSize", this->GetTileSize());
  settings.endGroup();
}

void SceneManager::readSettings()
{
//  QSettings settings(QSettings::IniFormat, QSettings::UserScope,
//                     "Tri Chu", "Astronomican");
  QSettings settings("Astronomican.ini", QSettings::IniFormat);

  settings.beginGroup("SceneManager");
  size_ = settings.value("size", QSize(11, 5)).toSize();
  tile_size_ = settings.value("tileSize", 150).toInt();
  settings.endGroup();
}


//void SceneManager::ClearScreenColor(QColor color)
//{
//  QBrush brush(color, Qt::SolidPattern);
//  this->setBackgroundBrush(brush);
//  emit (ScreenColorCleared(color));
//}

//void SceneManager::SetCameraToDisplayHomo(const cv::Mat& new_homo) {
//  camera_to_display_homography = new_homo;
//}

//cv::Mat SceneManager::GetHomo() const{
//  return camera_to_display_homography;
//}

//void SceneManager::TrackNewMovableUnit(MovableUnit *new_unit) {
//  movable_units.push_back(new_unit);
//}

//int SceneManager::TrackingUnitsNumber() {
//  return movable_units.size();
//}

//void SceneManager::ClearTracker() {
//  movable_units.clear();
//}

//void SceneManager::DrawAllUnits() {
//  for ( int i = 0; i < movable_units.size(); i++ )  {
//    emit (DrawUnit(*movable_units[i]));
//  }
//}
