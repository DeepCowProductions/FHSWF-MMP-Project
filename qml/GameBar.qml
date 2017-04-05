import QtQuick 2.7

Rectangle {
    id: gameBarRect
    height: parent.height * 0.05
    width: parent.width
    anchors.top: parent.top
    color: "#3067EAF9"

    //property alias powerUPSource: powerUPSource
    //property string powerUPSource
    property alias score: scoreText
    property alias firstLife: firstLife
    property alias secLife: secLife
    property alias thirdLife: thirdLife

    Text {
        id: scoreText
        text: "ERROR"
        color: "red"
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
        x: gameBarRect.width * 0.97
        y: gameBarRect.height * 0.1
        width: gameBarRect.height
        height: gameBarRect.height * 0.8
        source: "qrc:/life"
    }
    Image {
        id: secLife
        x: gameBarRect.width * 0.94
        y: gameBarRect.height * 0.1
        width: gameBarRect.height
        height: gameBarRect.height * 0.8
        source: "qrc:/life"
    }
    Image {
        id: firstLife
        visible: m_firstLife;
        x: gameBarRect.width * 0.91
        y: gameBarRect.height * 0.1
        width: gameBarRect.height
        height: gameBarRect.height * 0.8
        source: "qrc:/life"
    }
}
