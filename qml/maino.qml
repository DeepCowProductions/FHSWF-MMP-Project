import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello OpenGL in QML World")
    width: 480
    height: 800
    visible: true
    //set color to transparent, if you want to draw under QML-Items
    //color: "transparent"


    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }
    
    MainForm {
        anchors.fill: parent
        id:appWindow
        movementActivated: true
        //Rotation
        rotateX: buttonRotateX.pressed
        rotateY: buttonRotateY.pressed
        rotateZ: buttonRotateZ.pressed
        zoomIn: buttonZoomIn.pressed
        zoomOut: buttonZoomOut.pressed
        onRotationXChanged: buttonRotateX.text = qsTr("Rotate X") + ": " + rotationX
        onRotationYChanged: buttonRotateY.text = qsTr("Rotate Y") + ": " + rotationY
        onRotationZChanged: buttonRotateZ.text = qsTr("Rotate Z") + ": " + rotationZ
        //Exit
        buttonReset.onClicked: resetView()
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("Information")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
