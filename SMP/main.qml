import QtQuick 2.12
import QtQuick.Controls 2.12
import kPresenter 1.0

import themePresenter 1.0

ApplicationWindow {
    id: mainWindow
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    title: qsTr("SMP")

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

    ListView {
        id: lv
        anchors.fill: parent;
        model: queueModel

        delegate: Item {
            id: data
            height: 20
            width: lv.width
            Text {
                id: textic
                text: model.id + "..." + model.name;
            }
        }
    }
    Button {
        text: "->"
        anchors.bottom: parent.bottom
        id: erer
        onClicked: {
            /*waitBar.toggle();
            waitBar.toggle();*/
            console.log("start");
            pq.cycle();
            /*for (var i = 0; i < 10000; i++) {
                console.log(i);
            }*/


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
        to: kp.CompositionTime
        stepSize: 1
        value: kp.CurrentTime
        onMoved:  {
            kp.pause();
            ik.setTime(timeLine.value);
            kp.play();
        }
    }

    ComboBox {
        id: themes
        anchors.bottom: parent.bottom
        anchors.left: timeLine.right
        model: tp.getThemes()
        onCurrentIndexChanged: {
            tp.setTheme(currentIndex)
            console.log(tp.Background)
        }
    }

}
