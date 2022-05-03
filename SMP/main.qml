import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: mainWindow
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    title: qsTr("SMP")

    Image {
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
    }
}
