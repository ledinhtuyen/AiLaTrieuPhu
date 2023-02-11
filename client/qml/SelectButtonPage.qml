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
  property bool moveDown : false
  property bool moveUp : false
  property var funcBtn1Click
  property var funcBtn2Click
  property var funcBtn3Click
  property var funcBtn4Click
  property bool isVisible : false

  visible: isVisible

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
    isMoveUp: moveUp
    isMoveDown: moveDown

    funcAfterBtnAnimUp4Stopped : function (){
      moveUp = false
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
        btn1.background.enabled = false
        break;
      case 2:
        btn2.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        btn2.background.enabled = false
        break;
      case 3:
        btn3.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        btn3.background.enabled = false
        break;
      case 4:
        btn4.background.source = applicationDirPath + "/assets/Sprite/btn_choose2.png"
        btn4.background.enabled = false
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