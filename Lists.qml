import QtQuick 2.15
import QtQuick.Controls 2.5
Page {
    id: page
    anchors.fill : parent
    background: Rectangle {
        color: "gray"
    }

    ListView {
        id: list
        anchors.fill : parent
        model: dbManager.getAllULists()
        delegate: entry
        focus: true
        header: Rectangle {
            color: "gray"
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
                    text: "My Lists"
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
                    width: 30
                    height: 30
                    source: "qrc:/Assets/PngItem_679828.png"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            stackView.push("Add.qml")
                        }
                       cursorShape: Qt.PointingHandCursor

                    }
                }
            }

        }
        footer: Rectangle {
            gradient: Gradient {
                    GradientStop { position: 0.0; color: "gray" }
                    GradientStop { position: 1.0; color: "dimgray" }
                }
            width: parent.width
            height: 100
            Text {
                id: naslov
                height: parent.height
                width: 100
                anchors { left: parent.left ; leftMargin: 20 ; top: parent.top ; topMargin: 20}
                text: "Completed Lists: "
                font.pixelSize: 15
                color: "Orange"
            }

            ListView {
                id: newlist
                //model: dbManager.getAllFLists()
                model: finishedlists


                anchors { left: naslov.right ; leftMargin: 20 ; top: parent.top ; topMargin: 20 ; right: parent.right ; rightMargin: 20}
                orientation: ListView.Horizontal
                delegate: Item {
                    height: 30
                    width: 60
                    Text {
                        text: model.name + ", "
                        color: "white"
                        font.pixelSize: 15
                    }
                    MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        stackView.push("Details.qml", {listid : model.id, des : model.description, ime : model.name})
                    }
                    }

                }
            }
        }
        highlight: Rectangle {
            Rectangle {
                anchors {top: parent.top; topMargin: 0}
                width: parent.width
                height: 2
                color: "lightgray"
            }

            color:"gray"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "gray" }
                GradientStop { position: 1.0; color: "dimgray" }

            }

            width: parent.width
            height: 100
            //radius: 20
        }


    }

    Component {
        id: entry

        Item {
            id:podatoci
            property string _index: index
            focus:true
            width: parent.width
            height: 100
            //color: "gray"
            Row {
                width: parent.width
                height: 100
                Rectangle {
                    id: dot
                    anchors { left: parent.left ; leftMargin: 20 ; verticalCenter: parent.verticalCenter}
                    width: 20
                    height: parent.height*0.5
                    color:"lightgray"
                    Rectangle {
                        id: fill
                        anchors {bottom: parent.bottom ; bottomMargin: 2 ; horizontalCenter: parent.horizontalCenter}
                        width: 16
                        height: parent.height * 0.9 * (modelData["taskcount"]-modelData["unfinishedtaskcount"])/modelData["taskcount"]
                        color: "green"

                    }
                }
                Text {
                    anchors { left: dot.right ; leftMargin: 20 ; verticalCenter: parent.verticalCenter}
                    text: modelData["name"].toString()
                    color: "white"
                    font.pixelSize: 20
                }
                Text {
                    anchors { right: parent.right ; rightMargin: 20 ; verticalCenter: parent.verticalCenter}
                    text: modelData["unfinishedtaskcount"] + " Remaining tasks"
                    font.pixelSize: 12
                }

            }

            Rectangle {
                id: linija
                width: parent.width*0.95
                height: 2
                color: "black"
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
            MouseArea{
                id: dragArea
                hoverEnabled: true
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    stackView.push("Details.qml", {listid : modelData["id"], des : modelData["description"], ime : modelData["name"]})
                }


            }


        }

    }

    Component.onCompleted: list.forceActiveFocus()
    Connections {
        id: connections
        target: stackView
        onCurrentItemChanged: {
            list.model = dbManager.getAllULists()
            //newlist.model = dbManager.getAllFLists()
            finishedlists.updateModel()

        }
    }
    ListModel {
        id: finishedlists
        Component.onCompleted: updateModel()
        function updateModel() {
            var completedlists = dbManager.getAllFLists();
            finishedlists.clear(); // Clear the existing model data
            for (var i = 0; i < completedlists.length; i++) {
                finishedlists.append({
                                         id: completedlists[i].id,
                                         name: completedlists[i].name,
                                         description: completedlists[i].description
                                     });
            }
        }
    }

}
