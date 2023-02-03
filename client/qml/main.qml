import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtMultimedia 5.12
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

    Component.onCompleted: {
        mainTheme.play()
        stackView.push("MenuStart.qml")
    }

    SoundEffect{
        id: mainTheme
        source: applicationDirPath + "/assets/AudioClip/main theme.wav"
        loops: SoundEffect.Infinite
        volume: 0.5
    }

    SoundEffect {
        id: clickSound
        source: applicationDirPath + "/assets/AudioClip/click.wav"
        volume: 1.0
    }

    FontLoader {
        id: fontAwesome
        name: "fontawesome"
        source: applicationDirPath + "/assets/Font/fontawesome-webfont.ttf"
    }

    FontLoader {
        id: roboto
        name: "roboto"
        source: applicationDirPath + "/assets/Font/Roboto-Black.ttf"
    }

    StackView{
        id: stackView
        anchors.fill: parent
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

        background: Image {
            width: 200
            height: 200
            anchors.centerIn: parent
            source: applicationDirPath + "/assets/Sprite/popup.png"
            
            BusyIndicator {
                id: busyIndicator
                running: true
                anchors.centerIn: parent

                contentItem: Item {
                    implicitWidth: 64
                    implicitHeight: 64

                    Item {
                        id: item
                        x: parent.width / 2 - 32
                        y: parent.height / 2 - 32
                        width: 64
                        height: 64
                        opacity: busyIndicator.running ? 1 : 0

                        Behavior on opacity {
                            OpacityAnimator {
                                duration: 250
                            }
                        }

                        RotationAnimator {
                            target: item
                            running: busyIndicator.visible && busyIndicator.running
                            from: 0
                            to: 360
                            loops: Animation.Infinite
                            duration: 1250
                        }

                        Repeater {
                            id: repeater
                            model: 6

                            Rectangle {
                                x: item.width / 2 - width / 2
                                y: item.height / 2 - height / 2
                                implicitWidth: 10
                                implicitHeight: 10
                                radius: 5
                                color: "white"
                                transform: [
                                    Translate {
                                        y: -Math.min(item.width, item.height) * 0.5 + 5
                                    },
                                    Rotation {
                                        angle: index / repeater.count * 360
                                        origin.x: 5
                                        origin.y: 5
                                    }
                                ]
                            }
                        }
                    }
                }
            }

            Text {
                id: message
                width: 200
                anchors.top: busyIndicator.bottom
                anchors.topMargin: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
                font.family: "roboto"
                color: "white"
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
                    stackView.push("MenuMain.qml")
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
