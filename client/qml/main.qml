import QtQuick 2.12
import QtQuick.Controls 2.5
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
    property color errPopupBackGroundColor: "#b44"
    property color popupTextColor: "#ffffff"
    property string act : "none"
    property bool connectFail : false
    property string loginStatus : "none"
    property string signupStatus : "none"
    property string changePasswordStatus : "none"
    property bool lose : false
    property bool click_change_question : false
    property bool isPlayPvP : false

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

        onAccountBlocked: {
            rootWindow.loginStatus = "ACCOUNT_BLOCKED"
        }
        
        onAccountNotExist: {
            rootWindow.loginStatus = "ACCOUNT_NOT_EXIST"
        }

        onWrongPassword: {
            rootWindow.loginStatus = "WRONG_PASSWORD"
        }

        onSignupSuccess: {
            rootWindow.signupStatus = "SIGNUP_SUCCESS"
        }

        onAccountExist: {
            rootWindow.signupStatus = "ACCOUNT_EXIST"
        }

        onChangePasswordSuccess: {
            rootWindow.changePasswordStatus = "CHANGE_PASSWORD_SUCCESS"
        }

        onSameOldPassword: {
            rootWindow.changePasswordStatus = "SAME_OLD_PASSWORD"
        }

        onCorrectAnswer: {
            finalAnswerSound.stop()
            correctAnswerSound.play()
            flicker.start()
        }

        onLose: {
            rootWindow.lose = true
            finalAnswerSound.stop()
            wrongAnswerSound.play()
            flicker.start()
        }

        onLose2: {
            rootWindow.lose = true
            if (backEnd.prize > 5)
                quest5To15Theme.stop()
            else
                quest1To5Theme.stop()
            menuMain.showResultPopup()
        }

        onFoundPlayer: {
            isPlayPvP = true
            findOpponentPopup.popMessage = "Đã tìm thấy đối thủ"
            delayOpenFoundOpponentPopup.start()
        }

        onOpenVote: {
            menuMain.openVotePopup()
        }

        onOpenCallPhone: {
            menuMain.openCallPhonePopup()
        }

        onNotFoundPlayer: {
            findOpponentPopup.close()
            act = "none"
            notifyErrPopup.popMessage = "Không tìm thấy đối thủ"
            notifyErrPopup.open()
        }

        onShowResultPvP: {
            menuMain.showResultPopup()
        }
    }

    MenuMain {
        id: menuMain
        sTatus: 0
    }

    Component.onCompleted: {
        commericalBreakSound.play()
        stackView.push("MenuStart.qml")
    }

    SoundEffect {
        id : commericalBreakSound
        source: applicationDirPath + "/assets/AudioClip/commerical break.wav"
        volume: 1.0
    }

    SoundEffect{
        id: mainTheme
        source: applicationDirPath + "/assets/AudioClip/main theme.wav"
        volume: 0.5
    }

    SoundEffect {
        id: clickSound
        source: applicationDirPath + "/assets/AudioClip/click.wav"
        volume: 1.0
    }

    SoundEffect {
        id: prizeTheme
        source: applicationDirPath + "/assets/AudioClip/03 Explain The Rules.wav"
        volume: 1.0
    }

    SoundEffect {
        id: letsPlayTheme
        source: applicationDirPath + "/assets/AudioClip/lets play.wav"
        volume: 1.0
    }

    SoundEffect {
        id: quest1To5Theme
        source: applicationDirPath + "/assets/AudioClip/1to5.wav"
        volume: 1.0
        loops: SoundEffect.Infinite
    }

    SoundEffect {
        id: quest5To15Theme
        source: applicationDirPath + "/assets/AudioClip/5to15.wav"
        volume: 1.0
        loops: SoundEffect.Infinite
    }

    SoundEffect {
        id : fiftyFiftySound
        source: applicationDirPath + "/assets/AudioClip/50-50.wav"
        volume: 1.0
    }

    SoundEffect {
        id: finalAnswerSound
        source: applicationDirPath + "/assets/AudioClip/final answer.wav"
        volume: 1.0
    }

    SoundEffect {
        id: correctAnswerSound
        source: applicationDirPath + "/assets/AudioClip/correct answer.wav"
        volume: 1.0
    }

    SoundEffect {
        id: wrongAnswerSound
        source: applicationDirPath + "/assets/AudioClip/wrong answer.wav"
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
        id: notifySuccessPopup
        property alias popMessage: notifySuccessMessage.text

        background: Rectangle {
            implicitWidth: rootWindow.width
            implicitHeight: 60
            color: mainAppColor
        }
        y: (rootWindow.height - 60)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        Text {
            id: notifySuccessMessage
            anchors.centerIn: parent
            font.pointSize: 12
            color: popupTextColor
        }
        onOpened: notifySuccessPopupClose.start()
    }

    Popup {
        id: notifyErrPopup
        property alias popMessage: notifyErrMessage.text

        background: Rectangle {
            implicitWidth: rootWindow.width
            implicitHeight: 60
            color: errPopupBackGroundColor
        }
        y: (rootWindow.height - 60)
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        Text {
            id: notifyErrMessage
            anchors.centerIn: parent
            font.pointSize: 12
            color: popupTextColor
        }
        onOpened: notifyErrPopupClose.start()
    }

    Popup {
        id: waitPopup
        property alias popMessage: message.text

        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose
        modal: true

        background: Image {
            width: 220
            height: 220
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
                width: 220
                anchors.top: busyIndicator.bottom
                anchors.topMargin: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
                font.family: "roboto"
                color: "white"
            }
        }

        onOpened:waitPopupClose.start()
    }

    Popup {
        id: findOpponentPopup
        property alias popMessage: message2.text

        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose
        modal: true

        background: Image {
            width: 220
            height: 220
            anchors.centerIn: parent
            source: applicationDirPath + "/assets/Sprite/popup.png"
                
            BusyIndicator {
                id: busyIndicator2
                running: true
                anchors.centerIn: parent

                contentItem: Item {
                    implicitWidth: 64
                    implicitHeight: 64

                    Item {
                        id: item2
                        x: parent.width / 2 - 32
                        y: parent.height / 2 - 32
                        width: 64
                        height: 64
                        opacity: busyIndicator2.running ? 1 : 0

                        Behavior on opacity {
                            OpacityAnimator {
                                duration: 250
                            }
                        }

                        RotationAnimator {
                            target: item2
                            running: busyIndicator2.visible && busyIndicator2.running
                            from: 0
                            to: 360
                            loops: Animation.Infinite
                            duration: 1250
                        }

                        Repeater {
                            id: repeater2
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
                                        angle: index / repeater2.count * 360
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
                id: message2
                width: 220
                anchors.top: busyIndicator2.bottom
                anchors.topMargin: 20
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
                font.family: "roboto"
                color: "white"
            }
        }
    }

    // Popup will be closed automatically in 2 seconds after its opened
    Timer {
        id: notifySuccessPopupClose
        interval: 2000
        onTriggered: notifySuccessPopup.close()
    }

    Timer {
        id: notifyErrPopupClose
        interval: 2000
        onTriggered: notifyErrPopup.close()
    }

    Timer {
        id: waitPopupClose
        interval: 2000
        onTriggered:{
            waitPopup.close()
            if(act == "connect2server"){
                if (connectFail == true) {
                    notifyErrPopup.popMessage = "Không thể kết nối đến máy chủ"
                    notifyErrPopup.open()
                }
                else if (connectFail == false)
                {
                    stackView.push("LoginPage.qml")
                }
            }
            else if (act == "login"){
                if (loginStatus == "LOGIN_SUCCESS") {
                    backEnd.userNameChanged()
                    stackView.push(menuMain)
                    menuMain.resetToDefaultProperties()
                }
                else if (loginStatus == "LOGGED_IN")
                {
                    notifyErrPopup.popMessage = "Tài khoản đã được đăng nhập ở nơi khác"
                    notifyErrPopup.open()
                }
                else if (loginStatus == "ACCOUNT_BLOCKED")
                {
                    notifyErrPopup.popMessage = "Tài khoản đã bị khóa"
                    notifyErrPopup.open()
                }
                else if (loginStatus == "ACCOUNT_NOT_EXIST")
                {
                    notifyErrPopup.popMessage = "Tài khoản không tồn tại"
                    notifyErrPopup.open()
                }
                else if (loginStatus == "WRONG_PASSWORD")
                {
                    notifyErrPopup.popMessage = "Sai mật khẩu"
                    notifyErrPopup.open()
                }
            }
            else if (act == "signup"){
                if (signupStatus == "SIGNUP_SUCCESS") {
                    notifySuccessPopup.popMessage = "Đăng ký thành công"
                    notifySuccessPopup.open()
                }
                else if (signupStatus == "ACCOUNT_EXIST")
                {
                    notifyErrPopup.popMessage = "Tài khoản đã tồn tại"
                    notifyErrPopup.open()
                }
            } else if (act == "changepassword"){
                if (changePasswordStatus == "CHANGE_PASSWORD_SUCCESS") {
                    notifySuccessPopup.popMessage = "Đổi mật khẩu thành công"
                    notifySuccessPopup.open()
                }
                else if (changePasswordStatus == "SAME_OLD_PASSWORD")
                {
                    notifyErrPopup.popMessage = "Giống mật khẩu cũ"
                    notifyErrPopup.open()
                }
            }
        }
    }

    Timer {
        id : flicker
        property var count : 0
        interval: 200
        running: false
        repeat : true
        onTriggered: {
            menuMain.flickerCorrectAnswer(count)
            count++;
            if (count == 10) {
                count = 0
                flicker.stop()
                if (!rootWindow.lose && backEnd.prize != 15){
                    menuMain.showPrizePopup()
                }
                else if (!rootWindow.lose && backEnd.prize == 15) {
                    correctAnswerSound.stop()
                    mainTheme.play()
                    menuMain.showResultPopup()
                }
                else {
                    menuMain.showResultPopup()
                }
            }
        }
    }

    Timer {
        id: delayOpenFoundOpponentPopup
        interval: 3000
        onTriggered: {
            findOpponentPopup.close()
            menuMain.showFoundOpponentPopup()
        }
    }

    function startNewQuestion() {
        backEnd.prize++
        backEnd.prizeChanged()

        backEnd.questionChanged()
        backEnd.aChanged()
        backEnd.bChanged()
        backEnd.cChanged()
        backEnd.dChanged()

        correctAnswerSound.stop()
        letsPlayTheme.play()

        menuMain.resetBtnToStartY()
        menuMain.startBtnAnimUp()
    }

    function stopCountDown() {
        menuMain.stopCountDown()
    }
}
