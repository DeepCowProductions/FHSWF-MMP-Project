import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0


/**
  * Own Button for information befor starting the game
  */
Button {
    id: infoButton
    //### SET STYLE OF BUTTON
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 65
            implicitWidth: 65
            radius: 50
            color: "transparent"
            Canvas {
                id: infoButtonCanvas
                height: infoButton.height
                width: infoButton.width
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect( 0, 0, parent.width, parent.height );

                    ctx.strokeStyle = "green";
                    ctx.fillStyle = "green";

                    ctx.beginPath();
                    ctx.arc(parent.width*0.5,parent.height*0.5, 30, 0, 2 * Math.PI, false);
                    ctx.fill();
                    ctx.stroke();

                    ctx.globalCompositeOperation = "source-out";

                    ctx.beginPath();
                    ctx.arc(parent.width*0.5,parent.height*0.3, 5, 0, 2 * Math.PI, false);
                    ctx.fill();
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.roundedRect(parent.width*0.425, parent.height*0.48, 10, 25, 2 * Math.PI, 2 * Math.PI);
                    ctx.fill();
                    ctx.stroke();

                }
            }
            RadialGlossy {

            }
        }
    }
}
