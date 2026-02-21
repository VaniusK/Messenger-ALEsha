import QtQuick
import Messenger 1.0

Rectangle {
    id: root
    color: "#f0f2f5"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Welcome to Alyosha Messenger, " + AppState.currentUserHandle + "!"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Your token:\n" + AppState.token
            font.pixelSize: 12
            color: "gray"
            width: 300
            wrapMode: Text.WrapAnywhere
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: 200
            height: 40
            color: "#dc3545"
            radius: 4
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: "Log Out"
                color: "white"
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("[Chat] Log Out clicked. Navigating to Login screen.")
                    AppState.clearState()

                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_in.qml"
                    }
                }
            }
        }
    }
}
