import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4

Button {
    id: button

    //### LOAD ANDROID FONT
    FontLoader { id: fixedFont; name: "Roboto light" }
    FontLoader { id: localFont; source: "qrc:/fonts/Roboto-Light.ttf" }

    // set Style of Button
    style: ButtonStyle {
        background: Rectangle {
            color: "grey"
            width: parent.width
            radius: 10
            Glossy { // Glossyeffect
                radius: 10
            }
        }
        label: Text {
            text: button.text // put in the text of the button
            color: "black"
            font.family: "Roboto light"
            font.pointSize: 12
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
