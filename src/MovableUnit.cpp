#include "MovableUnit.h"

void MovableUnit::set_location(const QPoint& new_point) {
  location_ = new_point;
}

QPoint MovableUnit::get_location() const {
  return location_;
}

