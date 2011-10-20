import Qt 4.7

Grid {
  id:container;
  state: "Visible"
  rows:  10
  columns: 10

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

