import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: timerControls

    Button {
        id: stopButton
        height: 25
        width: 25
        x: 100
        y: 25
        z: 20
        background: Rectangle {
            color: "transparent"
        }

        onClicked: {
            timer.stop();
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: stopButton.clicked();
        }

        Image {
            id : stop
            height: 25
            width: 25
            source: "qrc:///images/pause-button.png"
            fillMode: Image.Stretch
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }
    }

    Button {
        id: startButton
        height: 25
        width: 25
        x: 130
        y: 25
        z: 20
        background: Rectangle {
            color: "transparent"
        }

        onClicked: {
            timer.start();
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: startButton.clicked();
        }

        Image {
            id : start
            height: 25
            width: 25
            source: "qrc:///images/play-button.png"
            fillMode: Image.Stretch
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }
    }
}
