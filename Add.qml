import QtQuick 2.15
import QtQuick.Controls 2.5
Page {
    background: Rectangle {
        color: "gray"
    }
    signal refresh()
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
                        text: "Create a new list"
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
                                stackView.pop("Add.qml")
                            }
                           cursorShape: Qt.PointingHandCursor

                        }
                    }
                }
    }
    Label {
        id: label
        anchors { top: header.bottom ; topMargin: 30 ; left: parent.left ; leftMargin: 30}
        text: "Name your new list:"
        color:"white"
        font.pixelSize: 15
    }
    Rectangle {
        id: input
        anchors { top: label.bottom ; topMargin: 5 ; left: parent.left ; leftMargin: 30}
        height: 50
        width: parent.width*0.8
        color: "white"
        radius: 8
        border.color: "dimgray"
        border.width: 2
        TextInput{
            id:name
            width: parent.width*0.9
            anchors.centerIn: parent
            focus:true
            font.pixelSize: 18
        }
    }
    Button {
        anchors { top: input.bottom ; topMargin: 10 ; left: parent.left ; leftMargin: 30}
        background: Rectangle {
            color: "orange"
            border.color: "dimgray"
            radius: 8
        }
        Text {
            text: "Create"
            font.pixelSize: 15
            color: "white"
            anchors.centerIn: parent
        }
        height: 40
        width: 100
        onClicked: {
            dbManager.addList(name.text,"")
            refresh()
            stackView.pop()

        }
    }

}
