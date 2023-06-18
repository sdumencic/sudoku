import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Button {
    id: buttonHint
    x: row_buttons.x + row_buttons.width + 10
    y: row_buttons.y - 10
    z: 20
    height: 70
    width: 70

    background: Rectangle {
        radius: 100
        color: buttonHint.hovered ? "lightblue" : "transparent"

        Image {
            id: hint
            height: 50
            width: 50
            source: "qrc:///images/lightbulb.png"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: buttonHint.clicked();
    }

    onClicked: {
        grid.help()
    }
}
