import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Popup {
  width: 480
  height: 640

  background: Rectangle {
    opacity: 0.5
    color: "gray"
    anchors.fill: parent
  }

  contentItem : Item {
      anchors.horizontalCenter: parent.horizontalCenter
      Image{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 100
        source: applicationDirPath + "/assets/Sprite/popup_91.png"
        width: 400
        height: 400

        Text {
          width: 400
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.top: parent.top
          anchors.topMargin: 70
          text: (backEnd.status_game == 24 ? "Bạn đã thua " : "Bạn đã thắng ") + (rootWindow.isPlayPvP ? backEnd.enemy_name : "")
          font.pixelSize: 30
          font.family: "roboto"
          font.bold: true
          color: "white"
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }

        Image{
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.verticalCenter: parent.verticalCenter
          source: applicationDirPath + (backEnd.status_game == 24 ? "/assets/Sprite/banggiaithuong_thua.png" : "/assets/Sprite/khung4.png")
          width: 320
          height: 50

          Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            text: backEnd.reward
            font.pixelSize: 23
            font.family: "roboto"
          }
        }
        SelectButton{
          width: 350
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.bottom: parent.bottom
          anchors.bottomMargin: 70
          text: "Trang chủ"
          onClick: {
            mainTheme.stop()
            close()
            menuMain.resetToDefaultProperties()
          }
        }
      }
  }
}