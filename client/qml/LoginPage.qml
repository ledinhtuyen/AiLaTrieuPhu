import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.3

Page {
    id: loginPage
    title: "Login"
    width: 480
    height: 640

    property bool isShowPassword: false
    

    background: Rectangle {
        color: backGroundColor
    }

    // BorderImage {
    //     id: backgroundImg
    //     anchors.fill: parent
    //     source: "../assets/wallpaper.jpg"
    // }

    Rectangle {
        id: iconRect
        width: parent.width
        height: parent.height / 3
        color: backGroundColor

         Text {
             id: icontext
             text: qsTr("\uf169")
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
        source: "../assets/back_icon.png"
        fillMode: Image.PreserveAspectFit

        HoverHandler{
            onHoveredChanged: {
                if (hovered)
                {
                    backIcon.source = "../assets/back_icon_hover.png"
                }
                else
                {
                    backIcon.source = "../assets/back_icon.png"
                }
            }
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.pop()
            }
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.top: iconRect.bottom
        spacing: 15

        TextField {
            id: loginUsername
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
            id: loginPassword
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

        Item {
            height: 20
        }

        CButton{
            height: 50
            Layout.preferredWidth: loginPage.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Log In"
            baseColor: mainAppColor
            borderColor: mainAppColor
            // onClicked: {
            //     loginUser(loginUsername.text, loginPassword.text)
            // }
        }

        CButton{
            height: 50
            Layout.preferredWidth: loginPage.width - 20
            Layout.alignment: Qt.AlignHCenter
            name: "Sign Up"
            baseColor: "transparent"
            borderColor: mainAppColor
            onClicked: stackView.push("qrc:/qml/SignUpPage.qml", {"uname": "arun", "pword": "some"}) //registerClicked()
        }
    }
}
