import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtTest 1.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height - 5
    title: qsTr("Space Invaders 3D")
    color: "transparent"

    Spaceinvaders {
        id: game
        visible: false
        anchors.fill: parent

        movementActivated: true
        runGameLoop : false

        leftKeyPressed: leftButton.pressed
        rightKeyPressed: rightButton.pressed
        shotButtonPressed: shotButton.pressed
        musicOn: settingsPage.musicOn
    }

//    SignalSpy {
//        id: spy
//        target: game
//        signalName: ""
//    }
//    TestCase {
//        name: "ButtonClick"
//        function test_click() {
//            compare(spy.count, 0)
//            button.clicked();
//            compare(spy.count, 1)
//        }
//    }

    Startpage {
        id: startPage
        visible: true
        playButton.onClicked:  {
            game.visible = true;
            startPage.visible = false;
            game.runGameLoop = true
        }

        infoButton.onClicked: {
            infoPage.visible = true;
        }
        settingsButton.onClicked: {
            settingsPage.visible = true;
        }
        anchors.fill: parent
    }

    SettingsPage {
        id: settingsPage
        anchors.fill: parent
        visible: startPage.settingsButton.pressed ? true : false
        backButton.onClicked: {
            startPage.visible = true;
            settingsPage.visible = false;
        }
    }

    InformationPage {
        id: infoPage
        anchors.fill: parent
        visible: startPage.infoButton.pressed ? true : false
        backButton.onClicked: {
            startPage.visible = true;
            infoPage.visible = false;
        }
    }
}
