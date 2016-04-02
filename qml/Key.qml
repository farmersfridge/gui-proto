import QtQuick 2.5

Item {
    id: root

    property alias mainLabel: mainLabelItem.text
    property alias iconSource: icon.source
    property int bounds: 2

    property alias mainFont: mainLabelItem.font
    property alias mainFontColor: mainLabelItem.color

    property color keyColor: "gray"
    property color keyPressedColor: "white"

    property alias radius: backgroundItem.radius

    signal clicked()
    signal released()

    Rectangle {
        id: backgroundItem
        anchors.fill: parent
        anchors.margins: root.bounds
        color: mouseArea.pressed ? keyPressedColor : keyColor

        Image {
            id: icon
            smooth: true
            anchors.fill: parent
            anchors.margins: 4
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: mainLabelItem
            smooth: true
            anchors.centerIn: parent
            width: parent.width
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
            visible: icon.source == ""
            opacity: root.enabled ? 1 : .25
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.clicked()
        onReleased: root.released()
    }
}
