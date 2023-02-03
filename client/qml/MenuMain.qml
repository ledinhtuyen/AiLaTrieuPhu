import QtQuick 2.0
import QtQuick.Controls 2.12

Page {
  id: menuMain
  width: 480
  height: 640

  SelectButtonPage{
    startY: 640
    textBtn1: "Chơi 1 mình"
    textBtn2: "Thi đấu online"
    textBtn3: "Đổi mật khẩu"
    textBtn4: "Đăng xuất"

    funcBtn3Click: function(){
      stackView.push("ChangePasswordPage.qml")
    }

    funcBtn4Click: function(){
      backEnd.logOut()
      stackView.pop()
    }
  }

  Logo {
    anchors.horizontalCenter: parent.horizontalCenter
  }

  Text {
    id: text
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
}