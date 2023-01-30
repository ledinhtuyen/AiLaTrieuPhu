import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

Page {
    id: signUpPage
    title: qsTr("Sign Up")
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
        text: qsTr("Sign Up")
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
            placeholderText: qsTr("User name")
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
            placeholderText: qsTr("Password")
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
            placeholderText: qsTr("Confirm Password")
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
            placeholderText: qsTr("Password Hint")
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
            name: "Sign Up"
            baseColor: mainAppColor
            borderColor: mainAppColor
            onClicked: {
                if(registerUsername.text == "" || registerPassword.text == "" || registerPassword2.text == "" || passwordHint.text == ""){
                    notifyPopup.popMessage = "Please fill in all fields"
                    notifyPopup.open()
                }
                else if (registerPassword.text != registerPassword2.text) {
                    notifyPopup.popMessage = "Passwords do not match"
                    notifyPopup.open()
                }
                else {
                    waitPopup.popMessage = "Signing up..."
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
            name: "Cancel"
            baseColor: "transparent"
            borderColor: mainAppColor
            onClicked: stackView.pop()
        }
    }
}
