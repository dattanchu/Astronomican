var drawAbleObjects = new Array();
/**
  TChu Note: have to make sure that the javascript data is
  synced with the data in the application logic or it gonna create
  artifacts on the qml
  */
var checkerBoard;
var boardSrc = "Checkerboard.qml";
var component = Qt.createComponent(boardSrc);


function createCheckerBoard() {

  if(component.status == Component.Ready) {
    var dynamicObject = component.createObject(background)

    if(dynamicObject == null) {
      console.log("error creating checkerboard");
      console.log(compoent.errorString());
      return false;
    }
    dynamicObject.tile_size = background.tile_size;
    checkerBoard = dynamicObject;
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
    console.log("deleting checkerboard");
    checkerBoard.destroy();
  }
}
