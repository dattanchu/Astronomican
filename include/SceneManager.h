#ifndef ASTRONOMICAN_SCENE_MANAGER_H_
#define ASTRONOMICAN_SCENE_MANAGER_H_
#include <QObject>
#include <vector>
#include <QSize>
#include <cv.h>
#include <QGraphicsScene>

#include "MovableUnit.h"

/** \class SceneManager
   Manage in memory the location of the different objects and other properties
   of the scene (e.g. scene geometry in real space, homography conversion)
*/
class SceneManager : public QGraphicsScene {
  Q_OBJECT
public:
  SceneManager();
  void TrackNewMovableUnit(MovableUnit *new_unit);
  int TrackingUnitsNumber();
  void ClearTracker();
  void SetSize (const QSize &new_size);
  void SetTileSize (const int new_tile_size);
  // TODO(tchu): Move to QSize GetSize()Tracconst as appropriate
  int GetTileSize() const;
  std::vector<cv::Point2f> GetWindowViewLandmarks() const;
  std::vector<cv::Point2f> GetCameraViewLandmarks() const;
  cv::Mat GetHomo() const;
  void SetWindowViewLandmarks(const std::vector<cv::Point2f>& new_landmarks);
  void SetCameraViewLandmarks(const std::vector<cv::Point2f>& new_landmarks);
  void SetCameraToDisplayHomo(const cv::Mat& new_homo);
  void DrawAllUnits();
  QSize& GetSize();
signals:
  void DrawUnit(MovableUnit unit);
private:
  std::vector<MovableUnit*> movable_units;
  std::vector<cv::Point2f> window_view_landmarks;
  std::vector<cv::Point2f> camera_view_landmarks;
  cv::Mat camera_to_display_homography;
  QSize size_;
  int tile_size_;
};

#endif
