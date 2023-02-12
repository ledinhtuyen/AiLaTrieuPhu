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
          text: "Bạn có muốn dừng lại không?"
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
        text: "Đồng ý"
        onClick: {
          close()
          mainTheme.play()
          backEnd.lose2()
          backEnd.stopGame()
        }
      }
      Item {
        width: 480
        height: 20
      }
      SelectButton{
        text: "Hủy"
        onClick: {
          close()
          gameScreen.continueCountDown()
        }
      }
    }
  }
}