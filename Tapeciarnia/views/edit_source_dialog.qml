import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Item {
    id: dialogComponent
    anchors.fill: parent

    property variant dataContext
    property int index

    // Add a simple animation to fade in the popup
    // let the opacity go from 0 to 1 in 400ms
    PropertyAnimation { target: dialogComponent; property: "opacity";
                                  duration: 400; from: 0; to: 1;
                                  easing.type: Easing.InOutQuad ; running: true }

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
        width: 500
        height: 200
        anchors.centerIn: parent

        Column {
            width: 450
            spacing: 6
            anchors.centerIn: parent

            Row {
                Text {
                    width: 100
                    text: "URL:"
                }

                TextField {
                    id: url
                    width: 350
                    text: dataContext.Sources[index].Url
                }
            }

            Row {
                Text {
                    width: 100
                    text: "Weight:"
                }

                TextField {
                    id: weight
                    width: 350
                    text:  dataContext.Sources[index].Weight
                    validator: IntValidator {}
                }
            }

            Row {
                Text {
                    width: 100
                    text: "Description:"
                }

                TextField {
                    id: description
                    width: 350
                    text:  dataContext.Sources[index].Description
                }
            }

            Rectangle { width: 1; height: 30 }

            Row {
                Rectangle { width: 100; height: 1 }

                Button {
                    text: "OK"
                    onClicked: {
                        dataContext.Sources[index].Url = url.text
                        dataContext.Sources[index].Weight = parseInt(weight.text)
                        dataContext.Sources[index].Description = description.text

                        // destroy object is needed when you dynamically create it
                        dialogComponent.destroy()
                    }
                }

                Rectangle { width: 100; height: 1 }

                Button {
                    text: "Cancel"
                    onClicked: {
                        // destroy object is needed when you dynamically create it
                        dialogComponent.destroy()
                    }
                }
            }
        }
    }
}
