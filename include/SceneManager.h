#ifndef ASTRONOMICAN_SCENE_MANAGER_H_
#define ASTRONOMICAN_SCENE_MANAGER_H_
#include <QObject>
#include <vector>
#include <QSize>
#include <cv.h>

#include "MovableUnit.h"

/** \class SceneManager
   Manage in memory the location of the different objects and other properties
   of the scene (e.g. scene geometry in real space, homography conversion)
*/
class SceneManager : public QObject {
  Q_OBJECT
public:
  SceneManager();
  void SetSize (const QSize &new_size);
  void SetTileSize (const int new_tile_size);
  // TODO(tchu): Move to QSize GetSize() const as appropriate
  int GetTileSize();
  std::vector<cv::Point2f> GetWindowViewLandmarks();
  std::vector<cv::Point2f> GetCameraViewLandmarks();
  void SetWindowViewLandmarks(std::vector<cv::Point2f> new_landmarks);
  void SetCameraViewLandmarks(std::vector<cv::Point2f> new_landmarks);
  QSize& GetSize();
private:
  std::vector<MovableUnit> movable_units;
  std::vector<cv::Point2f> window_view_landmarks;
  std::vector<cv::Point2f> camera_view_landmarks;
  QSize size_;
  int tile_size_;
};

#endif
