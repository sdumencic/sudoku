import QtQuick 2.15

GridView {
    id: gridView
    width: 500
    height: 500
    opacity: 1
    cellHeight: 55
    cellWidth: 55
    anchors {
        horizontalCenter: parent.horizontalCenter
    }

    model: ListModel {
        Component.onCompleted: {
            for (var yy = 0; yy < 9; yy++) {
                for (var xx = 0; xx < 9; xx++) {
                    append({
                        name: 0,
                        xx: xx,
                        yy: yy
                    })
                }
            }
        }
    }

    delegate: Item {
        x: 5
        height: 50
        Column {
            id: column
            spacing: 0
            Rectangle {
                id : rect
                width: 55
                height: 55
                // ListColors - boje
                color: grid.colors[index]
                border.color: "#cacaca"
                border.width: 1
                TextInput {
                    id: textEdit
                    padding: 13
                    topPadding: 15
                    x: 5
                    font.bold: true
                    font.pixelSize: 20
                    width: 55
                    height: 55
                    // ListCases - vrijednost svih celija
                    text: grid.cases[index]
                    // listTypeCases - tipovi celija
                    readOnly: grid.type[index]
                    // Boja brojeva - crno ako su zadani, plavo ako ih je igrac upisao
                    color: grid.type[index] ? "#000" : "#4a90e2"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: 8
                    maximumLength: 1
                    // Validacija inputa
                    validator: RegularExpressionValidator { regularExpression: /[1-9]/ }
                    // Mijenjanje boje na focus
                    onFocusChanged: {
                        grid.upListColors(index, focus)
                    }

                    // Unos brojeva
                    Keys.onPressed: {
                        switch (event.key) {
                        case Qt.Key_1:
                            grid.upListCases(index, 1)
                            break;
                        case Qt.Key_2:
                            grid.upListCases(index, 2)
                            break;
                        case Qt.Key_3:
                            grid.upListCases(index, 3)
                            break;
                        case Qt.Key_4:
                            grid.upListCases(index, 4)
                            break;
                        case Qt.Key_5:
                            grid.upListCases(index, 5)
                            break;
                        case Qt.Key_6:
                            grid.upListCases(index, 6)
                            break;
                        case Qt.Key_7:
                            grid.upListCases(index, 7)
                            break;
                        case Qt.Key_8:
                            grid.upListCases(index, 8)
                            break;
                        case Qt.Key_9:
                            grid.upListCases(index, 9)
                            break;
                        case Qt.Key_Delete:
                            grid.upListCases(index, 0)
                            break;
                        case Qt.Key_Backspace:
                            grid.upListCases(index, 0)
                            break;
                        }

                        // Provjera ako je grid ispravno ispunjen
                        grid.check(false)
                    }
                }
            }
        }
    }    
}
