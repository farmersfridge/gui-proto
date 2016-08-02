import QtQuick 2.5

Image {
    id: container
    property bool on: false
    source: "assets/ico-busy.png"
    visible: container.on
    NumberAnimation on rotation { running: container.on; from: 0; to: 360; loops: Animation.Infinite; duration: 1200 }
    z: _settings.zMax
}
