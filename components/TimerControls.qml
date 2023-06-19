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
        ToolTip.text: "Pauziraj"
        property bool isStart: true;

        background: Rectangle {
            color: "transparent"
        }

        onClicked: {
            if(isStart) {
                timer.stop();
                gridView.visible = false;
            } else {
                timer.start();
                gridView.visible = true;
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
            source: controlButton.isStart ? "qrc:///images/play-button.png" : "qrc:///images/pause-button.png"
            fillMode: Image.Stretch
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }
    }

//    Button {
//        id: startButton
//        height: 25
//        width: 25
//        x: 130
//        y: 25
//        z: 20
//        ToolTip.visible: hovered
//        ToolTip.text: "Nastavi"
//        background: Rectangle {
//            color: "transparent"
//        }

//        onClicked: {
//            timer.start();
//            gridView.visible = true;
//        }

//        MouseArea {
//            anchors.fill: parent
//            cursorShape: Qt.PointingHandCursor
//            onClicked: startButton.clicked();
//        }

//        Image {
//            id : start
//            height: 25
//            width: 25
//            source: "qrc:///images/play-button.png"
//            fillMode: Image.Stretch
//            anchors {
//                horizontalCenter: parent.horizontalCenter
//                verticalCenter: parent.verticalCenter
//            }
//        }
//    }
}
