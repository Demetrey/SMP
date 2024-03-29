/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import CycleState 1.0

import "../scripts/AdditionalFunctions.js" as AFunc

// Очередь воспроизведения
Item {
    anchors.fill: parent

    // Перемешивание, зацикливание
    Rectangle {
        id: topSide
        color: themePresenter.Background
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
        z: 2

        RowLayout {
            anchors.fill: parent

            // Перемешивание
            Button {
                Layout.fillWidth: true
                Layout.minimumWidth: 40
                Layout.maximumHeight: parent.height
                Layout.minimumHeight: parent.height

                background: Rectangle {
                    color: "#00000000"
                }

                Image {
                    id: shuffleBtnImage
                    source: "qrc:/controll/IMAGES/controlls/shuffle.svg"
                    anchors.centerIn: parent
                    width: height
                    height: parent.height
                    anchors.margins: 5
                    sourceSize.height: height
                    sourceSize.width: height
                }

                ColorOverlay {
                   anchors.fill: shuffleBtnImage
                   source: shuffleBtnImage
                   color: themePresenter.Textcolor
               }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: shuffleBtnImage.right
                    anchors.leftMargin: 5
                    color: themePresenter.Textcolor
                    font.pixelSize: 10
                    text: playQController.IsShuffled ? qsTr("on") + qmlTranslator.EmptyString : qsTr("off") + qmlTranslator.EmptyString
                }

                onClicked: {
                    playQController.IsShuffled ?
                                playQController.shuffleBack() :
                                playQController.shuffle();
                }
            }

            // Зацикливание
            Button {
                Layout.fillWidth: true
                Layout.minimumWidth: 40
                Layout.maximumHeight: parent.height
                Layout.minimumHeight: parent.height

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: btnRepeatImage.right
                    anchors.leftMargin: 5
                    color: themePresenter.Textcolor
                    font.pixelSize: 10
                    text: playQController.CurrentSycle === CycleState.CycleNo ?
                              qsTr("no") + qmlTranslator.EmptyString : playQController.CurrentSycle === CycleState.CycleOne ?
                                  "1" : qsTr("all") + qmlTranslator.EmptyString
                }

                background: Rectangle {
                    color: "#00000000"
                }

                Image {
                    id: btnRepeatImage
                    source: "qrc:/controll/IMAGES/controlls/repeat.svg"
                    anchors.centerIn: parent
                    width: height
                    height: parent.height
                    anchors.margins: 5
                    sourceSize.height: height
                    sourceSize.width: height
                }

                ColorOverlay {
                   anchors.fill: btnRepeatImage
                   source: btnRepeatImage
                   color: themePresenter.Textcolor
               }

                onClicked: {
                    playQController.cycle();
                }
            }
        }
    }

    // Очередь
    ListView {
        id: playQueueList
        anchors.top: topSide.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        model: queueModel

        // Описание делегата
        delegate: Rectangle {
            width: playQueueList.width
            height: 50
            color: playQController.CurrentPlayIndex === index ?
                       themePresenter.Listitemselected :
                       themePresenter.Listitem

            // Текстовые поля ограничены максимальным размером формы
            // Номер П/П
            Text {
                id: indexText
                text: index + 1
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 2
                width: height
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            // Название
            Text {
                id: nameText
                anchors.left: indexText.right
                anchors.top: parent.top
                height: parent.height / 2
                anchors.leftMargin: 10
                text: model.name.substr(0, parent.width / font.pointSize)
                verticalAlignment: Text.AlignBottom
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            // Исполнитель и альбом
            Text {
                anchors.left: nameText.left
                anchors.top: nameText.bottom
                anchors.bottom: parent.bottom
                font.pointSize: 9
                color: themePresenter.Textcolor
                horizontalAlignment: Text.AlignHCenter
                text: (model.artist + " :: " + model.album).substr(0, parent.width / font.pointSize)
            }

            // Обработка клика
            MouseArea {
                id: fillArea
                anchors.fill: parent
                onClicked: {
                    playQController.play(index)
                }

                onPressAndHold: {
                    var absolutePos = AFunc.getAbsolutePosition(fillArea);
                    mediaContextMenu.currentPlayId = model.id;
                    mediaContextMenu.currentPlayIndex = index;
                    mediaContextMenu.x =  absolutePos.x + mouseX;
                    mediaContextMenu.y = absolutePos.y;
                    mediaContextMenu.open();
                }
            }

            // Поле вызова контекстного меню
            Image {
                id: moreImg
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                source: "qrc:/controll/IMAGES/controlls/more_horiz.svg"
                anchors.margins: 5
                anchors.rightMargin: 10
                sourceSize.height: height
                sourceSize.width: height

                MouseArea {
                    id: rightArea
                    anchors.fill: parent

                    onClicked: {
                        var absolutePos = AFunc.getAbsolutePosition(rightArea);
                        mediaContextMenu.currentPlayId = model.id;
                        mediaContextMenu.currentPlayIndex = index;
                        mediaContextMenu.x =  absolutePos.x;
                        mediaContextMenu.y = absolutePos.y;
                        mediaContextMenu.open();
                    }
                }
            }

            ColorOverlay {
               anchors.fill: moreImg
               source: moreImg
               color: themePresenter.Textcolor
           }
        }

        ScrollBar.vertical: ScrollBar {}
    }

    // context menu (контекстное меню)
    Menu {
        id: mediaContextMenu

        property int currentPlayId: -1
        property int currentPlayIndex: -1

        Action {
            text: qsTr("Remove from Queue") + qmlTranslator.EmptyString;

            onTriggered: {
                playQController.removeFromQueue(mediaContextMenu.currentPlayId);
                mediaContextMenu.currentPlayId = -1;
                mediaContextMenu.currentPlayIndex = -1;
            }
        }
    }
}
