import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    // Затенение
    anchors.fill: parent
    color: "#88050505"
    z: 50

    // Перехват кликов
    MouseArea {
        anchors.fill: parent
    }

    // Отображаемый анимированный объект
    ProgressBar {
        anchors.fill: parent
        indeterminate: true
    }
}
