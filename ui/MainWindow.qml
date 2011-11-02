import Qt 4.7
import QtQuick 1.0
import "core.js" as Logic
import Unit 1.0

Rectangle {
  id: background
  objectName: "background"

  width: 800;
  height: 600;
  signal sizeChanged(int new_width, int new_height)
  signal calibrate
  signal resize
  signal detect
  signal screencap
  property int tile_size: 170;
  property bool board_alive: false;

  anchors.fill: parent;
  color: "White";

  onWidthChanged: {
    background.sizeChanged(width,height);
  }

  onHeightChanged: {
    background.sizeChanged(width,height);
  }

  function createCircle(x, y, radius) {
    Logic.drawMovableUnit(x, y, radius)
  }
  function clearDrawObject() {
    Logic.clearDrawObject();
  }
  function clearColorBuffer(color) {
    background.color = color;
  }
  function deleteCheckerBoard() {
    Logic.deleteCheckerBoard();
  }

  function createCheckerBoard() {
    Logic.createCheckerBoard();
  }


//  Rectangle {
//    id: calibration

//    width: 100; height: 40
//    anchors.right: parent.right; anchors.rightMargin: 20
//    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
//    radius: 6

//    Text {
//      anchors.centerIn: parent
//      text: "calibrate"
//    }

//    MouseArea {
//      anchors.fill: parent
//      onClicked: {
//        background.calibrate();
//      }
//    }
//  }

  Rectangle {
    id: resize

    width: 100; height: 40
    anchors.right: parent.right; anchors.rightMargin: 20
    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
    radius: 6

    Text {
      anchors.centerIn: parent
      text: "resize"
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        background.resize();
      }
    }
  }

  Rectangle {
    id: board_button

    property bool pressed: false

    width: 100; height: 40
    anchors.right: resize.left; anchors.rightMargin: 20
    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
    radius: 6
    color: pressed ? "gray" : "white"

    Text {
      anchors.centerIn: parent
      text: "board"
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        if(!background.board_alive)
        {
          Logic.createCheckerBoard();
          background.board_alive = true;
        }
        else
        {
          Logic.deleteCheckerBoard();
          background.board_alive = false;
        }
      }
    }

  }
//  Rectangle {
//    id: detect

//    property bool pressed: false

//    width: 100; height: 40
//    anchors.right: board_button.left; anchors.rightMargin: 20
//    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
//    radius: 6
//    color: pressed ? "gray" : "white"

//    Text {
//      anchors.centerIn: parent
//      text: "detect"
//    }

//    MouseArea {
//      anchors.fill: parent
//      onClicked: {
////        Logic.clearDrawObject();
//        background.detect();
//      }
//    }

//  }

//  Rectangle {
//    id: capture_screen

//    property bool pressed: false

//    width: 100; height: 40
//    anchors.right: detect.left; anchors.rightMargin: 20
//    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
//    radius: 6
//    color: pressed ? "gray" : "white"

//    Text {
//      anchors.centerIn: parent
//      text: "screencap"
//    }

//    MouseArea {
//      anchors.fill: parent
//      onClicked: {
//        Logic.clearDrawObject();
//        background.screencap();
//      }
//    }

}

//}
