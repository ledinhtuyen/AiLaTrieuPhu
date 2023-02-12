import QtQuick 2.12
import QtQuick.Controls 2.5

  Popup {
    id : vote
    modal : true
    width: 480
    height: 640

    property bool isShow: false

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
              Rectangle {
                id : tileA
                width: 30
                height: heightValue1
                visible: vote.isShow
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.left: parent.left
                anchors.leftMargin: 60

                property int heightValue1: 0
                Image {
                    source: applicationDirPath + "/assets/Sprite/cot_tile_.png"
                    width: parent.width
                    height: parent.height
                    
                    Text {
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 20
                      font.family: "roboto"
                      color: "white"
                      text: "A"
                    }

                    Text {
                      anchors.top: parent.top
                      anchors.topMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 17
                      font.family: "roboto"
                      color: "white"
                      text: parent.parent.heightValue1 + "%"
                    }
                }
                Timer{
                  id : runTileVote1
                  interval: 50
                  running: vote.isShow
                  repeat: true
                  onTriggered: {
                    if (parent.heightValue1 < backEnd.voteA) {
                      parent.heightValue1 += 1
                    }
                    else {
                      runTileVote1.stop()
                    }
                  }
                }
              }
              Rectangle {
                id : tileB
                width: 30
                height: heightValue2
                visible: vote.isShow
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.left: tileA.right
                anchors.leftMargin: 50

                property int heightValue2: 0
                Image {
                    source: applicationDirPath + "/assets/Sprite/cot_tile_.png"
                    width: parent.width
                    height: parent.height

                    Text {
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 20
                      font.family: "roboto"
                      color: "white"
                      text: "B"
                    }

                    Text {
                      anchors.top: parent.top
                      anchors.topMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 17
                      font.family: "roboto"
                      color: "white"
                      text: parent.parent.heightValue2 + "%"
                    }
                }
                Timer{
                  id : runTileVote2
                  interval: 50
                  running: vote.isShow
                  repeat: true
                  onTriggered: {
                    if (parent.heightValue2 < backEnd.voteB) {
                      parent.heightValue2 += 1
                    }
                    else {
                      runTileVote2.stop()
                    }
                  }
                }
              }
              Rectangle {
                id : tileC
                width: 30
                height: heightValue3
                visible: vote.isShow
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.left: tileB.right
                anchors.leftMargin: 50

                property int heightValue3: 0
                Image {
                    source: applicationDirPath + "/assets/Sprite/cot_tile_.png"
                    width: parent.width
                    height: parent.height

                    Text {
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 20
                      font.family: "roboto"
                      color: "white"
                      text: "C"
                    }

                    Text {
                      anchors.top: parent.top
                      anchors.topMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 17
                      font.family: "roboto"
                      color: "white"
                      text: parent.parent.heightValue3 + "%"
                    }
                }
                Timer{
                  id : runTileVote3
                  interval: 50
                  running: vote.isShow
                  repeat: true
                  onTriggered: {
                    if (parent.heightValue3 < backEnd.voteC) {
                      parent.heightValue3 += 1
                    }
                    else {
                      runTileVote3.stop()
                    }
                  }
                }
              }
              Rectangle {
                id : tileD
                width: 30
                height: heightValue4
                visible: vote.isShow
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 50
                anchors.left: tileC.right
                anchors.leftMargin: 50

                property int heightValue4: 0
                Image {
                    source: applicationDirPath + "/assets/Sprite/cot_tile_.png"
                    width: parent.width
                    height: parent.height

                    Text {
                      anchors.bottom: parent.bottom
                      anchors.bottomMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 20
                      font.family: "roboto"
                      color: "white"
                      text: "D"
                    }

                    Text {
                      anchors.top: parent.top
                      anchors.topMargin: -25
                      anchors.horizontalCenter: parent.horizontalCenter
                      font.pixelSize: 17
                      font.family: "roboto"
                      color: "white"
                      text: parent.parent.heightValue4 + "%"
                    }
                }
                Timer{
                  id : runTileVote4
                  interval: 50
                  running: vote.isShow
                  repeat: true
                  onTriggered: {
                    if (parent.heightValue4 < backEnd.voteD) {
                      parent.heightValue4 += 1
                    }
                    else {
                      runTileVote4.stop()
                    }
                  }
                }
              }
          }
          Item {
            width: 480
            height: 20
          }
          SelectButton{
            text: "Đóng"
            onClick: {
              vote.close()
            }
          }
        }
    }
  }