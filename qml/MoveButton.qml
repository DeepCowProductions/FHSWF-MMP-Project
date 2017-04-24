import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0


/**
  * Own Button for the Movement
  */
Button {
    id: moveButton

    //### LOAD ANDROID FONT
    FontLoader { id: fixedFont; name: "Roboto light" }
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto-Light.ttf" }

    //### SET STYLE OF BUTTON
    style: ButtonStyle {
        background:
            Rectangle {
            id: buttonRect
            implicitWidth: Screen.pixelDensity * 20
            implicitHeight: Screen.pixelDensity * 10 //### FOR USE IN MOBILE PHONES
            radius: 4
            color: moveButton.pressed ? "green" : "grey";
            border.color: moveButton.pressed ? "blue" : "grey";
            border.width: moveButton.pressed ? 2 : 1;
            Glossy { //### GLOSSYEFFECT

            }
        }

        label: Text {
            id: buttonText
            text: moveButton.text
            color: "black"
            font.family: "Roboto light"
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    antialiasing: true
}
