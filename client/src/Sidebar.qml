import QtQuick
import QtQuick.Layouts

Rectangle {
    id: sidebarRoot
    color: "#ffffff"
    border.color: "#e0e0e0"
    border.width: 1

    Rectangle {
        id:searchHeader
        width: parent.width
        height: 100
        color: "#f5f5f5"
        border.color: "#e0e0e0"
        border.width: 1
        anchors.top: parent.top 

        RowLayout { 
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Rectangle {
                width: 40
                height: 40 
                radius: 20
                color: "#e0e0e0"
                Layout.alignment: Qt.AlignVCenter

                Text {
                    text: "⚙"
                    font.pixelSize: 20
                    anchors.centerIn: parent
                }

                MouseArea { 
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onPressed: parent.color = "#d0d0d0"
                    onReleased: parent.color = "#e0e0e0"
                    onClicked: console.log("[Sidebar] settings click")
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 40
                color: "white"
                border.color: "#ccc"
                radius: 20
                Layout.alignment: Qt.AlignVCenter
                
                TextInput {
                    anchors.fill: parent
                    anchors.leftMargin: 15
                    anchors.rightMargin: 15
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                    Text {
                        text: "Поиск..."
                        color: "#999"
                        visible: !parent.text && !parent.activeFocus
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    ListView {
        id: chatList
        width: parent.width
        anchors.top: searchHeader.bottom
        anchors.bottom: parent.bottom

        clip: true
        model: 20

        delegate: Rectangle {
            id: chatItem
            width: chatList.width
            height: 100
            color: index % 2 == 0 ? "#ffffff" : "#fafafa"
            border.color: "#f0f0f0"
            border.width: 1

            MouseArea {
                id: hoverArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: console.log("[Sidebar] open chat " + index)
            }

            Row { 
                anchors.fill: parent
                anchors.margins: 10
                spacing: 15

                Rectangle {
                    width: Math.min(chatItem.height * 0.6, 60)
                    height: width
                    radius: width / 2
                    color: "#007bff"
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        text: "Ч"
                        color: "white"
                        font.bold: true
                        font.pixelSize: parent.height * 0.5
                        anchors.centerIn: parent
                    }
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        text: "Чат с пользователем " + index
                        font.bold: true
                        font.pixelSize: Math.max(12, Math.min(16, chatItem.height * 0.2))
                    }
                    Text { 
                        text: "Последнее сообщение..."
                        color: "#777"
                        font.pixelSize: Math.max(10, Math.min(14, chatItem.height * 0.15))
                    }
                }
            }
        }
    }
}
