import QtQuick 2.15
import QtQuick.Controls 2.5

Page {
    background: Rectangle {
        color: "gray"
    }
    id: page
    property bool visibility : false
    property int listid
    property string ime
    property string des
    property int starty
    signal refresh()
    onRefresh: {
        taskModel.updateModel();
        taskModel2.updateModel2();
    }
    Item {
        z:2
        id: header
        width: parent.width
        height: 100
        Rectangle {
            color: "orange"
            anchors.centerIn: parent
            radius: 40
            width: parent.width * 0.8
            height: parent.height * 0.8
            Text {
                anchors { left: parent.left ; leftMargin: 50 ; verticalCenter: parent.verticalCenter }
                text: ime
                color: "white"
                font.pixelSize: 30
            }
            Rectangle {
                width: 3
                height: 60
                color: "white"
                anchors { right: add.left ; rightMargin: 30 ; verticalCenter: parent.verticalCenter }
                radius: 5
            }
            Image {
                id: add
                anchors { right: parent.right ; rightMargin: 50 ; verticalCenter: parent.verticalCenter }
                width: 35
                height: 35
                source: "qrc:/Assets/back.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop()
                    }
                    cursorShape: Qt.PointingHandCursor
                }
            }
        }
    }

    Rectangle {
        id: toolbar
        color: "dimgray"
        anchors { left: parent.left ; top: header.bottom }
        width: parent.width
        height: 50
        Image {
            id: first
            anchors { left: parent.left ; leftMargin: 20; verticalCenter: parent.verticalCenter }
            source: "qrc:/Assets/edit.svg"
            width: 35
            height: 35
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    stackView.push("Edit.qml",{id : listid})
                }
                cursorShape: Qt.PointingHandCursor
            }
        }
        Image {
            anchors { left: first.right ; leftMargin: 20; verticalCenter: parent.verticalCenter }
            source: "qrc:/Assets/move.png"
            width: 35
            height: 35
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    page.visibility = !page.visibility
                }
                cursorShape: Qt.PointingHandCursor
            }
        }
    }

    Text {
        id: description
        z:2
        anchors { top: toolbar.bottom ; topMargin: 10 ; horizontalCenter: parent.horizontalCenter }
        width: parent.width * 0.8
        text: des
        color: "white"
        font.pixelSize: 13
        font.italic: true
        wrapMode: Text.Wrap
    }

    /*Rectangle {
        color: "transparent"
        id: listrec
        anchors { top: description.bottom ; topMargin: 30 ; left: parent.left ; leftMargin: 30 }
        height: 250
        width: parent.width*/
        ListView {
            anchors { top: description.bottom ; topMargin: 30 ; left: parent.left ; leftMargin: 30 }
            height: 300
            width: parent.width
            //width: parent.width
            id: listavnatre
            model: taskModel
            delegate: entryvnatre
            spacing: 5
            //anchors.fill: parent
            clip: true
            footer: Rectangle {
                id: part
                height: 150
                width: parent.width
                color: "transparent"
                Text {
                    id: addtask
                    text: "Add new task"
                    color: "white"
                    font.pixelSize: 13
                    font.italic: true
                    font.underline: true
                    MouseArea {
                        id: tuka
                        anchors.fill: parent
                        onClicked: {
                            addtask.visible = false
                            novtask.visible = true
                        }
                        cursorShape: Qt.PointingHandCursor
                    }
                }

                Item {
                    height: 100
                    width: parent.width
                    id: novtask
                    visible: false
                    Label {
                        id: label
                        text: "Enter the name"
                        color: "white"
                        font.pixelSize: 13
                        font.italic: true
                    }

                    Rectangle {
                        id: backgroundRect
                        width: 200
                        height: 40
                        radius: 10
                        border.color: "dimgray"
                        border.width: 2
                        anchors { top: label.bottom ; topMargin: 5 ; left: parent.left }
                        TextField {
                            id: field
                            anchors.fill: parent
                            anchors.margins: 5
                            focus: true
                            font.pixelSize: 13
                        }
                    }

                    Button {
                        id: yes
                        anchors { top: backgroundRect.bottom ; topMargin: 20 ; left: parent.left }
                        height: 30
                        width: 100
                        background: Rectangle {
                            color: "orange"
                            border.color: "dimgray"
                            radius: 8
                        }
                        Text {
                            text: "Add"
                            font.pixelSize: 15
                            color: "white"
                            anchors.centerIn: parent
                        }
                        enabled:{ if(field.text == "")
                                     return false
                                else
                                    return true

                        }
                        onClicked: {
                            dbManager.addTask(field.text, listid)
                            page.refresh()
                            addtask.visible = true
                            novtask.visible = false
                            field.text = ""
                        }
                    }

                    Text {
                        anchors { top: backgroundRect.bottom ; topMargin: 27 ; left: yes.right ; leftMargin: 35 }
                        text: "Close"
                        font.pixelSize: 13
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                addtask.visible = true
                                novtask.visible = false
                            }
                        }
                    }
                }
            }

        }
    //}

    Component {
        id: entryvnatre
        Item {
            width: listavnatre.width
            height: 50
            property int _index: index
            Row {
                 width: parent.width
                 height: 50
                 CheckBox {
                     id: control
                     anchors.verticalCenter: parent.verticalCenter
                     checked: model.finished
                     MouseArea {
                        anchors.fill : parent
                         onClicked: {
                             if(model.finished === 1){
                             dbManager.checkTask(model.id,false, page.listid)
                             }
                             else{
                             dbManager.checkTask(model.id,true, page.listid)
                            }
                             page.refresh()
                         }
                    }

                     indicator: Rectangle {
                         implicitWidth: 26
                        implicitHeight: 26
                         x: control.leftPadding
                         y: parent.height / 2 - height / 2
                         radius: 3
                         border.color: control.down ? "#17a81a" : "#21be2b"
                         Rectangle {
                             width: 14
                             height: 14
                             x: 6
                             y: 6
                             radius: 2
                            color: control.down ? "#17a81a" : "#21be2b"
                           visible: control.checked
                         }
                     }
                 }

                Text {
                    text: visibility ?model.name + '  <-' : model.name
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    font.pixelSize: 15
                    font.weight: Font.DemiBold
                }
             }
            MouseArea {
                id: dragArea
                enabled: visibility
                anchors.fill: parent
                cursorShape: visibility ? Qt.PointingHandCursor : Qt.ArrowCursor
                drag.target: parent
                drag.axis: Drag.YAxis
                drag.onActiveChanged: {
                    dropArea.enabled = !dropArea.enabled
                    parent.Drag.drop()

                }
                onPressed: {
                    starty = parent.y
                }
                onReleased: {
                    var gorna
                    var dolna
                    if (_index == (listavnatre.count-1)){
                        dolna = -parent.height/2+listavnatre.itemAtIndex(0).y

                        gorna = starty+parent.height/2
                    }else if(_index == 0){
                        dolna = -parent.height/2+starty

                         gorna = listavnatre.itemAtIndex(listavnatre.count-1).y+parent.height/2
                    }
                    else{
                        dolna = -parent.height/2+listavnatre.itemAtIndex(0).y

                        gorna = listavnatre.itemAtIndex(listavnatre.count-1).y+parent.height/2
                    }
                    console.log(dolna,gorna)
                    console.log(starty,parent.y)
                    if(parent.y<dolna || parent.y>gorna){
                        parent.y = starty
                    }
                    if(Math.abs(parent.y-starty)<parent.height/2){
                        parent.y = starty
                    }
                }

            }
            Drag.active: dragArea.drag.active
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2
            DropArea {
                id: dropArea
                anchors.fill: parent
                onDropped: {
                    if(drop.source._index !== _index){
                    console.log(drop.source._index,_index)
                    dbManager.replace(listid, drop.source._index, _index)
                    page.refresh()
                    }

                }
            }
        }
    }
    ListModel {
            id: taskModel
            Component.onCompleted: {
                updateModel()
            }
            function updateModel() {
                var tasks = dbManager.getAllUTasks(listid);
                taskModel.clear(); // Clear the existing model data
                for (var i = 0; i < tasks.length; i++) {
                    taskModel.append({
                        id: tasks[i].id,
                        name: tasks[i].name,
                        finished: tasks[i].finished
                    });
                }
            }
        }


    Connections {
        id: connections
        target: stackView
        function onCurrentItemChanged() {
            page.refresh()
            page.ime = dbManager.getList(page.listid)["name"]
            page.des = dbManager.getList(page.listid)["description"]
        }
    }
    Rectangle {
        color:"dimgray"
        anchors { top: listavnatre.bottom ; topMargin: 5 ; right: parent.right ; left: parent.left }
        height: 2
        id: linija
    }

    Label {
        text: "Finished Tasks"
        color: "white"
        font.pixelSize: 15
        anchors {top: linija.bottom ; topMargin: 5 ; left: parent.left ; leftMargin: 30}
        id: labela
    }

    /*Rectangle {
        color: "dimgray"
        id: listrec2
        anchors { top: labela.bottom ; topMargin: 10 ; left: parent.left ; leftMargin: 0 }
        height: 200
        width: parent.width*/
        ListView {
            anchors { top: labela.bottom ; topMargin: 10 ; left: parent.left ; leftMargin: 30 }
            height: 200
            width: parent.width
            id: listavnatre2
            model: taskModel2
            delegate: entryvnatre2
            spacing: 5
            //anchors.fill: parent
            clip: true
        }
    //}
    Component {
        id: entryvnatre2
        Item {
            width: listavnatre.width
            height: 50
            property int _index: index
            Row {
                 width: parent.width
                 height: 50
                 CheckBox {
                     id: control
                     anchors.verticalCenter: parent.verticalCenter
                     checked: model.finished
                     MouseArea {
                        anchors.fill : parent
                         onClicked: {
                             if(model.finished === 1){
                             dbManager.checkTask(model.id,false, page.listid)
                             }
                             else{
                             dbManager.checkTask(model.id,true, page.listid)
                            }
                             page.refresh()
                         }
                    }

                     indicator: Rectangle {
                         implicitWidth: 26
                        implicitHeight: 26
                         x: control.leftPadding
                         y: parent.height / 2 - height / 2
                         radius: 3
                         border.color: control.down ? "#17a81a" : "#21be2b"
                         Rectangle {
                             width: 14
                             height: 14
                             x: 6
                             y: 6
                             radius: 2
                            color: control.down ? "#17a81a" : "#21be2b"
                           visible: control.checked
                         }
                     }
                 }

                Text {
                    text: model.name
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    font.pixelSize: 15
                    font.weight: Font.DemiBold
                }
             }

        }
    }
    ListModel {
            id: taskModel2
            Component.onCompleted: {
                updateModel2()
            }
            function updateModel2() {
                var tasks = dbManager.getAllFTasks(listid);
                taskModel2.clear(); // Clear the existing model data
                for (var i = 0; i < tasks.length; i++) {
                    taskModel2.append({
                        id: tasks[i].id,
                        name: tasks[i].name,
                        finished: tasks[i].finished
                    });
                }
            }
        }


}
