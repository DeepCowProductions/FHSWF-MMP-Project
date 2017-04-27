import QtQuick 2.7
import QtQuick.Layouts 1.1

/*
 * A Page which is show, when the player
 * has loose the game.
 * On this page the player can decide, if he want to
 * quit the application, start a new game or go back
 * to the main menu
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
Item {
    property alias quitButton: quitButton
    property alias neustartButton: neustartButton
    property alias menuButton: menuButton
    property alias endPointsText: endPointsText.text

    //### LOAD ANDROID FONT
    FontLoader { id: fixedFont; name: "Roboto light" }
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto-Light.ttf" }

    id: gameOverPage
    anchors.fill: parent
    width: 640
    height: 480

    Image {
        height: parent.height
        width: parent.width
        source: "qrc:/starfield"
        opacity: 0.85
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        anchors.bottomMargin: 40
        Text {
            id: endPointsText
            text: qsTr("Endscore: ")
            font.pointSize: 24
            color: "red"
            font.family: "Roboto light"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: neustartButton
            text: qsTr("New Game")
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: parent.width * 0.3
            implicitHeight: parent.height * 0.1
        }
        Button {
            id: menuButton
            text: qsTr("Menu")
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: parent.width * 0.3
            implicitHeight: parent.height * 0.1
        }
        Button {
            id: quitButton
            text: qsTr("Quit")
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: parent.width * 0.3
            implicitHeight: parent.height * 0.1
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    Qt.quit();
                }
            }
        }
    }
}
