import Qt 4.7
import QtQuick 1.0
import "core.js" as logic

Rectangle {
    id: background
    objectName: "background"

    width: 800;
    height: 600;
    signal sizeChanged(int new_width, int new_height)
    signal draw
    signal calibrate
    signal resize
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

//    function createCheckerBoard() {
//        var component = Qt.createComponent("Checkerboard.qml");
//        var checker_board = component.createObject(background);
//        if(checker_board != null) {
//          checker_board.id = 'checker_board'
//          checker_board.tile_size = background.tile_size;
//        }
//        background.board_alive = true;
//    }

//    Checkerboard {
//      id: checker_board;
//      tile_size: background.tile_size;
//    }

    Rectangle {
        id: calibration

        width: 100; height: 40
        anchors.right: parent.right; anchors.rightMargin: 20
        anchors.bottom: parent.bottom; anchors.bottomMargin: 20
        radius: 6

        Text {
            anchors.centerIn: parent
            text: "camera"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.calibrate();
            }
        }
    }

    Rectangle {
        id: resize

        width: 100; height: 40
        anchors.right: calibration.left; anchors.rightMargin: 20
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
                logic.createCheckerBoard();
              }
              else
              {
                logic.deleteCheckerBoard();
              }
            }
        }

    }

}
