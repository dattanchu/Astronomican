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
  Q_PROPERTY(QPoint location READ location WRITE setLocation)
  Q_PROPERTY(float radius READ radius WRITE setRadius)
public:
  MovableUnit();
  MovableUnit(QPoint location, float radius);
  MovableUnit(const MovableUnit& unit);
  void setLocation(const QPoint& new_point);
  QPoint location() const;
  void setRadius(const float new_radius);
  float radius() const;
private:
  // (0,0) is at the top left and x horizontal pointing left, y is vertical
  // pointing down (similar to the indexing of matrices)
  QPoint location_;
  float radius_; // This probably will only be choices among {28, 55???}
};

#endif
