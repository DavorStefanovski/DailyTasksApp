import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
ApplicationWindow {
    width: 640
    height: 740
    visible: true
    title: qsTr("MyLists")
    StackView {
        id: stackView
        initialItem: "Lists.qml"
        anchors.fill: parent
    }



}


