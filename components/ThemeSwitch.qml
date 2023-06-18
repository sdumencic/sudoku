import QtQuick 2.15

Item {
    id: customSwitch
    width: 44
    height: 24
    y: 20
    z: 10
    anchors {
        horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        width: 44
        height: 24
        radius: height / 2
        color: switchControl.checked ? "#FFF59D" : "lightgray"

        Rectangle {
            id: handle
            width: 24
            height: 24
            radius: width / 2
            color: switchControl.checked ? "#FF9800" : "gray"
            border.color: switchControl.checked ? "#FF9800" : "gray"
            border.width: 2
            anchors.horizontalCenter: switchControl.checked ? parent.right : parent.left
        }
    }

    MouseArea {
        id: switchControl
        width: parent.width
        height: parent.height
        cursorShape: Qt.PointingHandCursor
        property bool checked: theme.isLight;

        onClicked: {
            checked = !theme.isLight
            theme.setIsLight(checked)
            themeImage.source = theme.isLight ? "qrc:///images/sun.png" : "qrc:///images/moon.png"
        }
    }
}
