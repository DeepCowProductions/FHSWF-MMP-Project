import QtQuick 2.7

Item {
     id: toggleswitch
     width: background.width; height: background.height

     property alias musicOn: toggleswitch.on
     property bool on: false

     function toggle() {
         if (toggleswitch.state == "on")
             toggleswitch.state = "off";
         else
             toggleswitch.state = "on";
     }

     function releaseSwitch() {
         if (knob.x == 2) {
             if (toggleswitch.state == "off") return;
         }
         if (knob.x == 74) {
             if (toggleswitch.state == "on") return;
         }
         toggle();
     }

     Image {
         id: background
         source: "qrc:/knobbackground"
         MouseArea { anchors.fill: parent; onClicked: toggle() }
     }

     Image {
         id: knob
         x: 2; y: 3
         source: "qrc:/knob"
         width:  background.width/2.2 - 5
         height: background.height-5

         MouseArea {
             anchors.fill: parent
             drag.target: knob; drag.axis: Drag.XAxis; drag.minimumX: 2; drag.maximumX: 74
             onClicked: toggle()
             onReleased: releaseSwitch()
         }
     }

     states: [
         State {
             name: "on"
             PropertyChanges { target: knob; x: 74 }
             PropertyChanges { target: toggleswitch; on: true }
         },
         State {
             name: "off"
             PropertyChanges { target: knob; x: 2 }
             PropertyChanges { target: toggleswitch; on: false }
         }
     ]

     transitions: Transition {
         NumberAnimation { properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
     }
 }
