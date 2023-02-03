import QtQuick 2.0
import QtQuick.Controls 2.12

Item{
  width: 480
  height: 640

  property var startY
  property var textBtn1
  property var textBtn2
  property var textBtn3
  property var textBtn4
  property var funcBtn1Click
  property var funcBtn2Click
  property var funcBtn3Click
  property var funcBtn4Click

  BackGround{
    id: bg
    anchors.fill: parent
  }

  SelectButton {
    id: btn1
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn1

    onClicked: {
      funcBtn1Click()
    }
  }

  SelectButton {
    id: btn2
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn2

    onClicked: {
      funcBtn2Click()
    }
  }

  SelectButton {
    id : btn3
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn3

    onClicked: {
      funcBtn3Click()
    }
  }

  SelectButton {
    id: btn4
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn4

    onClicked: {
      funcBtn4Click()
    }
  }

  ButtonAnimation{
    target1: btn1
    target2: btn2
    target3: btn3
    target4: btn4
    startY: menuStart.height
    isMoveUp: true

    funcAfterBtnAnimUp4Stopped : function (){
      btn1.background.opacity = 1
      btn2.background.opacity = 1
      btn3.background.opacity = 1
      btn4.background.opacity = 1
      btn1.enabled = true
      btn2.enabled = true
      btn3.enabled = true
      btn4.enabled = true
    }
  }
}