import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    property alias backButton: backButton

    id: settingsPage
    anchors.fill: parent
    width: 640
    height: 480



    Rectangle {
        id: rect
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Text {
            id: name
            text: qsTr("Hier ensteht eine Seite mit Einstellungen zum Spiel")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
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
}
