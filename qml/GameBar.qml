import QtQuick 2.7

/*
 * A bar for the game, in which we have the points,
 * the life of the player and a pause button
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
Rectangle {
    id: gameBarRect
    height: parent.height * 0.05
    width: parent.width
    anchors.top: parent.top
    color: "#3067EAF9"

    //### LOAD ANDROID FONT
    FontLoader { id: fixedFont; name: "Roboto light" }
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto-Light.ttf" }

    //property alias powerUPSource: powerUPSource
    //property string powerUPSource
    property alias score: scoreText
    property alias firstLife: firstLife
    property alias secLife: secLife
    property alias thirdLife: thirdLife
    property alias pause: pauseButton

    Text {
        id: scoreText
        text: "ERROR"
        color: "red"
        font.family: "Roboto light"
        font.pixelSize: 20
        anchors.left: gameBarRect.left
        anchors.verticalCenter: gameBarRect.verticalCenter
        anchors.leftMargin: 10
    }

    Rectangle {
        id: middleRect
        visible: false
        x: parent.width * 0.5
        y: parent.height * 0.5
        width: parent.width * 0.05
        height: parent.width * 0.05
        radius: 20
        color: "#67EAF9"
        Image {
            //source: powerUPSource
        }
    }

    PauseButton {
        id: pauseButton
        anchors.right: firstLife.left
        anchors.top: gameBarRect.top
    }

    Image {
        id: thirdLife
        x: Qt.platform.os == "android" ? gameBarRect.width * 0.93 : gameBarRect.width * 0.97
        y: gameBarRect.height * 0.1
        width: gameBarRect.height
        height: gameBarRect.height * 0.8
        source: "qrc:/life"
    }
    Image {
        id: secLife
        x: Qt.platform.os == "android" ? gameBarRect.width * 0.87 : gameBarRect.width * 0.94
        y: gameBarRect.height * 0.1
        width: gameBarRect.height
        height: gameBarRect.height * 0.8
        source: "qrc:/life"
    }
    Image {
        id: firstLife
        visible: m_firstLife;
        x: Qt.platform.os == "android" ? gameBarRect.width * 0.81 : gameBarRect.width * 0.91
        y: gameBarRect.height * 0.1
        width: gameBarRect.height
        height: gameBarRect.height * 0.8
        source: "qrc:/life"
    }
}
