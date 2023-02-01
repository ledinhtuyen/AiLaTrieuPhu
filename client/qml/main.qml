import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import AiLaTrieuPhu.BackEnd 1.0

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
    property string act : "none"
    property bool connectFail : false
    property string loginStatus : "none"
    property string signupStatus : "none"


    BackEnd{
        id: backEnd

        onConnectSuccess: {
            rootWindow.connectFail = false
        }

        onConnectFail: {
            rootWindow.connectFail = true
        }

        onLoginSuccess: {
            rootWindow.loginStatus = "LOGIN_SUCCESS"
        }

        onLoggedIn: {
            rootWindow.loginStatus = "LOGGED_IN"
        }

        onLoginFail: {
            rootWindow.loginStatus = "LOGIN_FAIL"
        }

        onSignupSuccess: {
            rootWindow.signupStatus = "SIGNUP_SUCCESS"
        }

        onAccountExist: {
            rootWindow.signupStatus = "ACCOUNT_EXIST"
        }
    }

    FontLoader {
        id: fontAwesome
        name: "fontawesome"
        source: applicationDirPath + "/assets/Font/fontawesome-webfont.ttf"
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
            if(act == "connect2server"){
                if (connectFail == true) {
                    notifyPopup.popMessage = "Không thể kết nối đến máy chủ"
                    notifyPopup.open()
                }
                else if (connectFail == false)
                {
                    stackView.push("LoginPage.qml")
                }
            }
            else if (act == "login"){
                if (loginStatus == "LOGIN_SUCCESS") {
                    console.log("Login success")
                }
                else if (loginStatus == "LOGGED_IN")
                {
                    notifyPopup.popMessage = "Tài khoản đã được đăng nhập ở nơi khác"
                    notifyPopup.open()
                }
                else if (loginStatus == "LOGIN_FAIL")
                {
                    notifyPopup.popMessage = "Sai tên đăng nhập hoặc mật khẩu"
                    notifyPopup.open()
                }
            }
            else if (act == "signup"){
                if (signupStatus == "SIGNUP_SUCCESS") {
                    notifyPopup.popMessage = "Đăng ký thành công"
                    notifyPopup.open()
                }
                else if (signupStatus == "ACCOUNT_EXIST")
                {
                    notifyPopup.popMessage = "Tài khoản đã tồn tại"
                    notifyPopup.open()
                }
            }
        }
    }
}
