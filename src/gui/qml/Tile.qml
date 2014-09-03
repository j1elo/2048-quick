import QtQuick 2.2

Rectangle {
    id: root
    implicitWidth: 5; implicitHeight: 5
    radius: 4
    color: value > 0 ? "yellow" : Qt.rgba(238/255, 228/255, 218/255, 0.35)

    property int value: 0
    property int delay: 100 // Time in ms taken by behavior animations
    property bool addAnimated: false

    function move(posX, posY, newValue) {
        if (newValue > 0) {
            // Perform Move and Merge sequential animations
            mergeAnimationPos.x = posX;
            mergeAnimationPos.y = posY;
            mergeAnimationScript.value = newValue;
            mergeAnimation.restart();
        } else {
            // Just perform the Move animation
            moveAnimationPos.x = posX;
            moveAnimationPos.y = posY;
            moveAnimation.restart();
        }
    }

    // Add animation
    ScaleAnimator on scale {
        running: addAnimated
        from: 0.0; to: 1.0
        duration: delay
        easing.type: Easing.InOutQuad
    }

    // Move animation
    PathAnimation {
        id: moveAnimation
        running: false
        target: root
        duration: delay
        easing.type: Easing.InOutQuad
        path: Path {
            PathLine { id: moveAnimationPos }
        }
    }

    // Merge animation
    SequentialAnimation {
        id: mergeAnimation
        running: false
        PathAnimation {
            target: root
            duration: delay
            path: Path {
                PathLine { id: mergeAnimationPos }
            }
        }
        NumberAnimation {
            target: root
            duration: delay / 2.0
            properties: "scale"
            to: 1.2
        }
        ScriptAction {
            id: mergeAnimationScript
            property int value
            script: root.value = value
        }
        NumberAnimation {
            target: root
            duration: delay / 2.0
            properties: "scale"
            to: 1.0
        }
    }

    Text {
        anchors.centerIn: parent
        visible: value > 0
        text: value
        font.pixelSize: root.width * 0.40
    }
}
