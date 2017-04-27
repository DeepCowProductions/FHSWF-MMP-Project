import QtQuick 2.7
import QtQuick.Layouts 1.1

/*
 * A Page in which the player can choose, after clicking on pause.
 * If he want start new game, go to main menu or quit the application
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
Item {
    property alias backButton: backButton
    property alias quitButton: quitButton
    property alias neustartButton: neustartButton
    property alias menuButton: menuButton
    property alias pauseSettingsButton: settingsButton

    id: infoPage
    anchors.fill: parent
    width: 640
    height: 480
    opacity: 0.85

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
            id: settingsButton
            text: qsTr("Settings")
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: parent.width * 0.3
            implicitHeight: parent.height * 0.1
        }
        Button {
            id: quitButton
            text: qsTr("Quit Game")
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
