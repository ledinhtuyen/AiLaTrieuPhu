import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
  id: menuMain
  width: 480
  height: 640
  property bool showMenuMain: true
  property bool isPlayGame: false
  property var isMoveUp : 0
  

  SelectButtonPage{
    id : menuSelectButton
    isVisible: showMenuMain
    moveUp: isMoveUp == 1 ? true : false

    startY: 640
    textBtn1: "Chơi 1 mình"
    textBtn2: "Thi đấu online"
    textBtn3: "Đổi mật khẩu"
    textBtn4: "Đăng xuất"

    funcBtn1Click: function(){
      moveDown = true
      backEnd.playAlone()
    }

    funcBtn3Click: function(){
      stackView.push("ChangePasswordPage.qml")
    }

    funcBtn4Click: function(){
      backEnd.logOut()
      stackView.pop()
    }
  }

  Logo {
    visible: showMenuMain
    anchors.horizontalCenter: parent.horizontalCenter
  }

  Text {
    id: text
    visible: showMenuMain
    width: 220
    height: 50
    anchors.top: parent.top
    anchors.topMargin: 265
    anchors.horizontalCenter: parent.horizontalCenter
    font.bold: true
    font.pointSize: 16
    font.family: "roboto"
    text: "Hello, <font color='red'>" + backEnd.user_name + "</font>"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    color: "white"
  }

  Text {
    id: text2
    visible: showMenuMain
    width: 220
    height: 50
    anchors.top: parent.top
    anchors.topMargin: 295
    anchors.horizontalCenter: parent.horizontalCenter
    font.bold: true
    font.pointSize: 16
    font.family: "roboto"
    text: "Score PvP:"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    color: "white"
  }

  GameScreen {
    id : gameScreen
    boolMoveUp: isMoveUp == 2 ? true : false
  }

  PrizePopup{
    id: prizePopup
    modal : true

    property bool clickShowPrizeBtn: false

    onOpened : {
      if (!clickShowPrizeBtn && menuMain.isMoveUp != 2){
        mainTheme.stop()
        prizeTheme.play()
        runningHighLightPrize = true
      }
      else if (!clickShowPrizeBtn && menuMain.isMoveUp == 2){
        prizePopup.flickerPrize()
      }
      else {
        prize = backEnd.prize + 1
      }
    }
  }

  function startBtnAnimUp(){
    gameScreen.startBtnAnimUp()
  }

  function resetBtnToStartY(){
    gameScreen.resetBtnToStartY()
  }

  function flickerCorrectAnswer(count){
    gameScreen.flickerCorrectAnswer(count)
  }

  function showPrizePopup(){
    prizePopup.open()
  }
}