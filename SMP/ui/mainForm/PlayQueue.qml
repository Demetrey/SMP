import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import CycleState 1.0

Item {
    anchors.fill: parent

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

            Button {
                Layout.fillWidth: true
                Layout.minimumWidth: 40
                Layout.maximumHeight: parent.height
                Layout.minimumHeight: parent.height

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

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: shuffleBtnImage.right
                    anchors.leftMargin: 5
                    color: themePresenter.Textcolor
                    font.pixelSize: 10
                    text: playQController.IsShuffled ? qsTr("on") : qsTr("off")
                }

                onClicked: {
                    playQController.IsShuffled ?
                                playQController.shuffleBack() :
                                playQController.shuffle();
                }
            }

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
                              qsTr("no") : playQController.CurrentSycle === CycleState.CycleOne ?
                                  "1" : qsTr("all")
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

                onClicked: {
                    playQController.cycle();
                }
            }
        }
    }

    ListView {
        id: playQueueList
        anchors.top: topSide.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        model: queueModel

        delegate: Rectangle {
            width: playQueueList.width
            height: 50
            color: playQController.CurrentPlayIndex === index ?
                       themePresenter.Listitemselected :
                       themePresenter.Listitem

            Text {
                id: indexText
                text: index + 1
                //anchors.verticalCenter: parent.verticalCenter
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 2
                width: height
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
            }

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

            Text {
                anchors.left: nameText.left
                anchors.top: nameText.bottom
                anchors.bottom: parent.bottom
                font.pointSize: 9
                color: themePresenter.Textcolor
                horizontalAlignment: Text.AlignHCenter
                text: (model.artist + " :: " + model.album).substr(0, parent.width / font.pointSize)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    playQController.play(index)
                }
            }

            Image {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                source: "qrc:/controll/IMAGES/controlls/cancel.svg"
                anchors.margins: 5
                sourceSize.height: height
                sourceSize.width: height

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        playQController.removeFromQueue(model.id);
                    }
                }
            }
        }
    }
}
