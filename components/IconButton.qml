import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Button {
    id: hintButton
    x: controlButtons.x + controlButtons.width + 10
    y: controlButtons.y - 10
    z: 20
    height: 70
    width: 70
    enabled: true

    ToolTip.visible: hovered
    ToolTip.text: "Riješi 1 nasumičnu ćeliju"

    background: Rectangle {
        radius: 100
        color: hintButton.hovered ? "lightblue" : "transparent"

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
        onClicked: hintButton.clicked();
    }

    onClicked: {
        grid.help()
    }
}
