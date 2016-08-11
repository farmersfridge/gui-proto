import QtQuick 2.5

Item {
    id: kbdSettings

    // Keyboards dir:
    readonly property string keyboardsDir: "keyboards/"

    // Assets dir:
    readonly property string assetsDir: "assets/"

    // Source:
    readonly property string source: "keyboard_us.json"

    // Key size:
    readonly property int keyWidth: 105
    readonly property int keyHeight: 105

    // Bounds:
    readonly property int bounds: 3

    // Key color:
    readonly property color keyColor: _settings.ffBrown
    readonly property color keyPressedColor: _settings.ffGreen

    // Key label color:
    readonly property color keyLabelColor: "#F2F2F2"

    // Key label point size:
    readonly property int keyLabelPointSize: 28

    // Key label font weight:
    readonly property int keyLabelFontWeight: Font.Light

    // Row query:
    readonly property string rowQuery: "$.Keyboard.Row[*]"
}

