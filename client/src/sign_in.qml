import QtQuick

Rectangle {
    id: root
    color: "#f1f2f5"

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.8, 300)
        spacing: 20

        Text {
            text: "Alyosha messenger"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Handle Input
        Rectangle {
            width: parent.width
            height: 40
            color: "white"
            border.color: "#ccc"
            radius: 4

            TextInput {
                id: handleField
                anchors.fill: parent
                anchors.margins: 10
                text: ""
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                
                Text {
                    text: "Введите логин"
                    color: "#aaa"
                    visible: !parent.text && !parent.activeFocus
                    anchors.centerIn: parent
                }
            }
        }

        // Password Input
        Rectangle {
            width: parent.width
            height: 40
            color: "white"
            border.color: "#ccc"
            radius: 4

            TextInput {
                id: passwordField
                anchors.fill: parent
                anchors.margins: 10
                text: ""
                echoMode: TextInput.Password
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter

                Text {
                    text: "Введите пароль"
                    color: "#aaa"
                    visible: !parent.text && !parent.activeFocus
                    anchors.centerIn: parent
                }
            }
        }

        // Error Message box
        Rectangle {
            id: errorBox
            width: parent.width
            height: 30
            color: "white"
            border.color: "#F05C5C"
            radius: 4
            visible: false

            Text {
                id: errorText
                text: ""
                color: "red"
                anchors.centerIn: parent
                font.pixelSize: 14
            }

            Timer {
                id: errorTimer 
                interval: 5000
                running: false
                repeat: false
                onTriggered: parent.visible = false
            }
        }

        // Login Button
        Rectangle {
            width: parent.width
            height: 40
            color: "#007bff"
            radius: 4

            Text {
                text: "Sign In"
                color: "white"
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    errorBox.visible = false
                    if (handleField.text.length == 0) {
                        errorText.text = "Ошибка! Введите логин"
                        errorBox.visible = true
                        errorTimer.restart()
                    } else if (passwordField.length == 0) {
                        errorText.text = "Ошибка! Введите пароль"
                        errorBox.visible = true
                        errorTimer.restart()
                    } else {
                        var loader = root.parent
                        if (loader) {
                            loader.source = "chat.qml"
                        }
                    }
                }
                
                onPressed: parent.opacity = 0.75
                onReleased: parent.opacity = 1.0
            }
        }

        // Register Button
        Rectangle {
            width: parent.width
            height: 40
            color: "#007bff"
            radius: 4

            Text {
                text: "Register"
                color: "white"
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onPressed: parent.opacity = 0.75
                onReleased: parent.opacity = 1.0
                onClicked: {
                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_up.qml"
                    }
                }
            }
        }
    }
}
