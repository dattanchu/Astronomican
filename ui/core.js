
/**
  TChu Note: have to make sure that the javascript data is
  synced with the data in the application logic or it gonna create
  artifacts on the qml
  */
var checkerBoard;
var boardSrc = "Checkerboard.qml";
var circleSrc = "circle.qml";
var board_component = Qt.createComponent(boardSrc);
var drawAbleObjects = new Array();

function createCheckerBoard() {

  if(board_component.status == Component.Ready) {
    var dynamicObject = board_component.createObject(background)

    if(dynamicObject == null) {
      console.log("error creating checkerboard");
      console.log(compoent.errorString());
      return false;
    }
    dynamicObject.tile_size = background.tile_size;
    checkerBoard = dynamicObject;
  } else {
    console.log("error loading checkerboard component");
    console.log(board_component.errorString());
    return false;
  }
  return true;
}

function deleteCheckerBoard() {
  if(checkerBoard == null)
  {
    console.log("error deleting null checkerboard object");
    console.log(board_component.errorString());
  }
  else
  {
    console.log("deleting checkerboard");
    checkerBoard.destroy();
  }
}

function drawMovableUnit(x, y, radius) {
  var component = Qt.createComponent(circleSrc);
  if(component.status == Component.Ready) {
    var dynamicObject = component.createObject(background)

    if(dynamicObject == null) {
      console.log("error creating circle object");
      console.log(component.errorString());
      return false;
    }
    dynamicObject.x = x;
    dynamicObject.y = y;
    dynamicObject.size = radius*10;
    dynamicObject.color = "blue"
    drawAbleObjects.push(dynamicObject);
  } else {
    console.log("error loading cicle component");
    console.log(board_component.errorString());
    return false;
  }
  console.log("drawing a circle at "+ x + " "+ y + " with radius " + radius)
  return true;
}

function clearDrawObject() {
  for (var i=0; i < drawAbleObjects.length; i++)
  {
    drawAbleObjects[i].destroy();
  }
}
