import Qt 4.7


Rectangle {
  id: background
  objectName: "background"

  width: 800;
  height: 600;
  signal sizeChanged(int new_width, int new_height)
  property int tile_size: 100;

  onWidthChanged: {
    background.sizeChanged(width,height);
  }

  onHeightChanged: {
    background.sizeChanged(width,height);
  }

  Checkerboard {id: checker_board; tile_size: background.tile_size}

  property string text: "Using Qt class to echo this"

  function updateUI() {

  }

//  function LoadCheckerboard() {
//    var component = Qt.createComponent("Checkerboard.qml");
//    if (component.status == Component.Ready) {
//      var checkerboard = component.createObject(checker_board);
//    }
//  }

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
    id: board_button

    property bool pressed: false

    width: 100; height: 40
    anchors.right: camera_button.left; anchors.rightMargin: 20
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
        } else {
          checker_board.state = "Visible";
        }

        board_button.pressed = !board_button.pressed;
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
