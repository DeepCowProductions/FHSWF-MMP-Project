import QtQuick 2.0
import QtQuick.Layouts 1.1

/*
 * A page which is showing when the game starts
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
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

        ColumnLayout {
            id: buttonRow
            height: playButton.height * 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
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
        }}
