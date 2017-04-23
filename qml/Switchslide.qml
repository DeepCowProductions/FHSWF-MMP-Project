import QtQuick 2.7

Rectangle {
    color: "grey"
    width: 130; height: 60
    radius: 25
    property alias on: s.on
    property alias onText: isOn

    Switch {
        id: s
        anchors.centerIn: parent
        on: false
    }
    Text {
        id: isOn
        text: s.on ? qsTr("On") : qsTr("Off")
        anchors.top: s.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        color: s.on ? "green" : "red"
        font.pointSize: 12
    }
}
