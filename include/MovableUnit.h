#ifndef MOVABLE_UNIT_H_
#define MOVABLE_UNIT_H_
#include <QObject>
#include <QPoint>

#include "MovableUnit.h"

/** \class MovableUnit
   MovableUnit is like the space marine units on 28mm or a Dreadnought unit on
   a bigger base. As long as it is on a base that we can recognize. It is a
   MovableUnit
*/
class MovableUnit : public QObject {
  Q_OBJECT
public:
  MovableUnit();
  void set_location(const QPoint& new_point);
  QPoint get_location() const;
private:
  // (0,0) is at the top left and x horizontal pointing left, y is vertical
  // pointing down (similar to the indexing of matrices)
  QPoint location_;
  float radius_; // This probably will only be choices among {28, 55???}
  int id_; //unique ID for tracking
};

#endif
