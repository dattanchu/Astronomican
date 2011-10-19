import Qt 4.7

Grid {
  id:container;
  state: "Visible"

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

