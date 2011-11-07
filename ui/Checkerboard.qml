import Qt 4.7

Item {
  id:container;
  signal sizeChanged( int rows, int columns );
  property int tile_size: 150;

  onWidthChanged: {
    sizeChanged( board.columns, board.rows );
  }

  onHeightChanged: {
    sizeChanged( board.columns, board.rows );
  }

  Grid {
    id:board;
    state: "Visible"


    anchors.fill: parent;
    anchors.margins: container.tile_size/2;

    clip: true;

    rows: Math.floor(height/container.tile_size);
    columns: Math.floor(width/container.tile_size);

    onWidthChanged: {
      columns: Math.floor(width/container.tile_size);
    }

    onHeightChanged: {
      rows: Math.floor(height/container.tile_size);
    }

    Repeater {
      model: board.columns*board.rows
      Rectangle {
        width: container.tile_size; height: container.tile_size
        property int odd_row: Math.floor(index / board.columns)%2
        property int odd_column: (index % board.columns)%2
        color: (odd_row == 1 ^ odd_column == 1) ? "white" : "black"
      }
    }

    function destroy() {
      console.log("destroy the checkerboard");
      board.destroy();
    }

  //  states: [
  //    State {
  //      name: "Visible"
  //      PropertyChanges {
  //        target: container;
  //        visible: true;
  //      }
  //    },State {
  //      name: "Invisible"
  //      PropertyChanges {
  //        target: container;
  //        visible: false;
  //      }
  //    }
  //  ]

  }


}

