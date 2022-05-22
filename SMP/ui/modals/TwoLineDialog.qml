/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

import QtQuick 2.15
import QtQuick.Controls 2.15

// Ввод текста
Dialog {
    id: enterNameDialog
    anchors.centerIn: parent
    title: titleText
    standardButtons: Dialog.Ok | Dialog.Cancel
    implicitWidth: !isAndroid ? parent.width / 2 : parent.width
    focus: true

    // Текст диалогового окна
    property string titleText: qsTr("Dialog Title") + qmlTranslator.EmptyString
    property string label1Text: qsTr("Label_1") + qmlTranslator.EmptyString
    property string label2Text: qsTr("Label_2") + qmlTranslator.EmptyString

    // Передача тектста диалогового окна
    signal okClicked(msg1: string, msg2: string)

    contentItem:  Item {
        implicitHeight: 50

        TextField {
            id: enteredText1
            anchors.left: parent.left
            anchors.right: parent.right
            selectByMouse: true
            placeholderText: label1Text
        }

        TextField {
            id: enteredText2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: enteredText1.bottom
            selectByMouse: true
            focus: true
            placeholderText: label2Text
        }
    }

    onAccepted: {
        okClicked(enteredText1.text, enteredText2.text);
    }

   onClosed: {
       enteredText1.clear();
       enteredText2.clear();
   }
}
