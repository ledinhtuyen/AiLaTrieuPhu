import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Popup {
  width: 480
  height: 640

  background: Rectangle {
    opacity: 0
    anchors.fill: parent
  }

  contentItem : Item {
    Column {
      anchors.horizontalCenter: parent.horizontalCenter
      Item{
        width: 480
        height: 70
      }
      Image{
        anchors.horizontalCenter: parent.horizontalCenter
        source: applicationDirPath + "/assets/Sprite/popup#75.png"
        width: 400
        height: 200
      }
      Item {
        width: 480
        height: 20
      }
      SelectButton{
        text: "Đồng ý"
        isEnabled: true
        onClick: {
          console.log("Đồng ý");
        }
      }
      Item {
        width: 480
        height: 20
      }
      SelectButton{
        text: "Hủy"
        isEnabled: true
        onClick: {
          console.log("Hủy");
        }
      }
    }
  }
}