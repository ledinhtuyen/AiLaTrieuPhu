import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: rootWindow
    visible: true
    width: 480
    height: 640
    maximumWidth: 480
    maximumHeight: 640
    minimumWidth: 480
    minimumHeight: 640
    title: qsTr("Ai Là Triệu Phú")

    screen: Qt.application.screens[0]
    x: screen.virtualX + ((screen.width - width) / 2)
    y: screen.virtualY + ((screen.height - height) / 2)

    property color backGroundColor : "#394454"
    property color mainAppColor: "#6fda9c"
    property color mainTextColor: "#f0f0f0"
    property color popupBackGroundColor: "#b44"
    property color popupTextColor: "#ffffff"

    FontLoader {
        id: fontAwesome
        name: "fontawesome"
        source: "../assets/fontawesome-webfont.ttf"
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: MenuStart {}
    }

    Popup {
    id: notifyPopup
    property alias popMessage: notifyMessage.text

        background: Rectangle {
            implicitWidth: rootWindow.width
            implicitHeight: 60
            color: popupBackGroundColor
        }
        y: (rootWindow.height - 60)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        Text {
            id: notifyMessage
            anchors.centerIn: parent
            font.pointSize: 12
            color: popupTextColor
        }
        onOpened: notifyPopupClose.start()
    }

    Popup {
        id: waitPopup
        property alias popMessage: message.text

        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose
        modal: true

        background: Rectangle {
            implicitWidth: 180
            implicitHeight: 180
            color: "#E7F6F2"
            border.color: "#2C3333"
            
            BusyIndicator {
                id: busyIndicator
                running: true
                anchors.centerIn: parent
            }
            Text {
                id: message
                width: 180
                anchors.top: busyIndicator.bottom
                anchors.topMargin: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
            }
        }

        onOpened: waitPopupClose.start()
    }

    // Popup will be closed automatically in 2 seconds after its opened
    Timer {
        id: notifyPopupClose
        interval: 2000
        onTriggered: notifyPopup.close()
    }

    Timer {
        id: waitPopupClose
        interval: 2000
        onTriggered:{
            waitPopup.close()
            // notifyPopup.popMessage = "Đã có lỗi xảy ra, vui lòng thử lại sau"
            // notifyPopup.open()
            stackView.push("LoginPage.qml")
        }
    }
}
