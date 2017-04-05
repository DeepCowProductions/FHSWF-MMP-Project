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
    id: closeButton
    //### SET STYLE OF BUTTON
    style: ButtonStyle {
        background: Rectangle {
            implicitHeight: 65
            implicitWidth: 65
            radius: 50
            color: "transparent"
            Canvas {
                id:closeButtonCanvas
                height: closeButton.height
                width: closeButton.width
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
                    ctx.lineWidth = 3;

                    ctx.beginPath();
                    ctx.rotate(-45.1);
                    ctx.arc(parent.width*-0.25,parent.height*0.675, 15, 0, 1.7 * Math.PI, false);
                    ctx.stroke();

                    ctx.rotate(45.1);
                    ctx.beginPath();
                    ctx.moveTo(parent.width*0.5,parent.height*0.5);
                    ctx.lineTo(parent.width*0.5,parent.height*0.2);
                    ctx.stroke();


                    // DRAW A C FOR CLOSE

                }
            }
            RadialGlossy {

            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {
            Qt.quit();
        }
    }
}
