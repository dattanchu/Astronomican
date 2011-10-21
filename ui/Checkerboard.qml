import Qt 4.7

Grid {
  id:checker_board;
  state: "Visible"
  property int tile_size: 100;

  rows: Math.floor(height/tile_size);
  columns: Math.floor(width/tile_size);

  onWidthChanged: {
    columns: Math.floor(width/tile_size);
  }
  onHeightChanged: {
    rows: Math.floor(height/tile_size);
  }

  anchors.fill: parent;
  clip: true;

  Repeater {
    model: checker_board.columns*checker_board.rows
    Rectangle {
      width: checker_board.tile_size; height: checker_board.tile_size
      property int odd_row: Math.floor(index / checker_board.columns)%2
      property int odd_column: (index % checker_board.columns)%2
      color: (odd_row == 1 ^ odd_column == 1) ? "black" : "white"
    }
  }

  states: [
    State {
      name: "Visible"
      PropertyChanges {
        target: checker_board;
        visible: true;
      }
    },State {
      name: "Invisible"
      PropertyChanges {
        target: checker_board;
        visible: false;
      }
    }
  ]
}

