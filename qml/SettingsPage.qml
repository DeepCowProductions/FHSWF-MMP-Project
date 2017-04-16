import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    property alias backButton: backButton

    id: settingsPage
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
            id: musicText
            text: qsTr("Musik: ")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "red"
            font.pointSize: 24
        }
        Switchslide{
            id: switchSlide
            anchors.left: musicText.right
            anchors.verticalCenter: parent.verticalCenter
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
