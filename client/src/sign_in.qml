import QtQuick
import Messenger 1.0

Rectangle {
    id: root
    color: "#f1f2f5"

    Column {
        anchors.centerIn: parent
        width: Math.min(400, parent.width * 0.8)
        spacing: 15

        Connections {
            target: Auth

            function onLoginSuccess(token) {
                console.log("[Login] Authentication successful! Token:", token)
                AppState.token = token
                AppState.currentUserHandle = handleField.text
                console.log("State token is now:", AppState.token)
                
                var loader = root.parent
                if (loader) {
                    loader.source = "chat.qml"
                }
            }

            function onLoginFailed(errorMsg) {
                console.log("[Login] Login failed:", errorMsg)
                errorText.text = errorMsg
                errorBox.visible = true
                errorTimer.restart()
            }
        }

        Text {
            text: "Alyosha messenger"
            font.pixelSize: 28
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 20
        }

        // Handle Input
        Rectangle {
            width: parent.width
            height: Math.max(45, Math.min(55, root.height * 0.07))
            color: "white"
            border.color: "#ccc"
            radius: height / 2

            TextInput {
                id: handleField
                anchors.fill: parent
                anchors.leftMargin: parent.radius
                anchors.rightMargin: parent.radius
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16
                
                Text {
                    text: "Введите логин"
                    color: "#aaa"
                    font.pixelSize: parent.font.pixelSize
                    visible: !parent.text && !parent.activeFocus
                    anchors.centerIn: parent
                }
            }
        }

        // Password Input
        Rectangle {
            width: parent.width
            height: Math.max(45, Math.min(55, root.height * 0.07))
            color: "white"
            border.color: "#ccc"
            radius: height / 2

            TextInput {
                id: passwordField
                anchors.fill: parent
                anchors.leftMargin: parent.radius
                anchors.rightMargin: parent.radius
                echoMode: TextInput.Password
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16

                Text {
                    text: "Введите пароль"
                    color: "#aaa"
                    font.pixelSize: parent.font.pixelSize
                    visible: !parent.text && !parent.activeFocus
                    anchors.centerIn: parent
                }
            }
        }

        // Error Message box
        Rectangle {
            id: errorBox
            width: parent.width
            height: Math.max(45, Math.min(55, root.height * 0.07))
            color: "white"
            border.color: "#F05C5C"
            radius: 8
            visible: false

            Text {
                id: errorText
                text: ""
                color: "red"
                anchors.centerIn: parent
                font.pixelSize: 12
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
            height: Math.max(50, Math.min(60, root.height * 0.1))
            color: "#007bff"
            radius: height / 2

            Text {
                text: "Sign In"
                color: "white"
                font.pixelSize: 16
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onPressed: parent.opacity = 0.75
                onReleased: parent.opacity = 1.0
                onClicked: {
                    console.log("[Login] Sign In button clicked")
                    errorBox.visible = false
                    if (handleField.text.length == 0) {
                        console.log("[Login] Validation Error: Handle is empty")
                        errorText.text = "Ошибка! Введите логин"
                        errorBox.visible = true
                        errorTimer.restart()
                    } else if (passwordField.text.length == 0) {
                        console.log("[Login] Validation Error: Password is empty")
                        errorText.text = "Ошибка! Введите пароль"
                        errorBox.visible = true
                        errorTimer.restart()
                    } else {
                        console.log("[Login] Validation Successful. Sending data...", handleField.text)
                        Auth.loginUser(handleField.text, passwordField.text)
                    }
                }
            }
        }

        // Register Button
        Rectangle {
            width: parent.width
            height: Math.max(50, Math.min(60, root.height * 0.1))
            color: "#007bff"
            radius: height / 2

            Text {
                text: "Register"
                color: "white"
                font.pixelSize: 16
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onPressed: parent.opacity = 0.75
                onReleased: parent.opacity = 1.0
                onClicked: {
                    console.log("[Login] Navigating to Registration screen")
                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_up.qml"
                    }
                }
            }
        }
    }
}
