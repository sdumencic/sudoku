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
                    x: 5
                    width: 55
                    height: 55
                    font.bold: true
                    font.pixelSize: 20
                    padding: 13
                    topPadding: 15

                    // ListCells - vrijednost svih celija
                    text: grid.cells[index]

                    // listCellTypes - tipovi celija
                    readOnly: grid.type[index]

                    // Boja brojeva - crno ako su zadani, plavo ako ih je igrac upisao
                    color: grid.type[index] ? (theme.isLight ? "#000000" : "#999999") : "#4a90e2"

                    // Validacija inputa
                    maximumLength: 1
                    validator: RegularExpressionValidator { regularExpression: /[1-9]/ }

                    anchors {
                        verticalCenter: parent.verticalCenter
                        horizontalCenter: parent.horizontalCenter
                        horizontalCenterOffset: 8
                    }

                    // Mijenjanje boje na focus
                    onFocusChanged: {
                        grid.updateListColors(index, focus)
                        grid.changeIsLight(theme.isLight)
                    }

                    // Unos brojeva
                    Keys.onPressed: {
                        switch (event.key) {
                        case Qt.Key_1:
                            grid.updateListCells(index, 1)
                            break;
                        case Qt.Key_2:
                            grid.updateListCells(index, 2)
                            break;
                        case Qt.Key_3:
                            grid.updateListCells(index, 3)
                            break;
                        case Qt.Key_4:
                            grid.updateListCells(index, 4)
                            break;
                        case Qt.Key_5:
                            grid.updateListCells(index, 5)
                            break;
                        case Qt.Key_6:
                            grid.updateListCells(index, 6)
                            break;
                        case Qt.Key_7:
                            grid.updateListCells(index, 7)
                            break;
                        case Qt.Key_8:
                            grid.updateListCells(index, 8)
                            break;
                        case Qt.Key_9:
                            grid.updateListCells(index, 9)
                            break;
                        case Qt.Key_Delete:
                            grid.updateListCells(index, 0)
                            break;
                        case Qt.Key_Backspace:
                            grid.updateListCells(index, 0)
                            break;
                        default :
                            grid.updateListCells(index, 0)
                        }

                        // Provjera ako je grid ispravno ispunjen
                        grid.check(false)
                        grid.changeIsLight(theme.isLight)
                    }
                }
            }
        }
    }    
}
