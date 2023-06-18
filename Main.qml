import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import GameTimer 1.0

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

    UserDialog {
        id: usernamePopup
    }

    Rectangle{
        id : sudoku
        width: window.width
        height: window.height
        x : window.width / 2 - sudoku.width / 2
        visible : false
        color: theme.isLight ? "white" : "#3c3c3c"

        TimerControls {
            id: timerControls
        }

        GameTimer {
            id: timer
        }

        Text {
            id: timerText
            x: 20
            y: 20
            z: 10
            color: teal
            text: "00:00"
            font.pointSize: 20
        }

        Connections {
            target: timer
            function onTimeChanged(time) {
                timerText.text = time;
            }
        }

        ThemeSwitch {
            id: customSwitch
        }

        Image {
            id: themeImage
            x: customSwitch.x + customSwitch.width + 20
            y: 10
            z: 10
            source: "qrc:///images/sun.png"
            height: 50
            width: 50
            anchors {
                right: parent.right
                rightMargin: 20
            }
        }

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

        Row {
            id: row_buttons
            y: gridView.y+ gridView.height + 30
            width: 500
            height: 30
            spacing: 50
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            // Provjeri
            Rectangle {
                id : button1
                width: 130
                height: 55
                color: "#03A9F4"
                radius : 5
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        grid.check(true)
                    }

                    hoverEnabled: true
                    onEntered: {
                        button1.color = teal;
                        cursorShape = Qt.PointingHandCursor
                    }

                    onExited: {
                        button1.color = "#03A9F4";
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
                    color: 'white'
                    font.pixelSize: 20
                    font.family: "Arial"

                }
            }

            // Restart
            Rectangle {
                id : button2
                width: 130
                height: 55
                color: "#00BCD4"
                radius : 5
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        grid.initGrid_file_txt(grid.level)
                        timer.reset()
                    }

                    hoverEnabled: true
                    onEntered: {
                        button2.color = teal;
                        cursorShape = Qt.PointingHandCursor
                    }

                    onExited: {
                        button2.color = "#00BCD4";
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
                    color: 'white'
                    font.pixelSize: 20
                    font.family: "Arial"

                }
            }

            Save {
                id: save
            }
        }

        SavePanel {
            id: saved_pannel
        }

        IconButton {
            id: buttonHint
        }

        // Nazad
        Button {
            id: buttonBack
            x: row_buttons.x - buttonBack.width - 20
            y: row_buttons.y - 10
            z: 20
            height: 70
            width: 70

            background: Rectangle {
                radius: 100
                color: buttonBack.hovered ? "lightblue" : "transparent"

                Image {
                    id: hint
                    height: 50
                    width: 50
                    source: "qrc:///images/back.png"
                    fillMode: Image.PreserveAspectFit
                    anchors.centerIn: parent
                }
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    menu.visible = true
                    guest.visible = true
                    text1.visible = true
                    background.visible = true
                    sudoku.visible = false
                    timer.reset()
                    timer.stop()
                }
            }

            onClicked: {
                grid.help()
            }
        }

    }

    // Pozadina
    Image {
        id : background
        source: "qrc:///images/background.png"
        z: -1
    }

    // Naslov
    Text {
        id: text1
        y: 20
        width: 200
        text: "SUDOKU"
        color: "white"
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

    MainMenu {
        id: menu
    }
}
