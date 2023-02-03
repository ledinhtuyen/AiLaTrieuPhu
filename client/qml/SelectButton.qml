import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
  id : button
  width: 480
  height: 50
  enabled: false

  contentItem: Text {
    font.bold: true
    font.pointSize: 17
    font.family: "roboto"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    color: "white"
    text : button.text
  }

  background: Image {
    source: applicationDirPath + "/assets/Sprite/btn.png"
    opacity: 0.5
  }

  onHoveredChanged: {
    if (button.hovered)
    {
        background.source = applicationDirPath + "/assets/Sprite/btn_choose.png"
    }
    else {
        background.source = applicationDirPath + "/assets/Sprite/btn.png"
    }
  }
}