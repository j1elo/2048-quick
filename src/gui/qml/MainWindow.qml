import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1

Window {
    id: root
    visible: true
    width: 480
    height: 640
    color: "lightgrey"
    title: qsTr("2048 Quick!")

    Board {
        id: board
        objectName: "BoardQML"
        anchors.fill: parent
    }
}
