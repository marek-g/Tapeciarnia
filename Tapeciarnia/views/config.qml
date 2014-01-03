import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: mainWindow
    width: 600
    height: 400

    Rectangle {
        anchors {
            left: parent.left; top: parent.top; bottom: parent.bottom; right: parent.right;
            margins: 10
        }

        Column {
            width: parent.width
            height: parent.height
            spacing: 20

            TableView {
                id: tableSources
                width: parent.width
                height: parent.height - 135

                TableViewColumn{ role: "Url"  ; title: qsTr("URL") ; width: 400 }
                TableViewColumn{ role: "Weight" ; title: qsTr("Weight") ; width: 50 }
                TableViewColumn{ role: "Description"  ; title: qsTr("Description") ; width: 500 }

                model: dataContext.Sources
            }

            Row {
                width: parent.width
                height: 25

                Button {
                    width: parent.width / 3
                    text: qsTr("New")
                    onClicked: {
                        var component = Qt.createComponent("add_new_dialog.qml");
                        if (component.status == Component.Error) {
                            console.debug("Error:"+ component.errorString() );
                            return;
                        }
                        component.createObject(mainWindow,
                                               {
                                                   dataContext: dataContext
                                               });
                    }
                }

                Button {
                    width: parent.width / 3
                    text: qsTr("Edit")
                    onClicked: {
                        var component = Qt.createComponent("edit_source_dialog.qml");
                        if (component.status == Component.Error) {
                            console.debug("Error:"+ component.errorString() );
                            return;
                        }
                        component.createObject(mainWindow,
                                               {
                                                   dataContext: dataContext,
                                                   index: tableSources.currentRow
                                               });
                    }
                }

                Button {
                    width: parent.width / 3
                    text: qsTr("Delete")
                    onClicked: {
                        var component = Qt.createComponent("confirm_delete_dialog.qml");
                        if (component.status == Component.Error) {
                            console.debug("Error:"+ component.errorString() );
                            return;
                        }
                        component.createObject(mainWindow,
                                               {
                                                   dataContext: dataContext,
                                                   index: tableSources.currentRow
                                               });
                    }
                }
            }

            Row {
                height: 25
                spacing: 15

                Text {
                    text: qsTr("Change wallpaper every:")
                }

                TextField {
                    id: changeEveryMinutesTextField
                    width: 80
                    text: dataContext.ChangeEveryMinutes
                    validator: IntValidator {}
                    onTextChanged: dataContext.ChangeEveryMinutes = text
                }

                Text {
                    text: qsTr("minutes")
                }
            }

            Row {
                height: 25
                spacing: 15
                anchors.right: parent.right;

                Button {
                    text: qsTr("Save")
                    onClicked: {
                        dataContext.acceptSettings();
                    }
                }

                Button {
                    text: qsTr("Cancel")
                    onClicked: {
                        dataContext.cancelSettings();
                    }
                }
            }
        }
    }
}
