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

        Button {
            width: height
            height: parent.height

            Image {
                id: shuffleBtnImage
                source: "qrc:/controll/IMAGES/controlls/add.svg"
                anchors.centerIn: parent
                width: height
                height: parent.height
                anchors.margins: 5
                sourceSize.height: height
                sourceSize.width: height
            }

            onClicked: {
                fileGetter.getFiles();
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
        model: mediaModel

        delegate: Rectangle {
            width: playQueueList.width
            height: 50
            color: playQController.CurrentPlayId === model.id ?
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
                    playQController.CurrentPlayId = model.id
                    playQController.createQueue(0);
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
                        compositionController.deleteComposition(model.id);
                        playQController.compositionRemoved();
                        mediaModel.updateModel();
                    }
                }
            }
        }
    }
}