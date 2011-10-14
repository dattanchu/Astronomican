import Qt 4.7

Rectangle {
  id: background

  property string text: "Using Qt class to echo this"

  function updateUI() {

  }

  anchors.fill: parent
  color: "black"

  Component.onCompleted: updateUI()

  Rectangle {
    id: button

    property bool pressed: false

    width: 100; height: 40
    anchors.right: parent.right; anchors.rightMargin: 20
    anchors.bottom: parent.bottom; anchors.bottomMargin: 20
    radius: 6
    color: pressed ? "gray" : "white"

    Text {
      anchors.centerIn: parent
      text: "Toggle camera"
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        if (button.pressed) {
          // button pressed before StartCapturing
          camera_feed.StartCapturing(1);
        } else {
          camera_feed.StopCapturing();
        }

        button.pressed = !button.pressed;
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
