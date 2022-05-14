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
            property int val: Math.random() * r.height // 0

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
}