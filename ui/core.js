var drawAbleObjects = new Array();
var checkerBoard;

function createCheckerBoard() {
  var component = Qt.createComponent("Checkerboard.qml");

  if(component.status == Component.Ready) {
    var dynamicObject = component.createObject(background)

    if(dynamicObject == null) {
      console.log("error creating checkerboard");
      console.log(compoent.errorString());
      return false;
    }

    dynamicObject.tile_size = background.tile_size;
  } else {
    console.log("error loading checkerboard component");
    console.log(component.errorString());
    return false;
  }
  return true;
}

function deleteCheckerBoard() {
  if(checkerBoard == null)
  {
    console.log("error deleting null checkerboard object");
    console.log(component.errorString());
  }
  else
  {
    checkerBoard.destroy();
  }
}
