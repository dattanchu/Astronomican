#ifndef ASTRONOMICAN_SCENE_MANAGER_H_
#define ASTRONOMICAN_SCENE_MANAGER_H_
#include <QObject>
#include <vector>
#include <QSize>

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
  QSize& GetSize();
private:
  std::vector<MovableUnit> movable_units;
  QSize size_;
  int tile_size_;
};

#endif
