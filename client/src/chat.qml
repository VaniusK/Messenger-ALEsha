import QtQuick

Rectangle {
    id: root
    color: "#f0f2f5"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "It's a chat's box!"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Welcome to Alyosha Messenger!"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "You have successfully logged in!"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: 120
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
                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_in.qml"
                    }
                }
            }
        }
    }
}
