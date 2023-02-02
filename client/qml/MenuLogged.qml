import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height: 400
    color: "black"
    
    Button {
        width: 100
        height: 100
        text: "Click me"
        background : Rectangle {
            color: "red"
            radius: 50
        }

        NumberAnimation on y {
            to: 300
            duration: 1000
        }
    }

    Button {
        width: 100
        height: 100
        text: "Click"
        background : Rectangle {
            color: "red"
            radius: 50
        }

        NumberAnimation on y {
            to: 100
            duration: 700
        }
    }
}
