/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import QtQuick.Layouts 1.3

Rectangle {
    id: r
    anchors.fill: parent
    color: "#00000000"

    property real columnSize: 20
    property string rectangleColor: "#A8A8A8"
    property string borderColor: "#3D3D3D"

    function setValue(index, value) {
        vizualizer.itemAtIndex(index).val = value * r.height;
    }

    function dynamicAdd(count) {
        for(var i = 0; i < count; i++) {
            listModel.append({});
        }
    }

    ListView {
        id: vizualizer
        anchors.fill: parent
        orientation: Qt.Horizontal
        spacing: -1

        delegate: Item {
            width: r.columnSize + 1 // +1 - border compensation
            height: r.height
            property int val: 0 // Math.random() * r.height

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                color: r.rectangleColor
                border.color: r.borderColor
                border.width: 1
                height: val > r.height ? val / 2 : val

                Behavior on height {
                    NumberAnimation { duration: 100 }
                }
            }
        }

        model: ListModel {
            id: listModel
        }
    }

    Timer {
        id: valuRequest
        interval: 100
        repeat: true

        onTriggered: {
            var arr = iKernel.getVizValues();
            for (var i = 0; i < listModel.count; i++)
                r.setValue(i, Math.sqrt(arr[i+10]) * 3);
        }
    }

    Component.onCompleted: {
        valuRequest.start();
    }
}
