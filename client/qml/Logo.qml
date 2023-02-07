import QtQuick 2.12
import QtQuick.Controls 2.5

Item{
  Image {
    id: image
    width: 220
    height: 220
    anchors.top: parent.top
    anchors.topMargin: 40
    anchors.horizontalCenter: parent.horizontalCenter
    fillMode: Image.PreserveAspectFit
    source: applicationDirPath + "/assets/Sprite/2.png"
  }

  Image {
    id: image2
    width: 350
    height: 220
    anchors.top: parent.top
    anchors.topMargin: 40
    anchors.horizontalCenter: parent.horizontalCenter
    fillMode: Image.PreserveAspectFit
    source: applicationDirPath + "/assets/Sprite/1.png"
    }

  Text {
    id: text
    width: 220
    height: 50
    anchors.top: parent.top
    anchors.topMargin: 125
    anchors.horizontalCenter: parent.horizontalCenter
    font.bold: true
    font.pointSize: 20
    font.family: "roboto"
    text: qsTr("Ai Là Triệu Phú")
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    color: "white"
  }
}