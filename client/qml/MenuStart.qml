import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

Item{
  id: menuStart
  anchors.fill: parent
  width: 480
  height: 640

  BorderImage {
    id: borderImage
    anchors.fill: parent
    source: applicationDirPath + "/assets/Sprite/bg.png"
  }

  Image {
    id: image
    width: 250
    height: 250
    anchors.top: parent.top
    anchors.topMargin: 50
    anchors.horizontalCenter: parent.horizontalCenter
    fillMode: Image.PreserveAspectFit
    source: applicationDirPath + "/assets/Sprite/2.png"
  }

  Image {
    id: image2
    width: 350
    height: 250
    anchors.top: parent.top
    anchors.topMargin: 50
    anchors.horizontalCenter: parent.horizontalCenter
    fillMode: Image.PreserveAspectFit
    source: applicationDirPath + "/assets/Sprite/1.png"
  }

  Text {
    id: text
    width: 250
    height: 50
    anchors.top: parent.top
    anchors.topMargin: 150
    anchors.horizontalCenter: parent.horizontalCenter
    font.bold: true
    font.pointSize: 20
    font.family: "roboto"
    text: qsTr("Ai Là Triệu Phú")
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    color: "white"
  }

  Button {
    id: startBtn
    width: parent.width
    height: 50
    y : menuStart.height
    anchors.horizontalCenter: parent.horizontalCenter

    contentItem: Text {
      font.bold: true
      font.pointSize: 17
      font.family: "roboto"
      text: qsTr("Bắt đầu")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }

    background: Image {
      source: applicationDirPath + "/assets/Sprite/btn.png"
      opacity: 0.5
    }

    NumberAnimation on y {
      id : startBtnAnim
      duration: 350
      from : menuStart.height
      to: 350
      onStopped :{
        guideBtnAnim.start()
      }
    }

    onClicked: {
      clickSound.play()
      waitPopup.popMessage = "Connecting to server..."
      waitPopup.open()
      act = "connect2server"
      backEnd.connectToServer()
    }

    onHoveredChanged: {
      if (startBtn.hovered)
      {
        startBtn.background.source = applicationDirPath + "/assets/Sprite/btn_choose.png"
      }
      else {
        startBtn.background.source = applicationDirPath + "/assets/Sprite/btn.png"
      }
    }
  }

  Button {
    id: guideBtn
    width: parent.width
    height: 50
    y : menuStart.height
    contentItem: Text {
      font.bold: true
      font.pointSize: 17
      font.family: "roboto"
      text: qsTr("Cách chơi")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }
    anchors.horizontalCenter: parent.horizontalCenter

    background: Image {
      source: applicationDirPath + "/assets/Sprite/btn.png"
      opacity: 0.5
    }

    NumberAnimation on y {
      id : guideBtnAnim
      duration: 250
      from : menuStart.height
      to: 415
      running: false
      onStopped :{
        creditBtnAnim.start()
      }
    }

    onClicked: {
      clickSound.play()
      guideDialog.visible = true
    }

    onHoveredChanged: {
      if (guideBtn.hovered)
      {
        guideBtn.background.source = applicationDirPath + "/assets/Sprite/btn_choose.png"
      }
      else {
        guideBtn.background.source = applicationDirPath + "/assets/Sprite/btn.png"
      }
    }
  }

  Button {
    id: creditBtn
    width: parent.width
    height: 50
    y : menuStart.height
    contentItem: Text {
      font.bold: true
      font.pointSize: 17
      font.family: "roboto"
      text: qsTr("Giới thiệu")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }
    anchors.horizontalCenter: parent.horizontalCenter

    background: Image {
      source: applicationDirPath + "/assets/Sprite/btn.png"
      opacity: 0.5
    }

    NumberAnimation on y {
      id : creditBtnAnim
      duration: 220
      from : menuStart.height
      to: 480
      running : false
      onStopped :{
        quitBtnAnim.start()
      }
    }

    onClicked: {
      clickSound.play()
      creditDialog.visible = true
    }

    onHoveredChanged: {
      if (creditBtn.hovered)
      {
        creditBtn.background.source = applicationDirPath + "/assets/Sprite/btn_choose.png"
      }
      else {
        creditBtn.background.source = applicationDirPath + "/assets/Sprite/btn.png"
      }
    }
  }

  Button {
    id: quitBtn
    width: parent.width
    height: 50
    y : menuStart.height
    contentItem: Text {
      font.bold: true
      font.pointSize: 17
      font.family: "roboto"
      text: qsTr("Thoát")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }
    anchors.horizontalCenter: parent.horizontalCenter

    background: Image {
      source: applicationDirPath + "/assets/Sprite/btn.png"
      opacity: 0.5
    }

    NumberAnimation on y {
      id : quitBtnAnim
      duration: 200
      from : menuStart.height
      to: 545
      running : false
      
      onStopped :{
        startBtn.background.opacity = 1
        guideBtn.background.opacity = 1
        creditBtn.background.opacity = 1
        quitBtn.background.opacity = 1
      }
    }

    onClicked: {
      clickSound.play()
      Qt.quit()
    }

    onHoveredChanged: {
      if (quitBtn.hovered)
      {
        quitBtn.background.source = applicationDirPath + "/assets/Sprite/btn_choose.png"
      }
      else {
        quitBtn.background.source = applicationDirPath + "/assets/Sprite/btn.png"
      }
    }
  }

  Dialog {
    id: guideDialog
    visible: false
    title: "Cách chơi"

    contentItem: Rectangle {
      implicitWidth: 400
      implicitHeight: 400

      Text {
        id: titleGuide
        text: "<h1><b><i><font color='red'>Hướng dẫn chơi</font></i></b></h1>"
        font.family: "Times New Roman"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
      }
      Text {
        id: guideText
        width: 350
        height: 400
        text: "
        1. Người chơi chọn bắt đầu câu hỏi sẽ xuất hiện, bắt đầu tính thời gian 15s cho mỗi câu hỏi<br>
        2. Có 4 phương án. Người chơi chọn 1 đáp án trả lời<br>
        3. Đáp án đúng câu hỏi tiếp theo sẽ xuất hiện<br>
        4. Nếu sai lượt chơi sẽ kết thúc và hiển thị kết quả với số điểm nhận được tương ứng"
        font.family: "Times New Roman"
        font.pointSize: 15
        wrapMode: Text.WordWrap
        anchors.top: titleGuide.bottom
        anchors.topMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 30
      }
    }
  }

  Dialog {
    id: creditDialog
    visible: false
    title: "Giới thiệu"

    contentItem: Rectangle {
      implicitWidth: 450
      implicitHeight: 400

      Text {
        id: titleCredit
        text: "<h1><b><i><font color='red'>Giới thiệu</font></i></b></h1>"
        font.family: "Times New Roman"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
      }

      Text{
        id: contentCredit1
        text: "<h3><font color='#148F77'><i>1. Lê Đình Tuyên</i></font></h3>
        <b>Github</b>:   <a href='https://github.com/tuyenldhust'>https://github.com/tuyenldhust</a>
        <br>
        <b>Facebook</b>: <a href='https://www.facebook.com/le.tuyen.hust'>https://www.facebook.com/le.tuyen.hust</a>"
        font.family: "Times New Roman"
        font.pointSize: 12
        anchors.top: titleCredit.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 40
      }

      Text{
        id: contentCredit2
        text: "<h3><font color='#148F77'><i>2. Phạm Thị Ánh</i></font></h3>
        <b>Github</b>: <a href='https://github.com/Anhpham2802'>https://github.com/Anhpham2802</a>
        <br>
        <b>Facebook</b>: <a href='https://www.facebook.com/PhamAnh2802'>https://www.facebook.com/PhamAnh2802</a>"
        font.family: "Times New Roman"
        font.pointSize: 12
        anchors.top: contentCredit1.bottom
        anchors.topMargin: 33
        anchors.left: parent.left
        anchors.leftMargin: 40
      }

      Text{
        id: contentCredit3
        text: "<h3><font color='#148F77'><i>3. Hà Văn Đức</i></font></h3>
        <b>Github</b>: <a href='https://github.com/VanDucKun'>https://github.com/VanDucKun</a>
        <br>
        <b>Facebook</b>: <a href='https://www.facebook.com/100024461410153'>https://www.facebook.com/100024461410153</a>"
        font.family: "Times New Roman"
        font.pointSize: 12
        anchors.top: contentCredit2.bottom
        anchors.topMargin: 33
        anchors.left: parent.left
        anchors.leftMargin: 40
      }
    }
  }
}
