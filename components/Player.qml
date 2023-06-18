import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle{
    width: window.width
    height: 50
    y: 100
    color: "transparent"

    Text {
        text: "Dobrodošao/la nazad " + player.name + "!"
        color: "white"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    Button {
        id: editPlayer
        height: 50
        width: 50
        onClicked: {
            usernamePopup.open()
        }
        anchors {
            right: parent.right
            rightMargin: 20
        }

        background: Rectangle {
            radius: 100
            color: "white"
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: editPlayer.clicked();
        }

        Image {
            id : edit
            height: 20
            width: 20
            visible: true
            source: "qrc:///images/edit.png"
            fillMode: Image.Stretch
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }
    }
}
