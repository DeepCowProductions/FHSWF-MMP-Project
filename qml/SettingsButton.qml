import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0


/**
  * Own Button for starting the game
  */
Button {
    id: settingsButton
    //### SET STYLE OF BUTTON
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 65
            implicitWidth: 65
            radius: 50
            color: "transparent"
            Canvas {
                id:settingsButtonCanvas
                height: settingsButton.height
                width: settingsButton.width
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect( 0, 0, parent.width, parent.height );

                    ctx.strokeStyle = "green";
                    ctx.fillStyle = "green";

                    ctx.beginPath();
                    ctx.arc(parent.width*0.5,parent.height*0.5, 30, 0, 2 * Math.PI, false);
                    ctx.fill();
                    ctx.stroke();

                    ctx.globalCompositeOperation= "xor";
                }
            }
            RadialGlossy {

            }
        }
    }
}
