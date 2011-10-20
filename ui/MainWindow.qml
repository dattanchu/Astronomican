import Qt 4.7

Rectangle {
  id: background
  objectName: "background"

  width: 800;
  height: 600;
  signal sizeChanged(int new_width, int new_height)
  property int tile_size: 100

  onWidthChanged: {
    background.sizeChanged(width,height);
  }

  onHeightChanged: {
    background.sizeChanged(width,height);
  }

  Grid {
    id:checker_board;

    rows: Math.floor(background.height/background.tile_size);
    columns: Math.floor(background.width/background.tile_size);

    onWidthChanged: {
      columns: Math.floor(background.width/background.tile_size);
    }

    onHeightChanged: {
      rows: Math.floor(background.height/background.tile_size);
    }

    anchors.fill: parent;
    clip: true;

    Repeater {
      model: checker_board.columns*checker_board.rows
      Rectangle {
        width: background.tile_size; height: background.tile_size
        property int odd_row: Math.floor(index / checker_board.columns)%2
        property int odd_column: (index % checker_board.columns)%2
        color: (odd_row == 1 ^ odd_column == 1) ? "black" : "white"
      }
    }
  }



  property string text: "Using Qt class to echo this"

  function updateUI() {

  }

  anchors.fill: parent
  color: "black"

  Component.onCompleted: updateUI()


  Rectangle {
    id: camera_button

    property bool pressed: false

    width: 100; height: 40
    anchors.right: parent.right; anchors.rightMargin: 20
    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
    radius: 6
    color: pressed ? "gray" : "white"

    Text {
      anchors.centerIn: parent
      text: "camera"
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        if (camera_button.pressed) {
          // button pressed before StartCapturing
          camera_feed.StartCapturing(1);
        } else {
          camera_feed.StopCapturing();
        }

        camera_button.pressed = !camera_button.pressed;
      }
    }
  }

  Rectangle {
    id: checkerboard_button

    property bool pressed: false

    width: 100; height: 40
    anchors.right: camera_button.left; anchors.rightMargin: 20
    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
    radius: 6
    color: pressed ? "gray" : "white"

    Text {
      anchors.centerIn: parent
      text: "checkerboard"
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        if (checkerboard_button.pressed) {
          // button pressed before StartCapturing
          checker_board.show();
        } else {
          checker_board.hide();
        }

        checkerboard_button.pressed = !checkerboard_button.pressed;
      }
    }
  }

  Rectangle {
      id: tooltip1
      x: 78
      y: -46
      width: 200
      height: 200
      color: "#ffffff"
      visible: false

      Text {
        id: text
        x: -78
        y: 37
        anchors.centerIn: parent
    color: "white"
  }
  }
  states: [
      State {
          name: "State1"

          PropertyChanges {
            target: tooltip1
            radius: 10
            visible: true
          }
      }
  ]
}
