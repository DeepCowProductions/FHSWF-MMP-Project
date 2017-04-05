import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    property alias playButton: playButton
    property alias infoButton: infoButton
    property alias settingsButton: settingsButton

    id: startPage
    anchors.fill: parent
    width: 640
    height: 480
    Image {
        height: parent.height
        width: parent.width
        source: "qrc:/starfield"
    }

    Image {
        height: parent.height*0.5
        width: parent.width*0.5
        source: "qrc:/title"
        x: parent.width * 0.25
        y: parent.height * 0.001
    }

    Image {
        height: parent.height/3
        width: parent.width/2.5
        source: "qrc:/startship"
        x: parent.width * 0.6
        y: parent.height * 0.2
    }

    Column {
        id: outerColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        RowLayout {
            id: buttonRow
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            ColumnLayout {
                PlayButton {
                    id: playButton
                }
                InfoButton {
                    id: infoButton
                }
                SettingsButton {
                    id: settingsButton
                }
                CloseButton {
                    id: closeButton
                }
            }
        }}
}
