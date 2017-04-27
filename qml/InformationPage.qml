import QtQuick 2.7
import QtQuick.Layouts 1.1

/*
 * A page in there we have all information of
 * the game, as like how many points the player
 * get for killing a enemy.
 * And also how to control(steering) the game
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
Item {
    property alias backButton: backButton

    //### LOAD ANDROID FONT
    FontLoader { id: fixedFont; name: "Roboto light" }
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto-Light.ttf" }

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
            columnLayout.anchors.horizontalCenter = infoPage.horizontalCenter;
            startGameText.anchors.horizontalCenter = columnLayout.horizontalCenter;
            pauseText.anchors.horizontalCenter = columnLayout.horizontalCenter;
            moveText.anchors.horizontalCenter = columnLayout.horizontalCenter;
            quitText.anchors.horizontalCenter = columnLayout.horizontalCenter;
            pointText.anchors.horizontalCenter = columnLayout.horizontalCenter;
            shootText.anchors.horizontalCenter = columnLayout.horizontalCenter;
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
            font.family: "Roboto light"
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
            font.family: "Roboto light"
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
            font.family: "Roboto light"
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
            font.family: "Roboto light"
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
            font.family: "Roboto light"
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
            font.family: "Roboto light"
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
