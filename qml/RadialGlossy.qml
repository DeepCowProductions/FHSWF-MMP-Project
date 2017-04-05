import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    anchors.centerIn: parent // center in parent
    width: parent.width - parent.border.width
    height: parent.height - parent.border.width
    radius: 50
    clip: true

    border.width: parent.border.width/2
    border.color: "#22FFFFFF" /* semitransparent border first two number are the precentage of
                                 transparency see "http://online.sfsu.edu/chrism/hexval.html"*/

    // here we set the gradient for the glossy effect, you can play with the pers
    gradient: Gradient {
        GradientStop { position: 0;    color: "#88FF0000" }  // from 0 to 0.1 transparency of 35%
        GradientStop { position: 0.1;   color: "#55FF0000" } // from 0.1 to 0.5 transparency of 33%
        GradientStop { position: 0.2;   color: "#33FF0000" } // from 0.5 to 0.501 transparency of 20%
        GradientStop { position: 0.301; color: "#11FF0000" } // from 0.501 to 0.8 black with transparency of 7%
        GradientStop { position: 0.8;   color: "#11FFFFFF" } // from 0.8 to 1 transparency: see above
        GradientStop { position: 1;    color: "#55FFFFFF" }  // transparency: see second line
    }
    rotation: 60
}

