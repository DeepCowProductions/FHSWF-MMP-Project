import QtQuick 2.7

Rectangle {
    color: "grey"
    width: 130; height: 60
    radius: 25

    Switch {
        id: s
        anchors.centerIn: parent
        on: true
    }
    Text {
        id: isOn
        text: s.musicOn ? qsTr("On") : qsTr("Off")
        anchors.top: s.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: s.musicOn ? "green" : "red"
        font.pointSize: 12
    }
}
