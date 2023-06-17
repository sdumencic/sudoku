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

    MouseArea {
        width: 200
        anchors.fill: parent
        onClicked: {
            grid.initGrid_file_txt(game)
            menu.visible = false
            guest.visible = false
            text1.visible = false
            background.visible = false
            rect_game.visible = true
            themeImage.visible = true
            customSwitch.visible = true
            timerText.visible = true            
            buttonStop.visible = true
            buttonStart.visible = true
            timer.start();
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
        id: debutant
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
