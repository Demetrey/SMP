import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import CycleState 1.0

import "../modals/"

Item {
    anchors.fill: parent

    Rectangle {
        id: topSide
        color: themePresenter.Background
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50
        z: 2

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 20

            Button {
                Layout.fillWidth: true
                Layout.minimumWidth: parent.height
                Layout.maximumWidth: parent.height
                Layout.maximumHeight: parent.height
                Layout.minimumHeight: parent.height

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
                    playlistNameEnter.show();
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.minimumWidth: 40
                Layout.maximumHeight: parent.height
                Layout.minimumHeight: parent.height
                color: themePresenter.Background
                border.color: "black"
                border.width: 1
                clip: true

                TextInput {
                    id: searchField
                    anchors.fill: parent
                    anchors.margins: 3
                    font.family: "Arial"
                    font.pixelSize: height / 1.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: themePresenter.Textcolor
                    selectByMouse: true
                }
            }

            Button {
                id: searchBtn
                Layout.fillWidth: true
                Layout.minimumWidth: parent.height
                Layout.maximumWidth: parent.height
                Layout.maximumHeight: parent.height
                Layout.minimumHeight: parent.height

                Image {
                    id: searchImg
                    source: "qrc:/controll/IMAGES/controlls/search.svg"
                    anchors.centerIn: parent
                    width: height
                    height: parent.height
                    anchors.margins: 5
                    sourceSize.height: height
                    sourceSize.width: height
                }

                onClicked: {
                    playlistModel.updateModel(searchField.text);
                    searchField.clear();
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
        model: playlistModel

        delegate: Rectangle {
            width: playQueueList.width
            height: 50
            color: themePresenter.Listitem

            Text {
                id: indexText
                text: index + 1
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 2
                width: height
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
            }

            Text {
                id: nameText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: indexText.right
                anchors.leftMargin: 5
                text: model.name.substr(0, parent.width / font.pointSize)
                verticalAlignment: Text.AlignBottom
                font.pixelSize: 15
                color: themePresenter.Textcolor
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    swipeView.currentIndex = 1;
                    playlistDataModel.updateModel(model.id);
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
                        playlistController.deletePlaylist(model.id);
                        playlistModel.updateModel();
                    }
                }
            }
        }
    }

    DialogWindow {
        id: playlistNameEnter
    }

    Connections {
        target: playlistNameEnter

        function onOkClicked(msg) {
            playlistController.createPlaylist(msg);
            playlistModel.updateModel();
        }
    }
}
