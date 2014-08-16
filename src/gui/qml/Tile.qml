import QtQuick 2.0

Rectangle {
    property int value: 0
    property int delay: 200 // Time in ms taken by behavior animations

    implicitWidth: 100; implicitHeight: 100
    radius: 4
    //visible: value > 0
    color: value > 0 ? "yellow" : Qt.rgba(238/255, 228/255, 218/255, 0.35)

    Text {
        anchors.centerIn: parent
        visible: value > 0
        text: value
        font.pixelSize: gridItemSize * 0.40
    }

    Behavior on x {
        NumberAnimation {
            duration: delay
            //This selects an easing curve to interpolate with, the default is Easing.Linear
            //easing.type: Easing.OutBounce
        }
    }

    Behavior on y {
        NumberAnimation {
            duration: delay
            //This selects an easing curve to interpolate with, the default is Easing.Linear
            //easing.type: Easing.OutBounce
        }
    }
}
