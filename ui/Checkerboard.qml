import Qt 4.7

Grid {
  id:container;
  state: "Visible"

  anchors.fill: parent;
  anchors.margins: tile_size/2;

  clip: true;

  property int tile_size;

  rows: Math.floor(height/tile_size);
  columns: Math.floor(width/tile_size);

  onWidthChanged: {
    columns: Math.floor(width/tile_size);
  }
  onHeightChanged: {
    rows: Math.floor(height/tile_size);
  }

  Repeater {
    model: container.columns*container.rows
    Rectangle {
      width: container.tile_size; height: container.tile_size
      property int odd_row: Math.floor(index / container.columns)%2
      property int odd_column: (index % container.columns)%2
      color: (odd_row == 1 ^ odd_column == 1) ? "black" : "white"
    }
  }

  states: [
    State {
      name: "Visible"
      PropertyChanges {
        target: container;
        visible: true;
      }
    },State {
      name: "Invisible"
      PropertyChanges {
        target: container;
        visible: false;
      }
    }
  ]

}

