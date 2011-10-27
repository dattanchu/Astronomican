#include "MovableUnit.h"
MovableUnit::MovableUnit() {
  location_ = QPoint(0,0);
  radius_ = 28;
}

MovableUnit::MovableUnit(QPoint location, float radius) {
  location_ = location;
  radius_ = radius;
}

MovableUnit::MovableUnit(const MovableUnit& unit) {
  location_  = unit.get_location();
  radius_ = unit.get_radius();
}

void MovableUnit::set_location(const QPoint& new_point) {
  location_ = new_point;
}

QPoint MovableUnit::get_location() const {
  return location_;
}

void MovableUnit::set_radius(const float new_radius) {
  radius_ = new_radius;
}

float MovableUnit::get_radius() const {
  return radius_;
}
