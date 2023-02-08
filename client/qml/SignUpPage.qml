import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.1

Page {
    id: signUpPage
    title: qsTr("Đăng ký")
    width: 480
    height: 640

    property string uname: ""
    property string pword: ""
    property bool isShowPassword: false
    property bool isShowPassword2: false

    background: Rectangle {
        color: backGroundColor
    }

    Text {
        id: signupText
        text: qsTr("Đăng ký")
        font.pointSize: 24
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        color: mainTextColor
    }

    ColumnLayout {
        width: parent.width
        anchors.top: signupText.bottom
        anchors.topMargin: 30
        spacing: 25

        TextField {
            id: registerUsername
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
            id: registerPassword
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

        TextField {
            id: registerPassword2
            placeholderText: qsTr("Nhập lại mật khẩu")
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            color: mainTextColor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 30
            echoMode: isShowPassword2 ? TextField.Normal : TextField.Password
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
                    id: showPasswordIcon2
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
                            showPasswordIcon2.visible = false
                            hidePasswordIcon2.visible = true
                            isShowPassword2 = true
                        }
                    }
                }

                Text {
                    id: hidePasswordIcon2
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
                            hidePasswordIcon2.visible = false
                            showPasswordIcon2.visible = true
                            isShowPassword2 = false
                        }
                    }
                }
            }

            onTextChanged: {
                if (text.length > 0) {
                    showPasswordIcon2.visible = !isShowPassword2
                    hidePasswordIcon2.visible = isShowPassword2
                }
                else {
                    showPasswordIcon2.visible = false
                    hidePasswordIcon2.visible = false
                }
            }
        }

        TextField {
            id: passwordHint
            placeholderText: qsTr("Gợi ý mật khẩu")
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
                    text: "\uf05a"
                    font.pointSize: 13
                    font.bold: true
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

        Item {
            height: 20
        }

        CButton{
            height: 50
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Đăng ký"
            baseColor: mainAppColor
            borderColor: mainAppColor
            onClick: {
                if(registerUsername.text == "" || registerPassword.text == "" || registerPassword2.text == "" || passwordHint.text == ""){
                    notifyErrPopup.popMessage = "Vui lòng điền đầy đủ thông tin"
                    notifyErrPopup.open()
                }
                else if (registerPassword.text != registerPassword2.text) {
                    notifyErrPopup.popMessage = "Mật khẩu không khớp"
                    notifyErrPopup.open()
                }
                else {
                    waitPopup.popMessage = "Đang đăng ký ..."
                    act = "signup"
                    waitPopup.open()
                    backEnd.signUp(registerUsername.text, registerPassword.text)
                }
            }
                
        }

        CButton{
            height: 50
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Đăng nhập"
            baseColor: "transparent"
            borderColor: mainAppColor
            onClick: stackView.pop()
        }
    }
}
