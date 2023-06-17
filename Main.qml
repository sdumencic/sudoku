import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.settings 1.0

Window {
    id: window
    width: 700
    height: 700
    visible : true
    property alias gridView: gridView
    title: "Sudoku"
    property string teal: "#009688";
    property string lightTeal: "#80CBC4";
    Material.accent: Material.Teal

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
            color: "#ffffff"

            Column {
                spacing: 20
                anchors.centerIn: parent

                TextField {
                    width: 220
                    id: usernameInput
                    placeholderText: "Unesi svoje ime"
                    font.pixelSize: 20
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        text: "U redu"
                        font.pixelSize: 20
                        width: 100
                        onClicked: {
                            var username = usernameInput.text.trim()
                            player.setName(username)

                            usernamePopup.close()
                        }
                    }

                    Button {
                        text: "Odustani"
                        font.pixelSize: 20
                        width: 100
                        onClicked: {
                            usernamePopup.close()
                        }
                    }
                }
            }
        }
    }

    Rectangle{
        id : rect_game
        width: window.width
        height: window.height
        x : window.width / 2 - rect_game.width / 2
        visible : false

        SudokuGrid {
            id: gridView
            y : 70
        }

        // Tirkizne horizontalne linije da se lakse raspoznaje izmedu sub-kvadrata
        Repeater {
            model: 4;
            ColorRow {
                x: gridView.x
                y: gridView.y + index * 3 * 55
            }
        }

        // Tirkizne okomite linije da se lakse raspoznaje izmedu sub-kvadrata
        Repeater {
            model: 4;
            ColorColumn {
                x: gridView.x + index * 3 * 55
                y: gridView.y
            }
        }

        // Check - Restart - Save
        Row {
            id: row_buttons
            y: gridView.y+ gridView.height + 30
            width: 500
            height: 30
            spacing: 50
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            // Check
            Rectangle {
                id : button1
                width: 130
                height: 55
                color: '#2ecc71'
                border.color: "#95a5a6"
                border.width: 2
                radius : 5
                MouseArea {
                    anchors.fill: parent
                    onClicked: { grid.check(true) }

                    hoverEnabled: true
                    onEntered: {
                        button1.color = teal;
                        cursorShape = Qt.PointingHandCursor
                    }

                    onExited: {
                        button1.color = "#2ecc71";
                    }
                }

                Text {
                    id: check
                    height: 30
                    width: 90

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenterOffset: 0

                    text: "Provjeri"
                    color: '#fff'
                    font.pixelSize: 20
                    font.family: "Arial"

                }
            }

            // Restart
            Rectangle {
                id : button2
                width: 130
                height: 55
                color: '#3498db'
                border.color: "#95a5a6"
                border.width: 2
                radius : 5
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        grid.initGrid_with_csv(grid.level)
                    }

                    hoverEnabled: true
                    onEntered: {
                        button2.color = teal;
                        cursorShape = Qt.PointingHandCursor
                    }

                    onExited: {
                        button2.color = "#3498db";
                    }
                }

                Text {
                    id: restart
                    height: 30
                    width: 90

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 0
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenterOffset: 0

                    text: "Restart"
                    color: '#fff'
                    font.pixelSize: 20
                    font.family: "Arial"

                }
            }

            Save {
                id: save
            }

        }

        Rectangle {
            id: saved_pannel
            visible: false
            width: 500
            height: 170
            y: window.height / 2 - saved_pannel.height / 2 - 30
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            opacity: 0.9
            color: "#2ecc71"
            transformOrigin: Item.Center
            Text {
                id: text_saved
                height: 30
                width: 90

                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenterOffset: 0

                text: "Igra je spremljena"
                color: '#fff'
                font.pixelSize: 40
                font.family: "Arial"
            }
        }
    }

    // Pozadina
    Image {
        id : background
        visible: true
        source: "qrc:///images/sudoku2.png"
        z: -1
    }

    // Naslov
    Text {
        id: text1
        y: 20
        width: 200
        text: "SUDOKU"
        color: "#fff"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        minimumPixelSize: 12
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    Player {
        id: guest
    }

    Column {
        id: menu
        spacing: 20
        x: window.width / 2 - menu.width / 2
        y: window.height / 2 - menu.height / 2

        CustomButton {
            id : button_menu1
            label: "Početnik"
            color: "#2ecc71"
            game: 1
            startingColor: "#2ecc71"
        }

        CustomButton {
            id : button_menu2
            label: "Lagano"
            color: "#1abc9c"
            game: 2
            startingColor: "#1abc9c"
        }

        CustomButton {
            id : button_menu3
            label: "Srednje"
            color: "#80CBC4"
            game: 3
            startingColor: "#80CBC4"
        }

        CustomButton {
            id : button_menu4
            label: "Napredno"
            color: "#ff9800"
            game: 4
            startingColor: "#ff9800"
        }

        CustomButton {
            id : button_menu5
            label: "Nastavi spremljeno"
            color: "#00BCD4"
            game: 5
            startingColor: "#00BCD4"
            visible : grid.show_save_btn ? true : false
        }
    }
}
