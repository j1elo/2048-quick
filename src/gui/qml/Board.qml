import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: root

    Keys.onUpPressed: { focus = false; upPressed() }
    Keys.onDownPressed: { focus = false; downPressed() }
    Keys.onLeftPressed: { focus = false; leftPressed() }
    Keys.onRightPressed: { focus = false; rightPressed() }

    onFocusChanged: keysTimer.start()
    Timer {
        // This timer avoids overlapping key inputs
        // (ie. a key input when the animation of the previous one didn't finish yet)
        id: keysTimer; interval: 200; running: true
        // FIXME: this should be Tile.delay * 2.0
        onTriggered: root.focus = true // Enable keyboard events
    }

    signal upPressed()
    signal downPressed()
    signal leftPressed()
    signal rightPressed()

    // Spacing and ItemSize values won't work if Size != 4
    property int gridSize: 4
    property real gridSpacing: width * 0.03
    property real gridItemSize: width * 0.2125

    function addTile(index, value) {
//        console.log("width:", width, "height:", height);
//        for (var i = 0; i < gridRepeater.count; i++) {
//            print("Item", i, "x:", gridRepeater.itemAt(i).x, "y:", gridRepeater.itemAt(i).y);
//        }

        print("[Board.qml addTile]", "index:", index, "value:", value);
        var component = Qt.createComponent("Tile.qml");
        if (component.status === Component.Ready) {
            var tile = component.createObject(
                null,
                {
                    "x": gridRepeater.itemAt(index).x,
                    "y": gridRepeater.itemAt(index).y,
                    "width": gridItemSize,
                    "height": gridItemSize,
                    "value": value,
                    "addAnimated": true
                });
            tile.parent = gridContainer;
            _tiles[index] = tile;
        }
    }

    function moveTile(fromIndex, toIndex, newValue) {
        console.log("[Board.qml] moveTile", "fromIndex:", fromIndex, "toIndex:", toIndex, "newValue:", newValue);
        var merging = (newValue > 0);
        var oldTile = _tiles[toIndex];
        if (oldTile) {
            if (!merging) {
                console.log("ERROR: Destination tile should be empty. This is a bug!!")
            } else {
                oldTile.destroy(oldTile.delay);
                _tiles[toIndex] = null;
            }
        }
        var tile = _tiles[fromIndex];
//        tile.x = Qt.binding(function() { return gridRepeater.itemAt(toIndex).x; });
//        tile.y = Qt.binding(function() { return gridRepeater.itemAt(toIndex).y; });
        tile.move(gridRepeater.itemAt(toIndex).x, gridRepeater.itemAt(toIndex).y, newValue);
        _tiles[toIndex] = tile;
        _tiles[fromIndex] = null;
    }

    // Private:
    property var _tiles: new Array(gridSize * gridSize)

    radius: 8
    color: "#bbada0"
    border.color: "red"

    Rectangle {
        id: gridContainer
        anchors {
            fill: parent
            margins: gridSpacing
        }
        color: "transparent"
        border.color: "blue"

        // Main game grid
        Grid {
            id: grid
            anchors.fill: parent
            spacing: gridSpacing

            Repeater {
                id: gridRepeater
                model: gridSize * gridSize
                Tile {
                    width: gridItemSize; height: gridItemSize
                }
            }
        }
    }

//    Component.onCompleted: {
//        console.log("[Board.qml onCompleted]");
//        console.log("width:", width, "height:", height);
//        for (var i = 0; i < gridRepeater.count; i++) {
//            console.log("Item", i, "x:", gridRepeater.itemAt(i).x, "y:", gridRepeater.itemAt(i).y);
//        }
//    }
}
