import QtQuick 2.15

Rectangle {
    id: savedPanel
    visible: false
    width: 500
    height: 170
    y: window.height / 2 - savedPanel.height / 2 - 30
    anchors {
        horizontalCenter: parent.horizontalCenter
    }

    opacity: 0.9
    color: "#009688"
    transformOrigin: Item.Center
    Text {
        id: saved
        height: 30
        width: 90

        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        text: "Igra je spremljena"
        color: 'white'
        font.pixelSize: 40
        font.family: "Arial"
    }
}
