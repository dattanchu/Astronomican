import Qt 4.7
import QtQuick 1.0

Rectangle {
  id: circle_root

  property int size: 10
  property alias selectedColor: circle_root.color

  x: 0
  y: 0
  width: size
  height: size
  radius: size/2

  function destroy() {
    circle_root.destroy();
  }
}
