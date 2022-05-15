import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import CycleState 1.0

import "../modals/"
import "../scripts/AdditionalFunctions.js" as AFunc

Item {
    anchors.fill: parent

    property int currentPlaylistId: 1

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

                background: Rectangle {
                    color: "#00000000"
                }

                Image {
                    id: addBtnImg
                    source: "qrc:/controll/IMAGES/controlls/add.svg"
                    anchors.centerIn: parent
                    width: height
                    height: parent.height
                    anchors.margins: 5
                    sourceSize.height: height
                    sourceSize.width: height
                }

                ColorOverlay {
                   anchors.fill: addBtnImg
                   source: addBtnImg
                   color: themePresenter.Textcolor
               }

                onClicked: {
                    enterNameDialog.open();
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

                background: Rectangle {
                    color: "#00000000"
                }

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

                ColorOverlay {
                   anchors.fill: searchImg
                   source: searchImg
                   color: themePresenter.Textcolor
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
                id: fillArea
                anchors.fill: parent
                onClicked: {
                    console.log(model.id)
                    currentPlaylistId = model.id;
                    swipeView.currentIndex = 1;
                    playlistDataModel.updateModel(model.id);
                }

                onPressAndHold: {
                    var absolutePos = AFunc.getAbsolutePosition(fillArea);
                    mediaContextMenu.currentPlayListId = model.id;
                    mediaContextMenu.currentPlayListIndex = index;
                    mediaContextMenu.x =  absolutePos.x + mouseX;
                    mediaContextMenu.y = absolutePos.y;
                    mediaContextMenu.open();
                }
            }

            Image {
                id: moreImg
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                source: "qrc:/controll/IMAGES/controlls/more_horiz.svg"
                anchors.margins: 5
                sourceSize.height: height
                sourceSize.width: height

                MouseArea {
                    id: rightArea
                    anchors.fill: parent

                    onClicked: {
                        var absolutePos = AFunc.getAbsolutePosition(rightArea);
                        mediaContextMenu.currentPlayListId = model.id;
                        mediaContextMenu.currentPlayListIndex = index;
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
    }

    DialogWindow {
        id: enterNameDialog
        titleText: qsTr("Enter playlist name") + qmlTranslator.EmptyString
    }

    DialogWindow {
        id: renameDialog

        property int curplaylistId: -1

        titleText: qsTr("Enter playlist name") + qmlTranslator.EmptyString
    }

    Connections {
        target: enterNameDialog

        function onOkClicked(msg) {
            playlistController.createPlaylist(msg);
            playlistModel.updateModel();
        }
    }

    Connections {
        target: renameDialog

        function onOkClicked(msg) {
            if (renameDialog.curplaylistId !== -1) {
                playlistController.updatePlaylist(renameDialog.curplaylistId, msg);
                playlistModel.updateModel();
                renameDialog.curplaylistId = -1;
            }
        }
    }

    // context menu
    Menu {
        id: mediaContextMenu

        property int currentPlayListId: -1
        property int currentPlayListIndex: -1

        Action {
            text: qsTr("Delete") + qmlTranslator.EmptyString;

            onTriggered: {
                playlistController.deletePlaylist(mediaContextMenu.currentPlayListId);
                playlistModel.updateModel();
                mediaContextMenu.currentIndex = -1;
                mediaContextMenu.currentPlayListId = -1;
            }
        }

        Action {
            text: qsTr("Rename") + qmlTranslator.EmptyString

            onTriggered: {
                renameDialog.curplaylistId = mediaContextMenu.currentPlayListId;
                renameDialog.open();
                mediaContextMenu.currentIndex = -1;
                mediaContextMenu.currentPlayListId = -1;
            }
        }
    }
}
