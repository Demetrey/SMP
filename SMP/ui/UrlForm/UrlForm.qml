import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import CycleState 1.0

import "../modals/"
import "../scripts/AdditionalFunctions.js" as AFunc

Item {
    anchors.fill: parent

    // top bar
    Rectangle {
        id: topSide
        color: themePresenter.Background
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50
        z: 2

        // search, add
        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 20

            // add file btn
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
                    id: btnAddImg
                    source: "qrc:/controll/IMAGES/controlls/add.svg"
                    anchors.centerIn: parent
                    width: height
                    height: parent.height
                    anchors.margins: 5
                    sourceSize.height: height
                    sourceSize.width: height
                }

                ColorOverlay {
                   anchors.fill: btnAddImg
                   source: btnAddImg
                   color: themePresenter.Textcolor
               }

                onClicked: {
                    insertUrlDialog.open();
                }
            }

            // search field
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

            // search btn
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
                    urlModel.updateModel(searchField.text);
                    searchField.clear();
                }
            }

        }

    }

    // medialibrary
    ListView {
        id: mediaList
        anchors.top: topSide.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10
        model: urlModel

        delegate: Rectangle {
            width: mediaList.width
            height: 50
            color: playQController.CurrentPlayId === model.id ?
                       themePresenter.Listitemselected :
                       themePresenter.Listitem

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
                color: themePresenter.Textcolor
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

            // select song
            MouseArea {
                id: fillArea
                anchors.fill: parent
                onClicked: {
                    playQController.playURL(index);
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

            // delete song (Fix for context menu)
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

    TwoLineDialog {
        id: insertUrlDialog
        label1Text: qsTr("URL (HTTP/HTTPS/FTP)")
        label2Text: qsTr("Name")
    }

    TwoLineDialog {
        id: updateUrlDialog

        property int currentPlayId: -1

        label1Text: qsTr("URL (HTTP/HTTPS/FTP)")
        label2Text: qsTr("Name")
    }

    Connections {
        target: insertUrlDialog

        function onOkClicked(url, name) {
            compositionController.insertUrl(updateUrlDialog.currentPlayId, url, name);
            urlModel.updateModel();
        }
    }

    Connections {
        target: updateUrlDialog

        function onOkClicked(url, name) {
            compositionController.updateUrl(url, name);
            urlModel.updateModel();
        }
    }

    // context menu
    Menu {
        id: mediaContextMenu

        property int currentPlayId: -1
        property int currentPlayIndex: -1

        Action {
            text: qsTr("Delete") + qmlTranslator.EmptyString;

            onTriggered: {
                compositionController.deleteUrl(mediaContextMenu.currentPlayId);
                urlModel.updateModel();
                mediaContextMenu.currentPlayId = -1;
                mediaContextMenu.currentPlayIndex = -1;
            }
        }

        Action {
            text: qsTr("Update") + qmlTranslator.EmptyString;

            onTriggered: {
                updateUrlDialog.open();
                mediaContextMenu.currentPlayId = -1;
                mediaContextMenu.currentPlayIndex = -1;
            }
        }
    }
}
