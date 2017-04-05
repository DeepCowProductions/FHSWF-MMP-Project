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
    id: pauseButton
    //### SET STYLE OF BUTTON
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 35
            implicitWidth: 35
            radius: 50
            color: "transparent"
            Canvas {
                id:pauseButtonCanvas
                height: pauseButton.height
                width: pauseButton.width
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect( 0, 0, parent.width, parent.height );

                    ctx.strokeStyle = "green";
                    ctx.fillStyle = "green";

                    ctx.beginPath();
                    ctx.rect(parent.width * 0.35,parent.height * 0.25, parent.width * 0.1, parent.height * 0.4);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.rect(parent.width * 0.55,parent.height * 0.25, parent.width * 0.1, parent.height * 0.4);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();

                }
            }
        }
    }
}
