import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: mainWindow
    width: 600
    height: 270

    Rectangle {
        anchors {
            left: parent.left; top: parent.top; bottom: parent.bottom; right: parent.right;
            margins: 10
        }

        Column {
            width: parent.width
            spacing: 20

            TableView {
                id: tableSources
                width: parent.width

                TableViewColumn{ role: "Url"  ; title: "URL" ; width: 400 }
                TableViewColumn{ role: "Weight" ; title: "Weight" ; width: 50 }
                TableViewColumn{ role: "Description"  ; title: "Description" ; width: 500 }

                model: dataContext.Sources
            }

            Row {
                width: parent.width

                Button {
                    text: "New"
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
                    text: "Edit"
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
                    text: "Delete"
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
                spacing: 15

                Text {
                    text: "Change wallpaper every:"
                }

                TextField {
                    id: changeEveryMinutesTextField
                    text: dataContext.ChangeEveryMinutes
                    validator: IntValidator {}
                    onTextChanged: dataContext.ChangeEveryMinutes = text
                }

                Text {
                    text: "minutes"
                }
            }
        }
    }
}
