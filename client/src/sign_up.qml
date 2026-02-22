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

            function onRegisterSuccess() {
                console.log("[Sign Up] Registration successful!")
                var loader = root.parent
                if (loader) {
                    loader.source = "sign_in.qml"
                }
            }

            function onRegisterFailed(errorMsg) {
                console.log("[Sign Up] Registration failed: ", errorMsg)
                errorText.text = errorMsg
                errorBox.visible = true
                errorTimer.restart()
            }
        }

        Text {
            text: "Регистрация"
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

        // Display Name Input
        Rectangle {
            width: parent.width
            height: Math.max(45, Math.min(55, root.height * 0.07))
            color: "white"
            border.color: "#ccc"
            radius: height / 2

            TextInput {
                id: displayNameField
                anchors.fill: parent
                anchors.leftMargin: parent.radius
                anchors.rightMargin: parent.radius
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16
                
                Text {
                    text: "Введите имя"
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
                    text: "Придумайте надежный пароль"
                    color: "#aaa"
                    font.pixelSize: parent.font.pixelSize
                    visible: !parent.text && !parent.activeFocus
                    anchors.centerIn: parent
                }
            }
        }

        // Repeat Password Input
        Rectangle {
            width: parent.width
            height: Math.max(45, Math.min(55, root.height * 0.07))
            color: "white"
            border.color: "#ccc"
            radius: height / 2

            TextInput {
                id: repeatPasswordField
                anchors.fill: parent
                anchors.leftMargin: parent.radius
                anchors.rightMargin: parent.radius
                echoMode: TextInput.Password
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16

                Text {
                    text: "Повторите пароль"
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

        // Sign Up Button
        Rectangle {
            width: parent.width
            height: Math.max(50, Math.min(60, root.height * 0.1))
            color: "#007bff"
            radius: height / 2

            Text {
                text: "Sign Up!"
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
                    console.log("[Sign Up] Sign Up button clicked")
                    errorBox.visible = false
                    
                    if (handleField.text.length == 0) {
                        console.log("[Sign Up] Validation Error: Handle is empty")
                        errorText.text = "Введите логин!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    } else if (displayNameField.text.length == 0) {
                        console.log("[Sign Up] Validation Error: Display Name is empty")
                        errorText.text = "Введите имя!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    } else if (passwordField.text.length == 0) {
                        console.log("[Sign Up] Validation Error: Password is empty")
                        errorText.text = "Введите пароль!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    } else if (passwordField.text != repeatPasswordField.text) {
                        console.log("[Sign Up] Validation Error: Passwords do not match")
                        errorText.text = "Пароли не совпадают!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    }

                    console.log("[Sign Up] Validation successful. Sending request to server...")
                    Auth.registerUser(handleField.text, displayNameField.text, passwordField.text)
                }   
            }
        }

        // Back to Login Link
        Rectangle {
            width: parent.width
            height: Math.max(50, Math.min(60, root.height * 0.1))
            color: "transparent"
            border.color: "#007bff"
            border.width: 2
            radius: height / 2
            
            Text {
                text: "Уже есть аккаунт? Войти"
                color: "#007bff"
                font.pixelSize: 14
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    console.log("[Sign Up] Navigating to Login screen (already have account)")
                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_in.qml"
                    }
                }
            }
        }
    }
}