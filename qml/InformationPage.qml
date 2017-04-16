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
        anchors.bottomMargin: 40
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
            id: quitText
            text: qsTr("Close the Game: ")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
            CloseButton {
                enabled: false
                anchors.left: quitText.right
                anchors.verticalCenter: quitText.verticalCenter
            }
        }
        Text {
            id: moveText
            text: Qt.platform.os == "android" ? qsTr("Moving the Player's Spaceship by Pressing: ") : qsTr("Moving the Player's Spaceship by pressing: LEFT/RIGHT or 'a'/'d'")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
            MoveButton {
                enabled: false
                visible: Qt.platform.os == "android"
                anchors.left: moveText.right
                anchors.verticalCenter: moveText.verticalCenter
                text: "Move Direction"
            }
        }
        Text {
            id: shootText
            text: qsTr("Fire with Player's Spaceship by pressing: ")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
            ShotButton {
                enabled: false
                anchors.left: shootText.right
                anchors.verticalCenter: shootText.verticalCenter
            }
        }
        Text {
            id: pointText
            text: qsTr("Getting Points by shooting a enemy: 10 Points")
            color: "red"
            font.pointSize: 24
            anchors.horizontalCenter: columnLayout.horizontalCenter
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
