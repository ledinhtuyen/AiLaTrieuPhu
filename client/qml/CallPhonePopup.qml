import QtQuick 2.12
import QtQuick.Controls 2.12

Popup {
  id : callPhonePopup
  width: 480
  height: 640

  background: Rectangle {
    opacity: 0.4
    color: "gray"
    anchors.fill: parent
  }

  contentItem : Item {
    Column {
      anchors.horizontalCenter: parent.horizontalCenter
      Item{
        width: 480
        height: 120
      }
      Image{
        anchors.horizontalCenter: parent.horizontalCenter
        source: applicationDirPath + "/assets/Sprite/popup_75.png"
        width: 400
        height: 200

        Text {
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.verticalCenter: parent.verticalCenter
          text: "Tôi đoán đáp án đúng là " + backEnd.call_phone_answer
          font.pixelSize: 23
          font.family: "roboto"
          color: "white"
        }
      }
      Item {
        width: 480
        height: 20
      }
      SelectButton{
        text: "Đóng"
        onClick: {
          callPhonePopup.close()
        }
      }
    }
  }
}