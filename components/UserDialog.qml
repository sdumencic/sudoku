import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Popup {
    id: usernamePopup
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    anchors {
        centerIn: parent
    }

    width: 500
    height: 200
    background: Rectangle {
        radius: 8
    }

    contentItem: Rectangle {
        color: "white"

        Column {
            spacing: 20
            anchors.centerIn: parent

            TextField {
                width: 220
                id: usernameInput
                placeholderText: "Unesi svoje ime"
                font.pixelSize: 20
                validator: RegularExpressionValidator  { regularExpression: /^([a-zA-Z]{1,10})$/ }
            }

            Row {
                id: popupButtonRow
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: ok
                    text: "U redu"
                    font.pixelSize: 20
                    width: usernamePopup.width / 4
                    ToolTip.visible: hovered
                    ToolTip.text: "U redu"
                    onClicked: {
                        var username = usernameInput.text.trim()

                        if(username.length > 0){
                            player.setName(username)
                        }

                        usernamePopup.close()
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: ok.clicked();
                    }
                }

                Button {
                    id: cancel
                    text: "Odustani"
                    font.pixelSize: 20
                    width: usernamePopup.width / 4
                    ToolTip.visible: hovered
                    ToolTip.text: "Odustani"
                    onClicked: {
                        usernamePopup.close()
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: cancel.clicked();
                    }
                }
            }
        }
    }
}
