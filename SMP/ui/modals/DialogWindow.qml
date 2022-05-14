import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: dialogBase
    color: "#880f0f0f"
    anchors.fill: parent
    visible: false

    signal okClicked(msg: string)
    signal cancelClicked

    property string currentText: ""

    Rectangle {
        id: searchBorder
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width > 360 ? parent.width / 2 : parent.width
        height: 40
        color: themePresenter.Background
        border.color: "black"
        border.width: 1
        clip: true

        TextInput {
            id: inputField
            anchors.fill: parent
            anchors.margins: 3
            font.family: "Arial"
            font.pixelSize: height / 1.5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: themePresenter.Textcolor
            selectByMouse: true
        }
    }

    Button {
        id: btnOk
        anchors.left: searchBorder.left
        anchors.top: searchBorder.bottom
        width: searchBorder.width / 2 - 5
        height: 40

        Text {
            text: qsTr("OK")
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: themePresenter.Textcolor
        }

        onClicked: {
            dialogBase.hide();
            dialogBase.currentText = inputField.text;
            dialogBase.okClicked(inputField.text);
        }
    }

    Button {
        id: btnCancel
        anchors.left: btnOk.right
        anchors.leftMargin: 5
        anchors.top: searchBorder.bottom
        width: btnOk.width
        height: btnOk.height

        Text {
            text: qsTr("CANCEL")
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            color: themePresenter.Textcolor
        }

        onClicked: {
            dialogBase.hide();
            dialogBase.cancelClicked();
        }
    }

    function show() {
        inputField.clear();
        dialogBase.visible = true;
    }

    function hide() {
        dialogBase.visible = false;
    }
}
