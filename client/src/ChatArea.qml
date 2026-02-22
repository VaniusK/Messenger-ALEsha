import QtQuick
import QtQuick.Layouts
import Messenger 1.0

Rectangle {
    id:chatAreaRoot
    color: "#e5ddd5"

    signal logoutRequested()

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            height: 95
            color: "#f5f5f5"
            border.color: "#e0e0e0"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 15

                Rectangle {
                    width: 40
                    height: 40
                    radius: 20
                    color: "#007bff"
                    
                    Text {
                        text: "C"
                        color: "white"
                        font.bold: true
                        anchors.centerIn: parent
                    }
                }

                Column {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignVCenter
                        
                    Text {
                        text: "Собеседник "
                        font.bold: true
                        font.pixelSize: 16
                    }

                    Text {
                        text: "В сети"
                        color: "#007bff"
                        font.pixelSize: 12
                    }
                }

                Rectangle {
                    width: 100
                    height: 36
                    radius: 18
                    color: "#dc3545"

                    Text { 
                        text: "LogOut"
                        color: "white"
                        font.bold: true
                        anchors.centerIn: parent
                    }

                    MouseArea { 
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: chatAreaRoot.logoutRequested()
                    }
                }
            }
        }

        ListView {
            id: messageList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: 15
            spacing: 10

            topMargin: 15
            bottomMargin: 15

            delegate: Rectangle {
                property bool isMe: index % 2 == 0

                width: Math.min(300, messageList.width * 0.7)
                height: Math.max(40, messageText.contentHeight + 20)
                radius: 12
                color: isMe ? "#dcf8c6" : "#ffffff"

                anchors.right: isMe ? parent.right : undefined
                anchors.left: isMe ? undefined : parent.left
                anchors.rightMargin: isMe ? 20 : 0
                anchors.leftMargin: isMe ? 0 : 20

                Text {
                    id: messageText
                    text: isMe ? "Это мое сообщение " + index : "А это ответ настоящего собеседника " + index
                    anchors.fill: parent
                    anchors.margins: 10
                    wrapMode: Text.Wrap
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: "#f5f5f5"
            border.color: "#e0e0e0"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    height: 40
                    radius: 20
                    color: "white"
                    border.color: "#ccc"

                    TextInput {
                        anchors.fill: parent
                        anchors.leftMargin: 15
                        anchors.rightMargin: 15
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 14
                        
                        Text {
                            text: "Write a message..."
                            color: "#999"
                            visible: !parent.text && !parent.activeFocus
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                }

                Rectangle {
                    width: 40
                    height: 40
                    radius: 20
                    color: "#007bff"
                    
                    Text {
                        text: "➤"
                        color: "white"
                        font.pixelSize: 18
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            console.log("[ChatArea] Sending message...")
                        }
                    }
                }
            }
        }
    }
}
