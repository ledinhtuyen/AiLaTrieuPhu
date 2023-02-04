import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 480
    height: 640
    opacity: 0
    Rectangle {
        anchors.fill: parent
        color: "white"
        opacity: 0
    }

    Label {
        anchors.centerIn: parent
        text: "This is a transparent page"
        font.pointSize: 24
        font.bold: true
        color: "black"
    }
}
