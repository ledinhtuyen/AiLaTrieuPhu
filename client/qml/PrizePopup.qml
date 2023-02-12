import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Popup {
    id: popup
    width: 480
    height: 640

    property int prize: 0
    property bool runningHighLightPrize: false

    background: Rectangle {
        opacity: 0
        anchors.fill: parent
    }

    contentItem : Item {
        anchors.fill: parent
        Rectangle{
            color: "transparent"
            width: 60
            height: 60

            Image{
                source: applicationDirPath + "/assets/Sprite/btn_back.png"
                anchors.fill: parent
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        clickSound.play()
                        popup.close()
                        menuMain.clickShowPrizeBtn = false
                    }
                }
            }
        }

        Column {
            id : prizeList
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50
            width: 270
            height: 540

            Image{
                id: img15
                source: prize == 15 || prize == 18 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung4.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "<font color='black'>150.000</font>"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img14
                source: prize == 14 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "85.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img13
                source: prize == 13 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "60.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img12
                source: prize == 12 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "40.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img11
                source: prize == 11 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "30.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img10
                source: prize == 10 || prize == 17 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung3.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "<font color='black'>22.000</font>"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img9
                source: prize == 9 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "14.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img8
                source: prize == 8 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "10.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img7
                source: prize == 7 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "6.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img6
                source: prize == 6 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "3.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img5
                source: prize == 5 || prize == 16 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung3.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "<font color='black'>2.000</font>"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img4
                source: prize == 4 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "1.000"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img3
                source: prize == 3 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "600"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img2
                source: prize == 2 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "400"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            Image{
                id: img1
                source: prize == 1 ? applicationDirPath + "/assets/Sprite/khung1.png" : applicationDirPath + "/assets/Sprite/khung2.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 270
                height: 36
                Text{
                    text: "200"
                    color: "white"
                    font.family: "roboto"
                    font.pixelSize: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    Timer{
        id: highLightPrize
        interval: 250
        running: runningHighLightPrize
        repeat: true
        onTriggered: {
            prize++
            if(prize > 18){
                runningHighLightPrize = false
                prizeTheme.stop()
                letsPlayTheme.play()
                popup.close()
                menuMain.sTatus = 2
                menuMain.startBtnAnimUp()
                highLightPrize.stop()
            }
        }
    }

    Timer {
        id : flickerPrizeTimer
        property var count : 0
        interval: 300
        running: false
        repeat: true
        onTriggered : {
            if(count % 2 == 1){
                prize = backEnd.prize + 1
            }
            else {
                prize = 0
            }
            count++
            if(count > 6){
                count = 0
                flickerPrizeTimer.stop()
                popup.close()
                rootWindow.startNewQuestion()
            }
        }
    }

    function flickerPrize(){
        flickerPrizeTimer.start()
    }

    function startHightLightPrize(){
        prize = 0
        runningHighLightPrize = true
        highLightPrize.start()
    }
}
