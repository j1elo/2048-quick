import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1

Window {
    id: root
    visible: true
    width: 360
    height: 360
    color: "lightgrey"
    title: qsTr("2048 Quick!");

    Rectangle {
        anchors.fill: parent

        ColumnLayout {
            id: columnLay
            anchors.fill: parent
            anchors.margins: 25
            spacing: 6

            Text { text: "Hello" }

            Board {
                id: board
                objectName: "BoardQML"
                Layout.preferredWidth: columnLay.width
                Layout.preferredHeight: columnLay.width
            }

            Text { text: "bye" }
        }
    }
}
