import QtQuick

Rectangle {
    id: root
    color: "#f1f2f5"

    Column {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.8, 300)
        spacing: 15

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
                    errorBox.visible = false
                    if (handleField.text.length == 0) {
                        errorText.text = "Введите логин!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    } else if (displayNameField.text.length == 0) {
                        errorText.text = "Введите имя!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    } else if (passwordField.text.length == 0) {
                        errorText.text = "Введите пароль!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    } else if (passwordField.text != repeatPasswordField.text) {
                        errorText.text = "Пароли не совпадают!"
                        errorBox.visible = true
                        errorTimer.restart()
                        return
                    }
                
                    console.log("Регистрация :", handleField.text)
                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_in.qml"
                    }
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
                    var loader = root.parent
                    if (loader) {
                        loader.source = "sign_in.qml"
                    }
                }
            }
        }
    }
}