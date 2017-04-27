import QtQuick 2.7

/*
 * The Switchslide in where we setup the switch
 * for interacting with the player
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
Rectangle {
    color: "grey"
    width: 130; height: 60
    radius: 25
    property alias on: s.on
    property alias onText: isOn

    //### LOAD ANDROID FONT
    FontLoader { id: fixedFont; name: "Roboto light" }
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto-Light.ttf" }

    Switch {
        id: s
        anchors.centerIn: parent
        on: false
    }
    Text {
        id: isOn
        text: s.on ? qsTr("On") : qsTr("Off")
        anchors.top: s.bottom
        font.family: "Roboto light"
        anchors.horizontalCenter: parent.horizontalCenter
        color: s.on ? "green" : "red"
        font.pointSize: 12
    }
}
