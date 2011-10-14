#ifndef ASTRONOMICAN_SCENE_MANAGER_H_
#define ASTRONOMICAN_SCENE_MANAGER_H_
#include <QObject>
#include <vector>

#include "MovableUnit.h"

/** \class SceneManager
   Manage in memory the location of the different objects and other properties
   of the scene (e.g. scene geometry in real space, homography conversion)
*/
class SceneManager : public QObject {
  Q_OBJECT
public:
  SceneManager();
private:
  std::vector<MovableUnit> movable_units;
};

#endif
