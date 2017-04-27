import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0


/*
 * A button for going to the settingsPage
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
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

                    ctx.lineWidth = 7;

                    ctx.beginPath();
                    ctx.arc(parent.width*0.5,parent.height*0.5, 10, 0, 2 * Math.PI, false);
                    ctx.stroke();

                    ctx.lineWidth = 2;

                    ctx.beginPath();
                    ctx.moveTo(parent.width*0.5 - 6.5,parent.height*0.5 - 11.91);
                    ctx.lineTo(parent.width*0.5 - 5,parent.height*0.5 - 20);
                    ctx.lineTo(parent.width*0.5 + 5,parent.height*0.5 - 20);
                    ctx.lineTo(parent.width*0.5 + 6.5,parent.height*0.5 - 11.91);

                    ctx.lineTo(parent.width*0.5 + 13,parent.height*0.5 - 15.01);
                    ctx.lineTo(parent.width*0.5 + 18.5,parent.height*0.5 - 7.01);
                    ctx.lineTo(parent.width*0.5 + 12.8,parent.height*0.5);

                    ctx.lineTo(parent.width*0.5 + 20.5,parent.height*0.5 + 3.21);
                    ctx.lineTo(parent.width*0.5 + 17.5,parent.height*0.5 + 11.51);
                    ctx.lineTo(parent.width*0.5 + 7.2,parent.height*0.5 + 11.51);

                    ctx.lineTo(parent.width*0.5 + 6.5,parent.height*0.5 + 19.21);
                    ctx.lineTo(parent.width*0.5 - 5,parent.height*0.5 + 19.21);
                    ctx.lineTo(parent.width*0.5 - 6.5,parent.height*0.5 + 11.51);

                    ctx.lineTo(parent.width*0.5 - 17,parent.height*0.5 + 13.01);
                    ctx.lineTo(parent.width*0.5 - 20,parent.height*0.5 + 4.51);
                    ctx.lineTo(parent.width*0.5 - 13.2,parent.height*0.5);

                    ctx.lineTo(parent.width*0.5 - 20.5,parent.height*0.5 - 6.01);
                    ctx.lineTo(parent.width*0.5 - 14.5,parent.height*0.5 - 14.51);
                    ctx.lineTo(parent.width*0.5 - 6.5,parent.height*0.5 - 11.91);
                    //ctx.fill();
                    ctx.stroke();
                }
            }
            RadialGlossy {

            }
        }
    }
}
