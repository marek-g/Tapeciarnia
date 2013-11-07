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
            spacing: 30
            anchors.centerIn: parent

            Text {
                text: "Do you really want to delete this address?\n" + dataContext.Sources[index].Url
            }

            Row {
                Rectangle { width: 100; height: 1 }

                Button {
                    text: "Yes"
                    onClicked: {
                        dataContext.deleteSource(index)

                        // destroy object is needed when you dynamically create it
                        dialogComponent.destroy()
                    }
                }

                Rectangle { width: 100; height: 1 }

                Button {
                    text: "No"
                    onClicked: {
                        // destroy object is needed when you dynamically create it
                        dialogComponent.destroy()
                    }
                }
            }
        }
    }
}
