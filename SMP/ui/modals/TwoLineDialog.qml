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
    property string label1Text: qsTr("Label_1")
    property string label2Text: qsTr("Label_2")

    // Передача тектста диалогового окна
    signal okClicked(msg1: string, msg2: string)

    TextField {
        id: enteredText1
        anchors.left: parent.left
        anchors.right: parent.right
        selectByMouse: true
        focus: true
        placeholderText: label1Text
    }

    TextField {
        id: enteredText2
        anchors.left: parent.left
        anchors.right: parent.right
        selectByMouse: true
        focus: true
        placeholderText: label2Text
    }

    onAccepted: {
        okClicked(enteredText1.text, enteredText2.text);
    }

   onClosed: {
       enteredText1.clear();
       enteredText2.clear();
   }
}
