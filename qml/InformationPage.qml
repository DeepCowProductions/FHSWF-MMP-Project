import QtQuick 2.7
import QtQuick.Layouts 1.1

Item {
    property alias backButton: backButton

    id: infoPage
    anchors.fill: parent
    width: 640
    height: 480

    Image {
        height: parent.height
        width: parent.width
        source: "qrc:/starfield"
    }
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Text {
            id: startGameText
            text: qsTr("Starting Game: ")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
            PlayButton {
                enabled: false
                anchors.left: startGameText.right
                anchors.verticalCenter: startGameText.verticalCenter
            }
        }
        Text {
            id: pauseText
            text: qsTr("Pause the Game: ")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
            PauseButton {
                enabled: false
                height: 65
                width: 65
                anchors.left: pauseText.right
                anchors.verticalCenter: pauseText.verticalCenter
            }
        }
        Text {
            id: moveText
            text: qsTr("Moving the Player's Spaceship by pressing: ")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
            MoveButton {
                enabled: false
                anchors.left: moveText.right
                anchors.verticalCenter: moveText.verticalCenter
                text: "Move Direction"
            }
        }
    }
    RowLayout {
        id: buttonRow
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        BackButton {
            id: backButton
            anchors.bottom: parent.bottom

        }
    }
}
