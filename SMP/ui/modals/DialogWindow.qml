import QtQuick 2.15
import QtQuick.Controls 2.15

// Ввод текста
Dialog {
    id: enterNameDialog
    anchors.centerIn: parent
    title: titleText
    standardButtons: Dialog.Ok | Dialog.Cancel
    implicitWidth: parent.width / 2
    focus: true

    // Текст диалогового окна
    property string titleText: qsTr("Dialog Title")

    // Передача тектста диалогового окна
    signal okClicked(msg: string)

    TextField {
        id: enteredText
        anchors.left: parent.left
        anchors.right: parent.right
        selectByMouse: true
        focus: true
        placeholderText: titleText
    }

    onAccepted: {
        okClicked(enteredText.text);
    }

   onClosed: {
       enteredText.clear();
   }
}