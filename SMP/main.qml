import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15

import kPresenter 1.0
//import themePresenter 1.0

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

    /*Image {
        id: img
        property string currenImage: "image://imgPresenter/image"
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        source: currenImage
        sourceSize.width: 100
        sourceSize.height: 100

        function update() {
            source = "image://imgPresenter/image/";
            source = Qt.binding(function() { return currenImage });
        }
    }

    Connections {
        target: imagePresenter
        function onImageChanged() {
            console.log("new image");
            img.update();
        }
    }*/

    /*ListView {
        id: lv
        anchors.fill: parent;
        model: queueModel

        delegate: Rectangle {
            id: data
            height: 20
            width: lv.width
            color: themePresenter.Listitem
            Text {
                id: textic
                text: model.id + "..." + model.name;
                color: themePresenter.Textcolor
            }
        }
    }
    Button {
        text: "->"
        anchors.bottom: parent.bottom
        id: erer
        onClicked: {
            console.log("start");
            pq.cycle();


        }
    }

    Connections {
        target: pq
        function onCreatedQueue() {
            waitBar.toggle();
            console.log("sdsds");

        }
    }

    Rectangle {
        id: waitBar
        color: "#0f0f0f0f";
        anchors.fill: parent;
        visible: false
        function toggle() {
            console.log("toggle");
            if (waitBar.visible)
                waitBar.visible = false
            else
                waitBar.visible = true
        }

        ProgressBar {
            anchors.fill: parent
            indeterminate: true
        }
    }

    Slider {
        id: timeLine
        anchors.bottom: parent.bottom
        anchors.left: erer.right
        from: 0
        to: kernelPresenter.CompositionTime
        stepSize: 1
        value: kernelPresenter.CurrentTime
        onMoved:  {
            kernelPresenter.pause();
            iKernel.setTime(timeLine.value);
            kernelPresenter.play();
        }
    }

    ComboBox {
        id: themes
        anchors.bottom: parent.bottom
        anchors.left: timeLine.right
        model: themePresenter.getThemes()
        onCurrentIndexChanged: {
            themePresenter.setTheme(currentIndex)
        }
    }*/

}
