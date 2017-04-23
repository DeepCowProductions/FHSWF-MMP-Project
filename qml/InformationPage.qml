import QtQuick 2.7
import QtQuick.Layouts 1.1

Item {
    property alias backButton: backButton

    id: infoPage
    anchors.fill: parent
    width: 640
    height: 480

    function checkAndroid() {
        if(Qt.platform.os == "android") {
            columnLayout.anchors.left = parent.left;
            startGameText.anchors.left = columnLayout.left;
            pauseText.anchors.left = columnLayout.left;
            moveText.anchors.left = columnLayout.left;
            quitText.anchors.left = columnLayout.left;
            pointText.anchors.left = columnLayout.left;
            shootText.anchors.left = columnLayout.left;
            //pointBossText.anchors.left = columnLayout.left;
        }
        else {
            columnLayout.anchors.horizontalCenter = parent.horizontalCenter;
            startGameText.anchors.horizontalCenter = parent.horizontalCenter;
            pauseText.anchors.horizontalCenter = parent.horizontalCenter;
            moveText.anchors.horizontalCenter = parent.horizontalCenter;
            quitText.anchors.horizontalCenter = parent.horizontalCenter;
            pointText.anchors.horizontalCenter = parent.horizontalCenter;
            shootText.anchors.horizontalCenter = parent.horizontalCenter;
            //pointBossText.anchors.horizontalCenter = parent.horizontalCenter;
        }
    }

    Component.onCompleted: checkAndroid()

    Image {
        height: parent.height
        width: parent.width
        source: "qrc:/starfield"
    }
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        anchors.bottomMargin: 40
        Text {
            id: startGameText
            text: qsTr("Starting Game: ")
            color: "red"
            font.pointSize: 24
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
            CloseButton {
                enabled: false
                anchors.left: quitText.right
                anchors.verticalCenter: quitText.verticalCenter
            }
        }
        Text {
            id: moveText
            text: Qt.platform.os == "android" ? qsTr("Move by pressing: ") : qsTr("Moving the Player's Spaceship by pressing: LEFT/RIGHT or 'a'/'d'")
            color: "red"
            font.pointSize: 24
            MoveButton {
                enabled: false
                visible: Qt.platform.os == "android"
                anchors.left: moveText.right
                anchors.verticalCenter: moveText.verticalCenter
                text: "Direction"
            }
        }
        Text {
            id: shootText
            text: Qt.platform.os == "android" ? qsTr("Fire by pressing: ") : qsTr("Fire by pressing Spacebar")
            color: "red"
            font.pointSize: 24
            ShotButton {
                enabled: false
                visible: Qt.platform.os == "android"
                anchors.left: shootText.right
                anchors.verticalCenter: shootText.verticalCenter
            }
        }
        Text {
            id: pointText
            text: Qt.platform.os == "android" ? qsTr("Points for enemey: 10") : qsTr("Getting Points by shooting a enemy: 10 Points")
            color: "red"
            font.pointSize: 24
        }
        Text {
            id: pointBossText
            visible: false
            text: Qt.platform.os == "android" ? qsTr("Points for Boss: 100") : qsTr("Getting Points by shooting a Boss: 100 Points")
            color: "red"
            font.pointSize: 24
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
