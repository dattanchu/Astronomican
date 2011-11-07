#ifndef ASTRONOMICAN_SCENE_MANAGER_H_
#define ASTRONOMICAN_SCENE_MANAGER_H_
#include <QObject>
#include <vector>
#include <QSize>
#include <cv.h>
#include <QGraphicsScene>
#include "MovableUnit.h"
#include <QSettings>

/** \class SceneManager
   Manage in memory the location of the different objects and other properties
   of the scene (e.g. scene geometry in real space, homography conversion)
*/
class SceneManager : public QGraphicsScene {
  Q_OBJECT
public:
  SceneManager(QSettings *settings);
  ~SceneManager();
//  void TrackNewMovableUnit(MovableUnit *new_unit);
//  int TrackingUnitsNumber();
//  void ClearTracker();

  void SetSize (const QSize &new_size);
  void SetTileSize (const int new_tile_size);
  // TODO(tchu): Move to QSize GetSize()Tracconst as appropriate
  int GetTileSize() const;

  std::vector<cv::Point2f> GetWindowViewLandmarks() const;
  std::vector<cv::Point2f> GetCameraViewLandmarks() const;
  void SetWindowViewLandmarks(
      const std::vector<cv::Point2f>& new_landmarks);
  void SetCameraViewLandmarks(
      const std::vector<cv::Point2f>& new_landmarks);

//  void DrawAllUnits();
  QSize& GetSize();
  void readSettings();
  void writeSettings();

public slots:
//  void ClearScreenColor(QColor color);
protected:
//  void paintEvent(QPaintEvent *event);

signals:
//  void DrawUnit(MovableUnit unit);
//  void ScreenColorCleared(QColor color);
private:
  std::vector<MovableUnit*> movable_units;
  std::vector<cv::Point2f> window_view_landmarks;
  std::vector<cv::Point2f> camera_view_landmarks;
  QSettings *settings_;
  QSize size_;
  int tile_size_;
};

#endif
