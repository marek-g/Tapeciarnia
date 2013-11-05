import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    width: 600
    height: 400

    Rectangle {
        anchors {
            left: parent.left; top: parent.top; bottom: parent.bottom; right: parent.right;
            margins: 10
        }

        Column {
            width: parent.width

            TableView {
                width: parent.width

                TableViewColumn{ role: "Url"  ; title: "URL" ; width: 400 }
                TableViewColumn{ role: "Weight" ; title: "Weight" ; width: 50 }
                TableViewColumn{ role: "Description"  ; title: "Description" ; width: 500 }

                model: dataContext.Sources

                itemDelegate: Item {
                    Text {
                        width: parent.width
                        anchors.margins: 4
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        elide: styleData.elideMode
                        text: styleData.value !== undefined ? styleData.value : ""
                        color: styleData.textColor
                        visible: !styleData.selected
                    }
                    Loader { // Initialize text editor lazily to improve performance
                        id: loaderEditor
                        anchors.fill: parent
                        anchors.margins: 4
                        Connections {
                            target: loaderEditor.item
                            onAccepted: {
                                if (typeof styleData.value === 'number')
                                    model.setProperty(styleData.row, styleData.role, Number(parseFloat(loaderEditor.item.text).toFixed(0)))
                                else
                                    model.setProperty(styleData.row, styleData.role, loaderEditor.item.text)
                            }
                        }
                        sourceComponent: styleData.selected ? editor : null
                        Component {
                            id: editor
                            TextInput {
                                id: textinput
                                color: styleData.textColor
                                text: styleData.value
                                MouseArea {
                                    id: mouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked: textinput.forceActiveFocus()
                                }
                            }
                        }
                    }
                }
            }

            ComboBox {
                width: parent.width
                model: [ "Banana", "Apple", "Coconut" ]
            }

        }
    }
}
