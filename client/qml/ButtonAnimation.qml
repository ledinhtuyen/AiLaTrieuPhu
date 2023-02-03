import QtQuick 2.0
import QtQuick.Controls 2.12

Item{
  property var target1
  property var target2
  property var target3
  property var target4
  property var startY
  property var isMoveUp: false
  property var funcAfterBtnAnimUp4Stopped

  NumberAnimation {
    id : btnAnimUp1
    duration: 350
    target : target1
    from : startY
    to: 350
    property : "y"
    running: isMoveUp
    onStopped :{
      btnAnimUp2.start()
    }
  }

  NumberAnimation {
    id : btnAnimUp2
    duration: 250
    target : target2
    from : startY
    to: 415
    properties : "y"
    running: false
    onStopped :{
      btnAnimUp3.start()
    }
  }

  NumberAnimation {
    id : btnAnimUp3
    duration: 220
    target : target3
    from : startY
    to: 480
    properties : "y"
    running : false
    onStopped :{
      btnAnimUp4.start()
    }
  }

  NumberAnimation {
    id : btnAnimUp4
    duration: 200
    target : target4
    from : startY
    to: 545
    properties : "y"
    running : false

    onStopped :{
      funcAfterBtnAnimUp4Stopped()
    }
  }
}