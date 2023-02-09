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
          x1.visible = true
          namMuoiNamMuoi.enabled = false
        }
      }
    }

    Image {
      id: goiDienThoaiChoNguoiThan
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: namMuoiNamMuoi.right
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
          x2.visible = true
          goiDienThoaiChoNguoiThan.enabled = false
        }
      }
    }

    Image {
      id: hoiYKienKhanGia
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: goiDienThoaiChoNguoiThan.right
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
          vote.open()
          vote.isShow = true
          x3.visible = true
          hoiYKienKhanGia.enabled = false
        }
      }
    }

    Image {
      id: doiCauHoi
      visible: isMoveUp
      width: 70
      height: 40
      source: applicationDirPath + "/assets/Sprite/btn_trogiup.png"
      anchors.left: hoiYKienKhanGia.right
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
          x4.visible = true
          doiCauHoi.enabled = false
        }
      }
    }
  }

  VotePopup{
    id: vote
  }

  PausePopup {
    id: pausePopup
    modal : true
  }
}