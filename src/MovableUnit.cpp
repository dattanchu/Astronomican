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
  location_  = unit.location();
  radius_ = unit.radius();
}

void MovableUnit::setLocation(const QPoint& new_point) {
  location_ = new_point;
}

QPoint MovableUnit::location() const {
  return location_;
}

void MovableUnit::setRadius(const float new_radius) {
  radius_ = new_radius;
}

float MovableUnit::radius() const {
  return radius_;
}

QRect MovableUnit::boudingRect() const {
  return QRectF(-radius_/2, -radius_/2,
                radius_/2, radius_/2);
}

void MovableUnit::paint(QPainter *painter,
           const QStyleOptionGraphicsItem *option,
           QWidget *widget) {
  painter->drawEllipse(QPoint(0,0), radius_, radius_);
}
