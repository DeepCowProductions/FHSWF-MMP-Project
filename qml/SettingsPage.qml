import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    property alias backButton: backButton
    property alias musicOn: switchSlide.on
    property alias effectsOn: effectSlide.on

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
        anchors.bottomMargin: 40
        Text {
            id: musicText
            text: qsTr("Music: ")
            Layout.alignment: Qt.AlignCenter
            color: "red"
            font.pointSize: 24
            Switchslide{
                id: switchSlide
                anchors.left: musicText.right
                anchors.verticalCenter: musicText.verticalCenter
            }
        }
        Text {
            id: effectText
            text: qsTr("Effects: ")
            Layout.alignment: Qt.AlignCenter
            anchors.top: musicText.bottom
            anchors.topMargin: 50
            color: "red"
            font.pointSize: 24
            Switchslide{
                id: effectSlide
                on: true
                anchors.left: effectText.right
                anchors.verticalCenter: effectText.verticalCenter
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
