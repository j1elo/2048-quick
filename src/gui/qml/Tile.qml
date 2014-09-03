import QtQuick 2.2

Rectangle {
    id: root

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

    implicitWidth: 5; implicitHeight: 5
    radius: 3
    color: Qt.rgba(238/255, 228/255, 218/255, 0.35)
    // States will change the default background color


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

    FontLoader {
        id: tileFont
        source: "qrc:///fonts/ClearSans-Regular.ttf"
    }

    Text {
        id: label
        anchors.centerIn: parent
        color: "#f9f6f2" // States will change the default font color
        font.family: tileFont.name
        font.pixelSize: root.width * 0.40
        font.weight: Font.Bold
        text: value
        visible: value > 0
    }

    states: [
        State {
            name: "2"; when: value == 2
            PropertyChanges { target: root; color: "#eee4da" }
            PropertyChanges { target: label; color: "#776e65" }
        },
        State {
            name: "4"; when: value == 4
            PropertyChanges { target: root; color: "#ede0c8" }
            PropertyChanges { target: label; color: "#776e65" }
        },
        State {
            name: "8"; when: value == 8
            PropertyChanges { target: root; color: "#f2b179" }
        },
        State {
            name: "16"; when: value == 16
            PropertyChanges { target: root; color: "#f59563" }
        },
        State {
            name: "32"; when: value == 32
            PropertyChanges { target: root; color: "#f67c5f" }
        },
        State {
            name: "64"; when: value == 64
            PropertyChanges { target: root; color: "#f65e3b" }
        },
        State {
            name: "128"; when: value == 128
            PropertyChanges { target: root; color: "#edcf72" }
        },
        State {
            name: "256"; when: value == 256
            PropertyChanges { target: root; color: "#edcc61" }
        },
        State {
            name: "512"; when: value == 512
            PropertyChanges { target: root; color: "#edc850" }
        },
        State {
            name: "1024"; when: value == 1024
            PropertyChanges { target: root; color: "#edc53f" }
        },
        State {
            name: "2048"; when: value == 2048
            PropertyChanges { target: root; color: "#edc22e" }
        },
        State {
            name: "super"; when: value > 2048
            PropertyChanges { target: root; color: "#3c3a32" }
        }
    ]
}
