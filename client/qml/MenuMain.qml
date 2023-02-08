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

    CountDown{
      id: countDown
      visible: isMoveUp
      isRunning: isMoveUp
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: parent.top
      anchors.topMargin: 10
    }

    Image {
      id: questionImage
      visible: isMoveUp
      width: 400
      height: 200
      source: applicationDirPath + "/assets/Sprite/question_bg.png"
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: countDown.bottom
    }

    Text {
      id : questionNumber
      visible: isMoveUp
      width: 100
      height: 50
      anchors.horizontalCenter: parent.horizontalCenter
      horizontalAlignment: Text.AlignHCenter
      anchors.top: countDown.bottom
      anchors.topMargin: 10
      font.family: "roboto"
      font.pointSize: 14
      text: "Câu hỏi 1"
    }

    Text {
      id : questionText
      visible: isMoveUp
      width: 360
      height: 150
      anchors.horizontalCenter: parent.horizontalCenter
      horizontalAlignment: Text.AlignHCenter
      anchors.top: countDown.bottom
      anchors.topMargin: 50
      font.family: "roboto"
      font.pointSize: 14
      color: "white"
      text: "Noi dung cau hoi"
      wrapMode: Text.WordWrap
    }

    Image {
      id: namMuoiNamMuoi
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: parent.left
      anchors.top: questionImage.bottom
      anchors.topMargin: 15
      anchors.leftMargin: 50

      Image {
        id: namMuoiNamMuoiIcon
        width: 40
        height: 20
        source: applicationDirPath + "/assets/Sprite/ic_50_50.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
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