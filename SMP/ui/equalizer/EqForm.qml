/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

import QtQuick 2.1
import QtQuick.Controls 2.15

// Форма эквалайзера
Item {
    anchors.fill: parent
    anchors.margins: 5
    anchors.leftMargin: !isAndroid ? parent.width / 6 : 5
    anchors.rightMargin: anchors.leftMargin

    Column {
        id: deviceSettings
        anchors.fill: parent
        spacing: 10

        // Реверберация
        Item {
            id: reverbItem
            width: parent.width
            height: 40

            Text {
                id: reverbText
                text: qsTr("Reverberation") + " :: "
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 100
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            Text {
                id: reverbValue
                text: kernelPresenter.Reverb + " %"
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 60
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            Slider {
                id: reverbSlider
                anchors.left: reverbText.right
                anchors.right: reverbValue.left
                anchors.verticalCenter: parent.verticalCenter
                value: kernelPresenter.Reverb
                from: 0
                to: 100
                stepSize: 1

                onMoved: {
                    kernelPresenter.Reverb = reverbSlider.value;
                }
            }
        }

        // Баланс
        Item {
            id: balanceItem
            width: parent.width
            height: 40

            Text {
                id: balanceText
                text: qsTr("Balance") + " :: " + qsTr("L")
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 100
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            Text {
                id: balanceValue
                text: qsTr("R ") + kernelPresenter.Balance + " %"
                verticalAlignment: Text.AlignVCenter
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 60
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            Slider {
                id: balanceSlider
                anchors.left: balanceText.right
                anchors.right: balanceValue.left
                anchors.verticalCenter: parent.verticalCenter
                value: kernelPresenter.Balance
                from: -100
                to: 100
                stepSize: 1

                onMoved: {
                    kernelPresenter.Balance = balanceSlider.value;
                }
            }
        }

        // Настройки эквалайзера
        ListView {
            id: eqValues
            anchors.topMargin: 20
            width: parent.width
            height: parent.height - reverbItem.height - balanceItem.height - 10
            model: equalizerData

            delegate: Item {
                width: eqValues.width
                height: 35

                Text {
                    id: vertex
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 60
                    font.pixelSize: 15
                    color: themePresenter.Textcolor
                    text: model.center >= 1000 ?
                              model.center / 1000 + qsTr("KHz") :
                              model.center + qsTr("Hz")
                }

                Text {
                    id: eqValue
                    verticalAlignment: Text.AlignVCenter
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: 60
                    font.pixelSize: 15
                    color: themePresenter.Textcolor
                    text: Math.round(eqSlider.value * 100) / 100
                }

                Slider {
                    id: eqSlider
                    anchors.left: vertex.right
                    anchors.right: eqValue.left
                    anchors.verticalCenter: parent.verticalCenter
                    value: model.value
                    from: -10
                    to: 10
                    stepSize: 0.1

                    property int currentCenter: 0

                    onMoved: {
                        kernelPresenter.setEqValue(model.center, value);
                    }
                }
            }
        }

    }

    ListModel {
        id: equalizerData
    }

    function addEq(center, value) {
        equalizerData.append({center, value});
    }

    Component.onCompleted: {
        let centers = kernelPresenter.getEqCenters();
        let values = kernelPresenter.getEqValues();

        for (let i = 0; i < centers.length; i++) {
            addEq(centers[i], values[i]);
        }
    }

}
