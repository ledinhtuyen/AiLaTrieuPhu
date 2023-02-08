import QtQuick 2.12

Item {
    width: 76
    height: 76

    property int angle: 0
    property int radius: 30
    property int time: 30
    property bool stopped: false
    property bool isRunning: false

    Timer {
        id: timer
        interval: 1000
        repeat : true
        running: isRunning
        onTriggered: {
            if (!stopped) {
                angle += 12
                time -= 1
                canvas.requestPaint()
                if (time <= 0){
                    stopped = true
                    timer.stop()
                }
            }
        }
    }

    Canvas {
        id: canvas
        rotation: -90
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");

            ctx.clearRect(0, 0, width, height);
            ctx.beginPath();
            ctx.arc(width/2, height/2, radius, 0, (360 - angle) * Math.PI/180, false);
            ctx.lineWidth = 8;
            ctx.strokeStyle = "#3eefff";
            ctx.stroke();
        }
    }

    Text {
        id: timeLabel
        text: time
        font.pointSize: 20
        font.family : "roboto"
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }
}

