import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Item {
    id: timerControls

    Button {
        id: controlButton
        height: 25
        width: 25
        x: 100
        y: 25
        z: 20
        ToolTip.visible: hovered
        ToolTip.text: isStart ? "Pauziraj" : "Nastavi"
        property bool isStart: true;

        background: Rectangle {
            color: "transparent"
        }

        onClicked: {
            if(isStart) {
                timer.stop();
                gridView.visible = false;
                hintButton.enabled = false
            } else {
                timer.start();
                gridView.visible = true;
                hintButton.enabled = true
            }

            isStart = !isStart;
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: controlButton.clicked();
        }

        Image {
            id : stop
            height: 25
            width: 25
            source: controlButton.isStart ? "qrc:///images/pause-button.png" : "qrc:///images/play-button.png"
            fillMode: Image.Stretch
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }
    }
}
