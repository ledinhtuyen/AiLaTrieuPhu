import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
    id: changePasswordPage
    title: qsTr("Change Password")
    width: 480
    height: 640

    property string uname: ""
    property string pword: ""
    property bool isShowPassword: false
    property bool isShowPassword2: false

    background: Rectangle {
        color: backGroundColor
    }

    Rectangle {
        id: iconRect2
        width: parent.width
        height: parent.height / 3
        color: backGroundColor

         Text {
             id: icontext2
             text: qsTr("\uf136")
             anchors.centerIn: parent
             font.pointSize: 112
             font.family: "fontawesome"
             color: mainAppColor
         }
    }

    ColumnLayout {
        width: parent.width
        anchors.top: iconRect2.bottom
        spacing: 25

        Text {
          id: changePasswordText
          text: qsTr("Đổi mật khẩu")
          font.pointSize: 24
          Layout.alignment: Qt.AlignHCenter
          color: mainTextColor
        }

        TextField {
            id: changePassword
            placeholderText: qsTr("Mật khẩu mới")
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
            id: changePassword2
            placeholderText: qsTr("Nhập lại mật khẩu mới")
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

        Item {
            height: 20
        }

        CButton{
            height: 50
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Đổi mật khẩu"
            baseColor: mainAppColor
            borderColor: mainAppColor
            onClick: {
                if(changePassword.text == "" || changePassword2.text == ""){
                    notifyErrPopup.popMessage = "Vui lòng điền đầy đủ các trường"
                    notifyErrPopup.open()
                }
                else if (changePassword.text != changePassword2.text) {
                    notifyErrPopup.popMessage = "Mât khẩu không khớp"
                    notifyErrPopup.open()
                }
                else {
                    waitPopup.popMessage = "Đang đổi mật khẩu ..."
                    act = "changepassword"
                    waitPopup.open()
                    backEnd.changePassword(changePassword.text)
                }
            }
                
        }

        CButton{
            height: 50
            Layout.preferredWidth: parent.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Hủy"
            baseColor: "transparent"
            borderColor: mainAppColor
            onClick: 
            {
              stackView.pop()
              menuMain.resetToDefaultProperties()
            }
        }
    }
}
