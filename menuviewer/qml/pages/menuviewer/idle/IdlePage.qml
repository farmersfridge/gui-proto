import QtQuick 2.5
import Common 1.0
import "../.."

Rectangle {
    color: _colors.ffColor2
    signal idlePageClicked()

    // Define behavior on opacity:
    visible: opacity > 0
    opacity: 1
    Behavior on opacity {
        NumberAnimation {duration: 500}
    }

    // Main timer:
    Timer {
        id: timer
        interval: _settings.idlePageTimeOut
        repeat: true
        running: true
        onTriggered: idleView.currentIndex++
    }

    // Path view:
    PathView {
        id: idleView
        pathItemCount: 2
        model: _controller.saladAssets
        anchors.fill: parent
        highlightRangeMode: PathView.StrictlyEnforceRange
        snapMode: ListView.SnapOneItem
        interactive: false

        // Path:
        path: Path {
            startX: -idleView.width/2; startY: idleView.height/2
            PathLine {x: idleView.width + idleView.width/2; y: idleView.height/2 }
        }

        delegate: Item {
            width: idleView.width
            height: idleView.height
            Image {
                cache: true
                width: parent.width/2
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                source: _controller.saladAssets[index]
            }
        }
    }

    // Touch screen to start text:
    StandardText {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        color: _colors.ffColor3
        text: qsTr("Touch Screen To Start")
    }

    // Clicking anywhere loads previous page:
    MouseArea {
        anchors.fill: parent
        onClicked: idlePageClicked()
    }
}