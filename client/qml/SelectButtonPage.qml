import QtQuick 2.12
import QtQuick.Controls 2.5

Item{
  width: 480
  height: 640

  property var startY
  property var textBtn1
  property var textBtn2
  property var textBtn3
  property var textBtn4
  property bool btnMoveDown : false
  property bool btnMoveUp : false
  property var funcBtn1Click
  property var funcBtn2Click
  property var funcBtn3Click
  property var funcBtn4Click
  property bool _visible : false

  visible: _visible

  BackGround{
    id: bg
    anchors.fill: parent
  }

  SelectButton {
    id: btn1
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn1

    onClick: {
      funcBtn1Click()
    }
  }

  SelectButton {
    id: btn2
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn2

    onClick: {
      funcBtn2Click()
    }
  }

  SelectButton {
    id : btn3
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn3

    onClick: {
      funcBtn3Click()
    }
  }

  SelectButton {
    id: btn4
    y : startY
    anchors.horizontalCenter: parent.horizontalCenter
    text : textBtn4

    onClick: {
      funcBtn4Click()
    }
  }

  ButtonAnimation{
    id: btnAnimation
    target1: btn1
    target2: btn2
    target3: btn3
    target4: btn4
    startY: 640
    btnMoveUp: parent.btnMoveUp
    btnMoveDown: parent.btnMoveDown

    funcAfterBtnAnimUp4Stopped : function (){
      btnMoveUp = false
    }
  }

  function startBtnAnimUp(){
    btnAnimation.startBtnAnimUp()
  }

  function startBtnAnimDown(){
    btnAnimation.startBtnAnimDown()
  }

  function resetBtnToStartY(){
    btn1.y = startY
    btn2.y = startY
    btn3.y = startY
    btn4.y = startY
  }

  function hightLightChoice(choice){
    switch(choice){
      case 1:
        btn1.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        break;
      case 2:
        btn2.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        break;
      case 3:
        btn3.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        break;
      case 4:
        btn4.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        break;
    }
  }

  function flickerCorrectAnswer(count){
    switch(backEnd.correct_answer){
      case 1:
        btn1.background.source = applicationDirPath + (count % 2 == 0 ? "/assets/Sprite/btn_choose3.png" : "/assets/Sprite/btn.png")
        break;
      case 2:
        btn2.background.source = applicationDirPath + (count % 2 == 0 ? "/assets/Sprite/btn_choose3.png" : "/assets/Sprite/btn.png")
        break;
      case 3:
        btn3.background.source = applicationDirPath + (count % 2 == 0 ? "/assets/Sprite/btn_choose3.png" : "/assets/Sprite/btn.png")
        break;
      case 4:
        btn4.background.source = applicationDirPath + (count % 2 == 0 ? "/assets/Sprite/btn_choose3.png" : "/assets/Sprite/btn.png")
        break;
    }
  }
}