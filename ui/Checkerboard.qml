import QtQuick 1.0

Grid {
  id:container
  property int tile_width:100
  property int tile_height:100

  function show(w, h) {
    calibration_checkerboard.opacity = 1;
    calibration_checkerboard.columns;
    calibration_checkerboard.rows;
  }

  function hide() {
    container.opacity = 0;
    container.closed();
  }
}
