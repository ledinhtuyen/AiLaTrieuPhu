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
    Image{
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.verticalCenter: parent.verticalCenter
      source: applicationDirPath + "/assets/Sprite/popup_75.png"
      width: 400
      height: 200

      Column{
        Text {
          width: 400
          height: 40
        }
        Text {
          width: 400
          text: backEnd.user_name
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          font.pixelSize: 30
          font.family: "roboto"
          color: "white"
        }
        Item {
          width: 400
          height: 15
        }
        Text {
          width: 400
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          text: "VS"
          font.pixelSize: 17
          font.family: "roboto"
          color: "red"
        }
        Item {
          width: 400
          height: 15
        }
        Text {
          width: 400
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          text: backEnd.enemy_name
          font.pixelSize: 30
          font.family: "roboto"
          color: "white"
        }
      }
    }
  }
}