import QtQuick 2.15
import QtQuick.Controls 2.5

Page {
    background: Rectangle {
        color: "gray"
    }
    property int id
    property var obj
    Component.onCompleted: {
        obj = dbManager.getList(id)

    }



    Item {
                id: header
                width: parent.width
                height: 100
                Rectangle {
                    color: "orange"
                    anchors.centerIn: parent
                    radius: 40
                    width: parent.width*0.8
                    height:  parent.height*0.8
                    Text {
                        anchors { left: parent.left ; leftMargin: 50 ; verticalCenter: parent.verticalCenter}
                        text: obj["name"]
                        color: "white"
                        font.pixelSize: 30
                    }
                    Rectangle {
                        width: 3
                        height: 60
                        color: "white"
                        anchors { right: add.left ; rightMargin: 30 ; verticalCenter: parent.verticalCenter}
                        radius: 5
                    }
                    Image {
                        id: add
                        anchors { right: parent.right ; rightMargin: 50 ; verticalCenter: parent.verticalCenter}
                        width: 35
                        height: 35
                        source: "qrc:/Assets/back.png"
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                stackView.pop()
                            }
                           cursorShape: Qt.PointingHandCursor

                        }

                }
    }
    }

    // Title Input
    Label {
        id: titleLabel
        anchors { top: header.bottom; topMargin: 30; left: parent.left; leftMargin: 30 }
        text: "Enter the title"
        color: "white"
        font.pixelSize: 15
    }

    Rectangle {
        id: titleInput
        anchors { top: titleLabel.bottom; topMargin: 5; left: parent.left; leftMargin: 30 }
        height: 50
        width: parent.width * 0.8
        color: "white"
        radius: 8
        border.color: "dimgray"
        border.width: 2

        TextInput {
            id:titl
            width: parent.width * 0.9
            anchors.centerIn: parent
            text: obj["name"]
            font.pixelSize: 18
        }
    }
    Label {
        id: taskslabel
        anchors { top: titleInput.bottom; topMargin: 30; left: parent.left; leftMargin: 30 }
        text: "Enter the title"
        color: "white"
        font.pixelSize: 15
    }
    // Text Items Section
    ListView {
        id: textItemsContainer
        anchors { top: taskslabel.bottom; topMargin: 5; left: parent.left; leftMargin: 30 }
        width: parent.width * 0.8
        height: 200
        model: dbManager.getAllTasks(id)
        clip: true
        delegate:     Rectangle {
            id: task
            height: 50
            width: parent.width * 0.8
            color: "white"
            radius: 8
            border.color: "dimgray"
            border.width: 2
            property int taskid : modelData['id']
            TextInput {
                id:field
                width: parent.width * 0.9
                anchors.centerIn: parent
                text: modelData["name"]
                font.pixelSize: 18
            }
            Image {
                anchors {left: field.right; leftMargin: 30; verticalCenter: parent.verticalCenter}
                source: "qrc:/Assets/close.png"
                width: 60
                height: 60
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        dbManager.deleteTask(modelData["id"],id)
                        textItemsContainer.model = dbManager.getAllTasks(id)
                    }

                }
            }

        }
    }

    // Description Section
    Label {
        id: descriptionLabel
        anchors { top: textItemsContainer.bottom; topMargin: 30; left: parent.left; leftMargin: 30 }
        text: "Description:"
        color: "white"
        font.pixelSize: 15
    }

    Rectangle {
        id: descriptionInput
        anchors { top: descriptionLabel.bottom; topMargin: 5; left: parent.left; leftMargin: 30 }
        width: parent.width * 0.8
        height: 150
        color: "white"
        radius: 8
        border.color: "dimgray"
        border.width: 2

        TextArea {
            id:dscr
            anchors.fill: parent
            placeholderText: obj["description"]
            font.pixelSize: 18
            wrapMode: TextArea.Wrap
        }
    }

    // Buttons Section
    Row {
        id: buttonsRow
        anchors { top: descriptionInput.bottom; topMargin: 20; left: parent.left; leftMargin: 30 }
        spacing: 20

        Button {
            //text: "Save List"
            Text {
                color: "White"
                anchors.centerIn: parent
                text: "Save List"
                font.pixelSize: 13
            }
            background: Rectangle {
                color: "green"
                border.color: "dimgray"
                radius: 8
            }
            height: 40
            width: 100
            onClicked: {
                dbManager.editList(id,titl.text,dscr.text)
                for (var i = 0; i < textItemsContainer.count; i++) {
                            var taskDelegate = textItemsContainer.itemAtIndex(i)
                            dbManager.editTask(taskDelegate.taskid, taskDelegate.children[0].text)
                        }
                stackView.pop()
            }
        }

        Button {
            //text: "Delete List"
            Text {
                color: "White"
                anchors.centerIn: parent
                text: "Delete List"
                font.pixelSize: 13
            }

            background: Rectangle {
                color: "red"
                border.color: "dimgray"
                radius: 8
            }
            height: 40
            width: 100
            onClicked: {
                dbManager.deleteList(id)
                stackView.pop()
                stackView.pop()
            }
        }

        Button {
            //text: "Cancel"
            Text {
                color: "White"
                anchors.centerIn: parent
                text: "Cancel"
                font.pixelSize: 13
            }
            background: Rectangle {
                color: "gray"
                border.color: "dimgray"
                radius: 8
            }
            height: 40
            width: 100
            onClicked: {
                stackView.pop()
            }
        }
    }

}
