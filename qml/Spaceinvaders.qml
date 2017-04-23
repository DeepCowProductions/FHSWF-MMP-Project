import QtQuick 2.4
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import Spaceinvaders 1.0
import QtQuick.Window 2.2

GameSceen {
    id: mainForm
    width: 640
    height: 480
    musicOn: false

    //### FOR USE TO CHECK IF TABLET OR SMARTPHONE
    property alias isTablet: mainForm.isTablet

    property alias leftButton: leftButton
    property alias rightButton: rightButton
    property alias shotButton: shotButton

    GameBar {
        id: gameBar
        firstLife.visible: mainForm.firstLife
        secLife.visible: mainForm.secLife
        thirdLife.visible: mainForm.thirdLife
        score.text: "Score: " + mainForm.score
    }

    /**
      * For checking if Tablet or Smartphone
      */
    function checkTabletOrSmartPhone() {
        if(!isTablet)
            state = "Portrait";
        else if (isTablet)
            state = "Landscape";
    }

    //### WHEN WIDTH OR HEIGHT WAS CHANGED
    //onWidthChanged: checkTabletOrSmartPhone()
    //onHeightChanged: checkTabletOrSmartPhone()

    //### WHEN THE APP IS COMPILED AND AT THE START CHECK ORIENTATION
    Component.onCompleted: checkTabletOrSmartPhone()

    RowLayout {
        id: bottomRow
        spacing: 5
        visible: Qt.platform.os == "android"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        MoveButton {
            id: leftButton
            text: "Left "
        }
        ShotButton {
            id: shotButton
        }
        MoveButton {
            id: rightButton
            text: "Right"
        }
    }

    //### STATES FOR THE TWO ORIENTATION
    states: [
        State {
            name: "Portrait"
            PropertyChanges { target: bottomRow; spacing: Screen.pixelDensity * 3 }
        },
        State {
            name: "Landscape" // set standard orientation to landscape
            PropertyChanges { target: bottomRow; spacing: Screen.pixelDensity * 20 }
        }

    ]
}
