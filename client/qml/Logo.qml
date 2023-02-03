import QtQuick 2.0
import QtQuick.Controls 2.12

Item{
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
}