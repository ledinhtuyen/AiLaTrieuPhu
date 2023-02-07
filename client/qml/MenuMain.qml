import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
  id: menuMain
  width: 480
  height: 640
  property bool showMenuMain: true
  property bool isPlayGame: false
  property bool isMoveUp : false
  property bool clickShowPrizeBtn: false
  

  SelectButtonPage{
    id : menuSelectButton
    isVisible: showMenuMain
    moveUp: !isMoveUp

    startY: 640
    textBtn1: "Chơi 1 mình"
    textBtn2: "Thi đấu online"
    textBtn3: "Đổi mật khẩu"
    textBtn4: "Đăng xuất"

    funcBtn1Click: function(){
      moveDown = true
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

  SelectButtonPage{
    id: questionPage
    visible: isPlayGame
    moveUp: isMoveUp

    startY: 640
    textBtn1: "Đáp án 1"
    textBtn2: "Đáp án 2"
    textBtn3: "Đáp án 3"
    textBtn4: "Đáp án 4"

    Rectangle{
      color: "transparent"
      width: 60
      height: 60
      anchors.right: parent.right
      visible: isMoveUp

      Image{
        source: applicationDirPath + "/assets/Sprite/btn_xemgiaithuong.png"
        anchors.fill: parent
        MouseArea{
          anchors.fill: parent
          onClicked: {
            clickSound.play()
            clickShowPrizeBtn = true
            prizePopup.open()
          }
        }
      }
    }

    Rectangle{
      color: "transparent"
      width: 60
      height: 60
      visible: isMoveUp

      Image{
        source: applicationDirPath + "/assets/Sprite/btn_pause.png"
        anchors.fill: parent
        MouseArea{
          anchors.fill: parent
          onClicked: {
            clickSound.play()
            pausePopup.open()
          }
        }
      }
    }
  }

  PrizePopup{
    id: prizePopup
    modal : true

    onOpened : {
      if (!clickShowPrizeBtn){
        mainTheme.stop()
        prizeTheme.play()
        runningHighLightPrize = true
      }
      else {
        prize = 6
      }
    }
  }

  PausePopup {
    id: pausePopup
    modal : true
  }
}