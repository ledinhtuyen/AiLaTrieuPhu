import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Popup {
  width: 480
  height: 640

  background: Rectangle {
    opacity: 0.4
    color: "gray"
    anchors.fill: parent
  }

  contentItem : Item {
    anchors.horizontalCenter: parent.horizontalCenter
    Image{
      anchors.horizontalCenter: parent.horizontalCenter
      source: applicationDirPath + "/assets/Sprite/popup_75.png"
      width: 400
      height: 200

      Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: "Đã tìm thấy đối thủ"
        font.pixelSize: 23
        font.family: "roboto"
        color: "white"
      }
    }
  }
}