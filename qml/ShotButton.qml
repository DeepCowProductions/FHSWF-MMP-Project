import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

/**
  * Own Button for shotrmation befor starting the game
  */
Button {
    id: shotButton
    //### SET STYLE OF BUTTON
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 65
            implicitWidth: 65
            radius: 50
            color: shotButton.pressed ? "green" : "transparent";
            border.color: shotButton.pressed ? "blue" : "grey";
            border.width: shotButton.pressed ? 2 : 1;
            Canvas {
                id: shotButtonCanvas
                height: shotButton.height
                width: shotButton.width
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect( 0, 0, parent.width, parent.height );

                    ctx.strokeStyle = "grey";
                    ctx.fillStyle = "grey";

                    ctx.beginPath();
                    ctx.arc(parent.width*0.5,parent.height*0.5, 30, 0, 2 * Math.PI, false);
                    ctx.fill();
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.arc(parent.width*0.5,parent.height*0.5, 17, 0, 2 * Math.PI, false);
                    ctx.fill();
                    ctx.stroke();

                    ctx.globalCompositeOperation = "xor";

                    ctx.lineWidth = 3;

                    ctx.strokeStyle = "blue";

                    ctx.beginPath();
                    ctx.moveTo(parent.width * 0.5,(parent.height * 0.5) - 23);
                    ctx.lineTo(parent.width * 0.5,(parent.height * 0.5) - 8);
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.arc(parent.width * 0.5,parent.height * 0.5, 17, -1.15, -0.1 * Math.PI, false);
                    ctx.stroke();


                    ctx.beginPath();
                    ctx.moveTo(parent.width * 0.5+23,parent.height * 0.5);
                    ctx.lineTo(parent.width * 0.5+8,parent.height * 0.5);
                    ctx.stroke();

                    ctx.beginPath();;
                    ctx.arc(parent.width * 0.5,parent.height * 0.5, 17, 0.3, 0.38 * Math.PI, false);
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.moveTo(parent.width * 0.5,(parent.height * 0.5) + 23);
                    ctx.lineTo(parent.width * 0.5,(parent.height * 0.5) + 8);
                    ctx.stroke();

                    ctx.beginPath();;
                    ctx.arc(parent.width * 0.5,parent.height * 0.5, 17, 2, 0.9 * Math.PI, false);
                    ctx.stroke();

                    ctx.beginPath();
                    ctx.moveTo(parent.width * 0.5 - 23,parent.height * 0.5);
                    ctx.lineTo(parent.width * 0.5 - 8,parent.height * 0.5);
                    ctx.stroke();

                    ctx.beginPath();;
                    ctx.arc(parent.width * 0.5,parent.height * 0.5, 17, 3.45, 1.35 * Math.PI, false);
                    ctx.stroke();
                }
            }
        }
    }
}

