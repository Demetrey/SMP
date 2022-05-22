/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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
