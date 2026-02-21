import QtQuick
import Messenger 1.0

Rectangle {
    id: root
    color: "#f1f2f5"

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.8, 300)
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

        // Display Name Input
        Rectangle {
            width: parent.width
            height: 40
            color: "white"
            border.color: "#ccc"
            radius: 4

            TextInput {
                id: displayNameField
                anchors.fill: parent
                anchors.margins: 10
                text: ""
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
                
                Text {
                    text: "Введите имя"
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
                    text: "Придумайте надежный пароль"
                    color: "#aaa"
                    visible: !parent.text && !parent.activeFocus
                    anchors.centerIn: parent
                }
            }
        }

        // Repeat Password Input
        Rectangle {
            width: parent.width
            height: 40
            color: "white"
            border.color: "#ccc"
            radius: 4

            TextInput {
                id: repeatPasswordField
                anchors.fill: parent
                anchors.margins: 10
                text: ""
                echoMode: TextInput.Password
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter

                Text {
                    text: "Повторите пароль"
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

        // Sign Up Button
        Rectangle {
            width: parent.width
            height: 40
            color: "#007bff"
            radius: 4

            Text {
                text: "Sign Up!"
                color: "white"
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
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
        Text {
            text: "Уже зарегистрированы? Войти"
            color: "#007bff"
            font.underline: true
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 10
            
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