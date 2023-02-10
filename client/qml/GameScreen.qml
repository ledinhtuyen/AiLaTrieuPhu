import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
  width: 480
  height: 640

  property bool boolMoveUp : false

  SelectButtonPage{
    id: questionPage
    visible: isPlayGame
    moveUp: isMoveUp

    startY: 640
    textBtn1: backEnd.a
    textBtn2: backEnd.b
    textBtn3: backEnd.c
    textBtn4: backEnd.d

    funcBtn1Click: function (){
      backEnd.choiceAnswer(1)
    }

    funcBtn2Click: function (){
      backEnd.choiceAnswer(2)
    }

    funcBtn3Click: function (){
      backEnd.choiceAnswer(3)
    }

    funcBtn4Click: function (){
      backEnd.choiceAnswer(4)
    }

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
            prizePopup.clickShowPrizeBtn = true
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
      text: "Câu hỏi " + (backEnd.prize + 1)
    }

    Text {
      id : questionText
      visible: isMoveUp
      width: 360
      height: 150
      anchors.horizontalCenter: parent.horizontalCenter
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
      anchors.top: countDown.bottom
      anchors.topMargin: 45
      font.family: "roboto"
      font.pointSize: 14
      color: "white"
      text: backEnd.question
      wrapMode: Text.WordWrap
    }

    Image {
      id: fiftyFiftyIcon
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: parent.left
      anchors.top: questionImage.bottom
      anchors.topMargin: 15
      anchors.leftMargin: 45

      Image {
        width: 40
        height: 20
        source: applicationDirPath + "/assets/Sprite/ic_50_50.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
      }

      Image {
        id: x1
        visible: false
        source: applicationDirPath + "/assets/Sprite/x.png"
        anchors.fill: parent
      }

      MouseArea {
        anchors.fill: parent

        onClicked : {
          clickSound.play()
          fiftyFiftySound.play()
          x1.visible = true
          fiftyFiftyIcon.enabled = false
          backEnd.fiftyFifty()
        }
      }
    }

    Image {
      id: callPhoneIcon
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: fiftyFiftyIcon.right
      anchors.top: questionImage.bottom
      anchors.topMargin: 15
      anchors.leftMargin: 15

      Image {
        width: 30
        height: 20
        source: applicationDirPath + "/assets/Sprite/ic_goidienthoai.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
      }

      Image {
        id: x2
        visible: false
        source: applicationDirPath + "/assets/Sprite/x.png"
        anchors.fill: parent
      }

      MouseArea {
        anchors.fill: parent

        onClicked : {
          clickSound.play()
          fiftyFiftySound.play()
          x2.visible = true
          callPhoneIcon.enabled = false
          backEnd.callPhone()
          callPhonePopup.open()
        }
      }
    }

    Image {
      id: voteIcon
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: callPhoneIcon.right
      anchors.top: questionImage.bottom
      anchors.topMargin: 15
      anchors.leftMargin: 15

      Image {
        width: 30
        height: 20
        source: applicationDirPath + "/assets/Sprite/ic_vote.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
      }

      Image {
        id: x3
        visible: false
        source: applicationDirPath + "/assets/Sprite/x.png"
        anchors.fill: parent
      }

      MouseArea {
        anchors.fill: parent

        onClicked : {
          clickSound.play()
          fiftyFiftySound.play()
          votePopup.open()
          votePopup.isShow = true
          x3.visible = true
          voteIcon.enabled = false
          backEnd.vote()
        }
      }
    }

    Image {
      id: changeQuestionIcon
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: voteIcon.right
      anchors.top: questionImage.bottom
      anchors.topMargin: 15
      anchors.leftMargin: 15

      Image {
        width: 30
        height: 20
        source: applicationDirPath + "/assets/Sprite/ic_doicauhoi.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
      }

      Image {
        id: x4
        visible: false
        source: applicationDirPath + "/assets/Sprite/x.png"
        anchors.fill: parent
      }

      MouseArea {
        anchors.fill: parent

        onClicked : {
          clickSound.play()
          fiftyFiftySound.play()
          x4.visible = true
          changeQuestionIcon.enabled = false
          backEnd.changeQuestion()
        }
      }
    }
  }

  VotePopup{
    id: votePopup
  }

  PausePopup {
    id: pausePopup
    modal : true
  }

  CallPhonePopup {
    id: callPhonePopup
    modal : true
  }
}