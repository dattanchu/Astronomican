import Qt 4.7
import QtQuick 1.0

Rectangle {
    id: background
    objectName: "background"

    width: 800;
    height: 600;
    signal sizeChanged(int new_width, int new_height)
    signal draw
    signal calibrate
    property int tile_size: 200;

    anchors.fill: parent
    color: "White"

    onWidthChanged: {
        background.sizeChanged(width,height);
    }

    onHeightChanged: {
        background.sizeChanged(width,height);
    }


    Checkerboard {
        id: checker_board;
        tile_size: background.tile_size;
    }

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
        id: board_button

        property bool pressed: false

        width: 100; height: 40
        anchors.right: calibration.left; anchors.rightMargin: 20
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
                if (checker_board.state == "Visible") {
                    checker_board.state = "Invisible";
                    background.draw();
                } else {
                    checker_board.state = "Visible";
                    background.draw();
                }

                board_button.pressed = !board_button.pressed;
            }
        }

    }

}
