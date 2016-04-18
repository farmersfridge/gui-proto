import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0
import ".."
import "../script/Utils.js" as Utils

CustomPage {
    id: stockPagePrivate
    pageId: "_stockpageprivate_"
    idleTime: 0

    // Stop:
    function onStop()
    {
        if (xmlVersionModel)
            xmlVersionModel.source = ""
    }

    // XML version model:
    CustomXmlListModel {
        id: xmlVersionModel
        query: "/versionStatus/item"
        source: Utils.urlPlay(_controller.currentNetworkIP, "/config/versionStatus")

        XmlRole { name: "versionModel"; query: "version/string()"; isKey: true }
        XmlRole { name: "statusModel"; query: "status/string()"; isKey: true }
    }

    // XML row model:
    CustomXmlListModel {
        id: xmlRowModel
        query: "/restock/row"
        source: Utils.urlPlay(_controller.currentNetworkIP, "/config/restocks")

        XmlRole { name: "rowNumber"; query: "@rowId/string()"; isKey: true }
    }

    // Top bar:
    topBar: Item {
        anchors.fill: parent
        RowLayout {
            Layout.preferredWidth: body.width
            spacing: body.width/10
            height: parent.height
            anchors.centerIn: parent
            StyledButton {
                id: stock
                text: qsTr("STOCK")
                onClicked: _restockFromTabletCommand.execute()
            }
            StyledButton {
                id: clearAll
                text: qsTr("CLEAR ALL")
                onClicked: _clearAllCommand.execute()
            }
            StyledButton {
                id: back
                text: qsTr("BACK")
                onClicked: mainApplication.loadPreviousPage()
            }
            StyledButton {
                id: note
                text: qsTr("NOTE")

                // Keyboard enter key clicked:
                function onKeyboardEnterKeyClicked()
                {
                    console.log("ENTER KEY CLICKED FOR NOTEPAD")
                    mainApplication.hideNodePad()

                    mainApplication.keyBoardEnterKeyClicked.disconnect(onKeyboardEnterKeyClicked)
                    mainApplication.keyBoardCancelKeyClicked.disconnect(onKeyboardCancelKeyClicked)
                }

                // Keyboard cancel key clicked:
                function onKeyboardCancelKeyClicked()
                {
                    console.log("CANCEL KEY CLICKED FOR NOTEPAD")
                    mainApplication.hideNotePad()

                    mainApplication.keyBoardEnterKeyClicked.disconnect(onKeyboardEnterKeyClicked)
                    mainApplication.keyBoardCancelKeyClicked.disconnect(onKeyboardCancelKeyClicked)
                }

                onClicked: {
                    mainApplication.keyBoardEnterKeyClicked.connect(onKeyboardEnterKeyClicked)
                    mainApplication.keyBoardCancelKeyClicked.connect(onKeyboardCancelKeyClicked)
                    mainApplication.showNotePad()
                }
            }
        }
    }

    // Body:
    contents: Item {
        id: body
        height: parent.height
        width: parent.width-32
        anchors.centerIn: parent

        // Stock page grid:
        StockPageGrid {
            Layout.preferredWidth: body.width
            Layout.preferredHeight: body.height * .90
            Layout.alignment: Qt.AlignTop
        }
    }

    // Stock page footer block:
    bottomBar: Item {
        anchors.fill: parent
        StockPageHeaderBlock {
            id: header
            Layout.preferredWidth: body.width
            height: parent.height
            anchors.centerIn: parent
        }
    }
}