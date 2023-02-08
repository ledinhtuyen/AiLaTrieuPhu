import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.3

Page {
    id: loginPage
    title: "Đăng nhập"
    width: 480
    height: 640

    property bool isShowPassword: false
    

    background: Rectangle {
        color: backGroundColor
    }

    Rectangle {
        id: iconRect
        width: parent.width
        height: parent.height / 3
        color: backGroundColor

         Text {
             id: icontext
             text: qsTr("\uf136")
             anchors.centerIn: parent
             font.pointSize: 112
             font.family: "fontawesome"
             color: mainAppColor
         }
    }

    Image {
        id: backIcon
        width: 50
        height: 50
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        source: applicationDirPath + "/assets/Sprite/back_icon.png"
        fillMode: Image.PreserveAspectFit

        HoverHandler{
            onHoveredChanged: {
                if (hovered)
                {
                    backIcon.source = applicationDirPath + "/assets/Sprite/back_icon_hover.png"
                }
                else
                {
                    backIcon.source = applicationDirPath + "/assets/Sprite/back_icon.png"
                }
            }
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                clickSound.play()
                backEnd.disconnectToServer()
                stackView.pop()
                stackView.replace("MenuStart.qml")
            }
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.top: iconRect.bottom
        spacing: 15

        TextField {
            id: loginUsername
            placeholderText: qsTr("Tên đăng nhập")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextColor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Text {
                    text: "\uf007"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        TextField {
            id: loginPassword
            placeholderText: qsTr("Mật khẩu")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextColor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            echoMode: isShowPassword ? TextField.Normal : TextField.Password
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"
                Text {
                    text: "\uf023"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 10
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }

                Text {
                    id: showPasswordIcon
                    visible: false
                    text: "\uf06e"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    rightPadding: 10

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            showPasswordIcon.visible = false
                            hidePasswordIcon.visible = true
                            isShowPassword = true
                        }
                    }
                }

                Text {
                    id: hidePasswordIcon
                    visible: false
                    text: "\uf070"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    rightPadding: 10

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            hidePasswordIcon.visible = false
                            showPasswordIcon.visible = true
                            isShowPassword = false
                        }
                    }
                }
            }

            onTextChanged: {
                if (text.length > 0) {
                    showPasswordIcon.visible = !isShowPassword
                    hidePasswordIcon.visible = isShowPassword
                }
                else {
                    showPasswordIcon.visible = false
                    hidePasswordIcon.visible = false
                }
            }
        }

        Item {
            height: 20
        }

        CButton{
            height: 50
            Layout.preferredWidth: loginPage.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Đăng nhập"
            baseColor: mainAppColor
            borderColor: mainAppColor
            onClick: {
                if (loginUsername.text == "" || loginPassword.text == "") {
                    notifyErrPopup.popMessage = "Vui lòng nhập đầy đủ thông tin"
                    notifyErrPopup.open()
                }
                else {
                    waitPopup.popMessage = "Đang đăng nhập ..."
                    waitPopup.open()
                    act = "login"
                    backEnd.signIn(loginUsername.text, loginPassword.text)
                }
            }
        }

        CButton{
            height: 50
            Layout.preferredWidth: loginPage.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Đăng ký"
            baseColor: "transparent"
            borderColor: mainAppColor
            onClick:{
                stackView.push("qrc:/qml/SignUpPage.qml")
            }
        }
    }
}
