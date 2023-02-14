import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
  width: 480
  height: 640

  property bool btnMoveUp : false

  SelectButtonPage{
    id: questionPage
    visible: !showMenuMain
    btnMoveUp: parent.btnMoveUp

    startY: 640
    textBtn1: backEnd.a
    textBtn2: backEnd.b
    textBtn3: backEnd.c
    textBtn4: backEnd.d

    funcBtn1Click: function (){
      choice_answer(1)
    }

    funcBtn2Click: function (){
      choice_answer(2)
    }

    funcBtn3Click: function (){
      choice_answer(3)
    }

    funcBtn4Click: function (){
      choice_answer(4)
    }

    Rectangle{
      color: "transparent"
      width: 60
      height: 60
      anchors.right: parent.right
      visible: sTatus == 2 ? true : false

      Image{
        source: applicationDirPath + "/assets/Sprite/btn_xemgiaithuong.png"
        anchors.fill: parent
        MouseArea{
          anchors.fill: parent
          onClicked: {
            clickSound.play()
            menuMain.clickShowPrizeBtn = true
            prizePopup.open()
          }
        }
      }
    }

    Rectangle{
      color: "transparent"
      width: 60
      height: 60
      visible: sTatus == 2 ? true : false

      Image{
        source: applicationDirPath + "/assets/Sprite/btn_pause.png"
        anchors.fill: parent
        MouseArea{
          anchors.fill: parent
          onClicked: {
            clickSound.play()
            stopCountDown()
            pausePopup.open()
          }
        }
      }
    }

    CountDown{
      id: countDown
      visible: sTatus == 2 ? true : false
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: parent.top
      anchors.topMargin: 10
    }

    Image {
      id: questionImage
      visible: sTatus == 2 ? true : false
      width: 400
      height: 200
      source: applicationDirPath + "/assets/Sprite/question_bg.png"
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: countDown.bottom
    }

    Text {
      id : questionNumber
      visible: sTatus == 2 ? true : false
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
      visible: sTatus == 2 ? true : false
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

    Row {
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: questionImage.bottom
      anchors.topMargin: 15
      spacing: 15
    Image {
      id: fiftyFiftyIcon
      visible: sTatus == 2 ? true : false
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      // anchors.left: parent.left
      // anchors.top: questionImage.bottom
      // anchors.topMargin: 15
      // anchors.leftMargin: 45

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
      visible: sTatus == 2 ? true : false
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      // anchors.left: fiftyFiftyIcon.right
      // anchors.top: questionImage.bottom
      // anchors.topMargin: 15
      // anchors.leftMargin: 15

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
        }
      }
    }

    Image {
      id: voteIcon
      visible: sTatus == 2 ? true : false
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      // anchors.left: callPhoneIcon.right
      // anchors.top: questionImage.bottom
      // anchors.topMargin: 15
      // anchors.leftMargin: 15

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
          x3.visible = true
          voteIcon.enabled = false
          backEnd.vote()
        }
      }
    }

    Image {
      id: changeQuestionIcon
      visible: sTatus == 2 ? true : false
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      // anchors.left: voteIcon.right
      // anchors.top: questionImage.bottom
      // anchors.topMargin: 15
      // anchors.leftMargin: 15

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
          questionPage.startBtnAnimDown()
          rootWindow.click_change_question = true
        }
      }
    }

    Column{
      width: 70
      height: 40
      Text {
        width: 70
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "roboto"
        font.pointSize: 13
        color: "white"
        text: isPlayPvP ? backEnd.enemy_name + "|" + backEnd.enemy_current_question + "/15" : ""
        visible: isPlayPvP ? true : false
      }
      Text {
        width: 70
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "roboto"
        font.pointSize: 13
        color: "white"
        text: isPlayPvP ? backEnd.enemy_seconds + "s|" + backEnd.enemy_status : ""
        visible: isPlayPvP ? true : false
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

  function startBtnAnimUp() {
    questionPage.startBtnAnimUp()
  }

  function resetBtnToStartY(){
    questionPage.resetBtnToStartY()
  }

  function hightLightChoice(choice) {
    questionPage.hightLightChoice(choice)
  }

  function flickerCorrectAnswer(count) {
    questionPage.flickerCorrectAnswer(count)
  }

  function resetHelperIcon() {
    x1.visible = false
    x2.visible = false
    x3.visible = false
    x4.visible = false

    fiftyFiftyIcon.enabled = true
    callPhoneIcon.enabled = true
    voteIcon.enabled = true
    changeQuestionIcon.enabled = true
  }

  function startCountDown() {
    countDown.start()
  }

  function stopCountDown() {
    countDown.stop()
  }

  function continueCountDown() {
    countDown.continueCountDown()
  }

  function choice_answer(choice) {
      hightLightChoice(choice)
      if (backEnd.prize > 5)
        quest5To15Theme.stop()
      else
        quest1To5Theme.stop()
      finalAnswerSound.play()
      stopCountDown()
      backEnd.choiceAnswer(choice, menuMain.time)
  }

  function openVotePopup() {
    votePopup.open()
    votePopup.isShow = true
  }

  function openCallPhonePopup(){
    callPhonePopup.open()
  }
}