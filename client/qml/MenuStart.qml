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
    source: "../assets/wallpaper.jpg"
  }

  Image {
    id: image
    width: 250
    height: 250
    anchors.top: parent.top
    anchors.topMargin: 50
    anchors.horizontalCenter: parent.horizontalCenter
    fillMode: Image.PreserveAspectFit
    source: "../assets/logo.png"
  }

  Button {
    id: startBtn
    width: 160
    height: 50
    anchors.top: image.bottom
    anchors.topMargin: 50
    anchors.horizontalCenter: parent.horizontalCenter

    contentItem: Text {
      font.bold: true
      font.italic: true
      font.pointSize: 13
      font.family: "Times New Roman"
      text: qsTr("Bắt đầu")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }

    background: Rectangle {
      color: "#191919"
    }

    onClicked: {
      // stackView.push("LoginPage.qml")
      waitPopup.popMessage = "Connecting to server..."
      waitPopup.open()
      act = "connect2server"
      backEnd.connectToServer()
    }

    onHoveredChanged: {
      if (startBtn.hovered)
      {
        startBtn.background.color = "#6B728E"
      }
      else {
        startBtn.background.color = "#191919"
      }
    }

  }

  Button {
    id: guideBtn
    width: 160
    height: 50
    contentItem: Text {
      font.bold: true
      font.italic: true
      font.pointSize: 13
      font.family: "Times New Roman"
      text: qsTr("Cách chơi")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }
    anchors.top: startBtn.bottom
    anchors.topMargin: 15
    anchors.horizontalCenter: parent.horizontalCenter

    background: Rectangle {
      color: "#191919"
    }

    onClicked: {
      guideDialog.visible = true
    }

    onHoveredChanged: {
      if (guideBtn.hovered)
      {
        guideBtn.background.color = "#6B728E"
      }
      else
      {
        guideBtn.background.color = "#191919"
      }
    }
  }

  Button {
    id: creditBtn
    width: 160
    height: 50
    highlighted: true
    contentItem: Text {
      font.bold: true
      font.italic: true
      font.pointSize: 13
      font.family: "Times New Roman"
      text: qsTr("Giới thiệu")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }
    anchors.top: guideBtn.bottom
    anchors.topMargin: 15
    anchors.horizontalCenter: parent.horizontalCenter

    background: Rectangle {
      color: "#191919"
    }

    onClicked: {
      creditDialog.visible = true
    }

    onHoveredChanged: {
      if (creditBtn.hovered)
      {
        creditBtn.background.color = "#6B728E"
      }
      else {
        creditBtn.background.color = "#191919"
      }
    }
  }

  Button {
    id: quitBtn
    width: 160
    height: 50
    contentItem: Text {
      font.bold: true
      font.italic: true
      font.pointSize: 13
      font.family: "Times New Roman"
      text: qsTr("Thoát")
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "white"
    }
    anchors.top: creditBtn.bottom
    anchors.topMargin: 15
    anchors.horizontalCenter: parent.horizontalCenter

    background: Rectangle {
      color: "#191919"
    }

    onClicked: {
      Qt.quit()
    }

    onHoveredChanged: {
      if (quitBtn.hovered)
      {
        quitBtn.background.color = "#6B728E"
      }
      else
      {
        quitBtn.background.color = "#191919"
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
        <b>Facebook</b>: <a href='https://www.facebook.com/Phâmnh2802'>https://www.facebook.com/PhamAnh2802</a>"
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
