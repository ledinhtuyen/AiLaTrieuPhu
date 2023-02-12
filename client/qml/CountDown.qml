import QtQuick 2.12

Item {
    width: 76
    height: 76

    property int angle: 0
    property int radius: 30
    property bool stopped: false

    Timer {
        id: timer
        interval: 1000
        repeat : true
        running: false
        onTriggered: {
            if (!stopped) {
                angle += 24
                menuMain.time -= 1
                canvas.requestPaint()
                if (time <= 0){
                    stopped = true
                    timer.stop()
                    backEnd.overTime()
                    backEnd.lose2()
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
        text: menuMain.time
        font.pointSize: 20
        font.family : "roboto"
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.centerIn: parent
    }

    function start() {
        stopped = false
        angle = 0
        menuMain.time = 15
        canvas.requestPaint()
        timer.start()
    }

    function stop() {
        stopped = true
        timer.stop()
    }

    function continueCountDown() {
        stopped = false
        timer.start()
    }
}

