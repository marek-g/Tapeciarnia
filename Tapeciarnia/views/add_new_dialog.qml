import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Item {
    id: dialogComponent
    anchors.fill: parent

    property variant dataContext

    // Add a simple animation to fade in the popup
    // let the opacity go from 0 to 1 in 400ms
    PropertyAnimation { target: dialogComponent; property: "opacity";
                                  duration: 400; from: 0; to: 1;
                                  easing.type: Easing.InOutQuad ; running: true }

    Component.onCompleted: {
        url.forceActiveFocus()
    }

    // This rectange is the a overlay to partially show the parent through it
    // and clicking outside of the 'dialog' popup will do 'nothing'
    Rectangle {
        anchors.fill: parent
        id: overlay
        color: "#000000"
        opacity: 0.6
        // add a mouse area so that clicks outside
        // the dialog window will not do anything
        MouseArea {
            anchors.fill: parent
        }
    }

    // This rectangle is the actual popup
    Rectangle {
        id: dialogWindow
        width: parent.width - 100
        height: 200
        anchors.centerIn: parent

        Column {
            width: parent.width - 40
            spacing: 6
            anchors.centerIn: parent

            Row {
                width: parent.width

                Text {
                    width: 100
                    text: qsTr("Enabled:")
                }

                CheckBox {
                    id: enabled
                    width: parent.width - 106
                    checked: true
                }
            }

            Row {
                width: parent.width

                Text {
                    width: 100
                    text: qsTr("URL:")
                }

                TextField {
                    id: url
                    width: parent.width - 106
                }
            }

            Row {
                width: parent.width

                Text {
                    width: 100
                    text: qsTr("Weight:")
                }

                TextField {
                    id: weight
                    width: parent.width - 106
                    text: "10"
                    validator: IntValidator {}
                }
            }

            Row {
                width: parent.width

                Text {
                    width: 100
                    text: qsTr("Description:")
                }

                TextField {
                    id: description
                    width: parent.width - 106
                }
            }

            Rectangle { width: 1; height: 30 }

            Row {
                width: parent.width

                Rectangle { width: (parent.width - 300)/2; height: 1 }

                Button {
                    width: 100
                    text: qsTr("OK")
                    onClicked: {
                        dataContext.addNewSource(enabled.checked, url.text, parseInt(weight.text), description.text)

                        // destroy object is needed when you dynamically create it
                        dialogComponent.destroy()
                    }
                }

                Rectangle { width: 100; height: 1 }

                Button {
                    width: 100
                    text: qsTr("Cancel")
                    onClicked: {
                        // destroy object is needed when you dynamically create it
                        dialogComponent.destroy()
                    }
                }
            }
        }
    }
}
