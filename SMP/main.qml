import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15

import kPresenter 1.0

import "./ui/modals/"

ApplicationWindow {
    id: mainWindow
    flags: Qt.Window | Qt.FramelessWindowHint

    property int prevX: 0
    property int prevY: 0
    property bool isAndroid: Qt.platform.os === "android"

    minimumWidth: 640
    minimumHeight: 480
    visible: true
    title: qsTr("SMP")

    // set theme settings
    Material.theme: themePresenter.BaseTheme === "light" ? Material.Light : Material.Dark
    Material.background: themePresenter.Background
    Material.primary: themePresenter.Primary
    Material.accent: themePresenter.Accent
    Material.foreground: themePresenter.Textcolor

    // Top bar
    Rectangle {
        id: topMenu
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
        color: themePresenter.Primary

        Text {
            anchors.fill: parent
            anchors.margins: 2
            id: appName
            text: qsTr("SMP")
            font.family: "Cascadia Code"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.pointSize: 20
            minimumPointSize: 5
            fontSizeMode: Text.Fit
        }

        DragHandler {
            enabled: !isAndroid
            onActiveChanged: if (active) mainWindow.startSystemMove();
            target: null
        }

        // Menu button
        Button {
            id: btnMenu
            width: height
            height: parent.height
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 5

            Image {
                source: "qrc:/controll/IMAGES/controlls/menu.svg"
                anchors.fill: parent
                anchors.margins: 10
                sourceSize.width: width
                sourceSize.height: height
            }

            onClicked: {
                navDrawer.open();
            }
        }

        // Button Close
        Button {
            id: btnClose
            width: height
            height: parent.height
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 5
            visible: !isAndroid
            z: 100

            Image {
                source: "qrc:/controll/IMAGES/controlls/close.svg"
                anchors.fill: parent
                anchors.margins: 10
                sourceSize.width: width
                sourceSize.height: height
            }

            onClicked: {
                mainWindow.close();
            }
        }

        // Button maximize/normalize
        Button {
            id: btnMaximize
            width: height
            height: parent.height
            anchors.top: parent.top
            anchors.right: btnClose.left
            visible: !isAndroid

            Image {
                source: "qrc:/controll/IMAGES/controlls/maximize.svg"
                anchors.fill: parent
                anchors.margins: 10
                sourceSize.width: width
                sourceSize.height: height
            }

            onClicked: {
                windowResize();
            }
        }

        Button {
            id: btnMinimize
            width: height
            height: parent.height
            anchors.top: parent.top
            anchors.right: btnMaximize.left
            visible: !isAndroid

            Image {
                source: "qrc:/controll/IMAGES/controlls/minimize.svg"
                anchors.fill: parent
                anchors.margins: 10
                sourceSize.width: width
                sourceSize.height: height
            }

            onClicked: {
                mainWindow.showMinimized();
            }
        }
    }

    Component.onCompleted: {
        console.log(Qt.platform.os)
    }



    // Main Content
    Loader {
        id: pageLoader
        anchors.top: topMenu.bottom
        anchors.bottom: isAndroid ? parent.bottom : bottomBar.top
        anchors.left: parent.left
        anchors.right: parent.right
        source: "qrc:/ui/mainForm/MainForm.qml"

        function formLoad(index) {
            switch (index) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
            }
        }
    }

    // bottom bar
    Rectangle {
        id: bottomBar
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 20
        color: themePresenter.Background
        visible: !isAndroid

        // Resize Button
        Image {
            id: resizeItem
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 20
            height: 20
            visible: !isAndroid
            source: "qrc:/controll/IMAGES/controlls/field.svg"

            DragHandler {
                enabled: !isAndroid
                onActiveChanged: if (active) mainWindow.startSystemResize(Qt.RightEdge | Qt.BottomEdge);
                target: null
                cursorShape: Qt.SizeFDiagCursor
            }
        }
    }

    Drawer {
        id: navDrawer
        width: !isAndroid ? parent.width * 0.3 : parent.width * 0.75
        height: parent.height
        Rectangle {
            anchors.fill: parent
            color: themePresenter.Background

            // back button
            Button {
                id: hideMenu
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 5
                width: height
                height: topMenu.height

                Image {
                    source: "qrc:/controll/IMAGES/controlls/arrow_back.svg"
                    anchors.fill: parent
                    anchors.margins: 10
                    anchors.leftMargin: parent.width / 3
                    sourceSize.width: width
                    sourceSize.height: height
                }

                onClicked: {
                    navDrawer.close();
                }
            }

            // menu
            ListView {
                id: listMenu
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: hideMenu.bottom
                model: navModel

                delegate: Button {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 50
                    anchors.margins: 5
                    text: model.menuText

                    contentItem: Text {
                        text: parent.text
                        font.family: "Arial"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: themePresenter.Textcolor
                        font.pixelSize: 20
                    }

                    onClicked: {
                        console.log(text);
                    }
                }
            }
        }
    }

    WaitLocker {
        id: waitLocker
        visible: false
    }

    Connections {
        target: playQController

        function onStartShuffle() {
            waitLocker.visible = true;
        }

        function onEndShuffle() {
            waitLocker.visible = false;
        }

        function onStartCreateQueue() {
            waitLocker.visible = true;
        }

        function onCreatedQueue() {
            waitLocker.visible = false;
        }

        function onStartInsertToQueue() {
            waitLocker.visible = true;
        }

        function onEndInsertToQueue() {
            waitLocker.visible = false;
        }

        function onStartRemoveFromQueue() {
            waitLocker.visible = true;
        }

        function onStopRemoveFromQueue() {
            waitLocker.visible = false;
        }
    }

    // menu data
    ListModel {
        id: navModel
        ListElement {menuText: qsTr("Home")}
        ListElement {menuText: qsTr("Media library")}
        ListElement {menuText: qsTr("Equalizer")}
        ListElement {menuText: qsTr("Settings")}
    }

    function windowResize() {
        if (mainWindow.visibility === Window.Maximized)
            mainWindow.showNormal();
        else
            mainWindow.showMaximized();
    }

}
