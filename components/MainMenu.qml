import QtQuick 2.15

Column {
    id: menu
    spacing: 20
    x: window.width / 2 - menu.width / 2
    y: window.height / 2 - menu.height / 2

    CustomButton {
        id : menuButton1
        label: "Početnik"
        color: "#2ecc71"
        game: 1
        startingColor: "#2ecc71"
        loadLevel: true
    }

    CustomButton {
        id : menuButton2
        label: "Lagano"
        color: "#1abc9c"
        game: 2
        startingColor: "#1abc9c"
        loadLevel: true
    }

    CustomButton {
        id : menuButton3
        label: "Srednje"
        color: "#80CBC4"
        game: 3
        startingColor: "#80CBC4"
        loadLevel: true
    }

    CustomButton {
        id : menuButton4
        label: "Napredno"
        color: "#ff9800"
        game: 4
        startingColor: "#ff9800"
        loadLevel: true
    }

    CustomButton {
        id : menuButton5
        label: "Nastavi spremljeno"
        color: "#00BCD4"
        game: 5
        startingColor: "#00BCD4"
        visible : grid.show_save_game ? true : false
        loadLevel: false
    }
}
