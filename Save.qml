import QtQuick 2.15

Rectangle {
    width: 130
    height: 55
    color: '#74e1e3'
    radius : 5

    Timer {
        id: timer
        function setTimeout(cb, delayTime) {
            timer.interval = delayTime;
            timer.repeat = false;
            timer.triggered.connect(cb);
            timer.triggered.connect(function release () {
                timer.triggered.disconnect(cb);
                timer.triggered.disconnect(release);
            });
            timer.start();
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled : true
        onClicked: {
            saved_pannel.visible = true
            grid.save()
            timer.setTimeout(function(){ saved_pannel.visible = false }, 1000);
        }

        onExited: {
            save.color = "#74e1e3";
        }

        onEntered: {
            save.color = teal;
            cursorShape = Qt.PointingHandCursor
        }
    }

    Text {
        id: saveText
        height: 30
        width: 90

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenterOffset: 0

        text: "Spremi"
        color: '#fff'
        font.pixelSize: 20
        font.family: "Arial"
    }
}
