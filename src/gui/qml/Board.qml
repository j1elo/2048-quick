import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: root

    focus: true // Enable keyboard events
    Keys.onUpPressed: upPressed()
    Keys.onDownPressed: downPressed()
    Keys.onLeftPressed: leftPressed()
    Keys.onRightPressed: rightPressed()

    signal upPressed()
    signal downPressed()
    signal leftPressed()
    signal rightPressed()

    // Spacing and ItemSize values won't work if Size != 4
    property int gridSize: 4
    property real gridSpacing: width * 0.03
    property real gridItemSize: width * 0.2125
//    property int gridSize
//    property real gridSpacing
//    property real gridItemSize

    function addTile(index, value) {
        console.log("[Board.qml addTile]");
        console.log("width:", width, "height:", height);
        for (var i = 0; i < gridRepeater.count; i++) {
            console.log("Item", i, "x:", gridRepeater.itemAt(i).x, "y:", gridRepeater.itemAt(i).y);
        }

        console.log("[Board.qml] addTile", "index:", index, "value:", value);
        var component = Qt.createComponent("Tile.qml");
        if (component.status == Component.Ready) {
//            var tile = component.createObject(
//                gridContainer,
//                {
//                    "x": Qt.binding(function() { return gridRepeater.itemAt(index).x; }),
//                    "y": Qt.binding(function() { return gridRepeater.itemAt(index).y; }),
//                    "width": Qt.binding(function() { return gridItemSize; }),
//                    "height": Qt.binding(function() { return gridItemSize; }),
//                    "value": value
//                });
            var tile = component.createObject(
                null,
                {
                    "x": Qt.binding(function() { return gridRepeater.itemAt(index).x; }),
                    "y": Qt.binding(function() { return gridRepeater.itemAt(index).y; }),
                    "width": Qt.binding(function() { return gridItemSize; }),
                    "height": Qt.binding(function() { return gridItemSize; }),
                    "value": value
                });
//            var tile = component.createObject(
//                null,
//                {
//                    "x": gridRepeater.itemAt(index).x,
//                    "y": gridRepeater.itemAt(index).y,
//                    "width": gridItemSize,
//                    "height": gridItemSize,
//                    "value": value
//                });
            tile.parent = gridContainer;
            _tiles[index] = tile;
        }
    }

    function moveTile(fromIndex, toIndex) {
        console.log("[Board.qml] moveTile", "fromIndex:", fromIndex, "toIndex:", toIndex);
        var oldTile = _tiles[toIndex];
        if (oldTile) {
            oldTile.destroy(oldTile.speed);
            _tiles[toIndex] = null;
        }
        var tile = _tiles[fromIndex];
        tile.x = Qt.binding(function() { return gridRepeater.itemAt(toIndex).x; });
        tile.y = Qt.binding(function() { return gridRepeater.itemAt(toIndex).y; });
        _tiles[toIndex] = tile;
        _tiles[fromIndex] = null;
    }

    function setTile(index, value) {
        console.log("[Board.qml] setTile", "index:", index, "value:", value);
        var tile = _tiles[index];
        tile.value = value;
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
//            columns: gridSize
            spacing: gridSpacing

            Repeater {
                id: gridRepeater
                model: gridSize * gridSize

                // Delegate for each of the grid cells
//                Rectangle {
//                    width: gridItemSize; height: gridItemSize
//                    radius: 4
//                    color: Qt.rgba(238/255, 228/255, 218/255, 0.35)
//                }
                Tile {
                    width: gridItemSize; height: gridItemSize
                    //width: 100; height: 100
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("[Board.qml onCompleted]");
        console.log("width:", width, "height:", height);
        for (var i = 0; i < gridRepeater.count; i++) {
            console.log("Item", i, "x:", gridRepeater.itemAt(i).x, "y:", gridRepeater.itemAt(i).y);
        }
    }
}