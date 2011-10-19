import Qt 4.7

Rectangle {
  id: background
  objectName: "background"

  width: 800;
  height: 600;

  onWidthChanged: {
    main_controller.SetWidth(width);
  }

  onHeightChanged: {
    main_controller.SetHeight(height);
  }

  Grid {
    id:checker_board;

    property int tile_size: main_controller.GetRatio(background.width, background.height);

    rows: height/tile_size; columns: width/tile_size;

    onWidthChanged: {
      columns: width/tile_size;
    }

    onHeightChanged: {
      rows: height/tile_size;
    }

    anchors.fill: parent;
    clip: true;

    Repeater {
      model: checker_board.columns*checker_board.rows
      Rectangle {
        width: checker_board.tile_size; height: checker_board.tile_size
        color: (index % 2 == 0)? "black" : "white"
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
