import QtQuick 2.15

Rectangle {
    width: 200
    height: 55
    transformOrigin: Item.Center
    border.color: "white"
    border.width: 2
    radius : 5

    property string label: "";
    property int game: 0;
    property string startingColor: "";

    // Ucitati level ili iz saved datotekte
    property bool loadLevel: true

    MouseArea {
        width: 200
        anchors.fill: parent
        onClicked: {
            window.game = game;
            if (loadLevel){
                grid.generate()
                grid.initGrid_game(window.game);
            } else {
                grid.initGrid_file_txt(window.game)
            }
            menu.visible = false
            guest.visible = false
            title.visible = false
            background.visible = false
            sudoku.visible = true
            timer.start()
        }

        hoverEnabled: true

        onEntered: {
            parent.color = "#009688";
            cursorShape = Qt.PointingHandCursor
        }

        onExited: {
            parent.color = startingColor;
        }
    }

    Text {
        height: 55
        width: 200
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 1
        text: label
        color: "white"
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenterOffset: 0
        font.bold: true
        font.family: "Arial"
    }
}
