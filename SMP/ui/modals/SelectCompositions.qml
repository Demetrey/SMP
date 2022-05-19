import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: enterNameDialog
    title: titleText
    standardButtons: Dialog.Ok | Dialog.Cancel
    focus: true
    implicitWidth: parent.width
    implicitHeight: parent.height

    property string titleText: qsTr("Title text") + qmlTranslator.EmptyString
    property var selectedIds: []
    property int insertedPlaylistId: -1

    ListView {
        id: mediaView
        anchors.fill: parent
        model: mediaModel

        delegate: Rectangle {
            width: mediaView.width
            height: 50
            color: selectedBox.checked ? themePresenter.Listitemselected : themePresenter.Listitem

            // index
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
            }

            // title
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

            // artist :: album
            Text {
                anchors.left: nameText.left
                anchors.top: nameText.bottom
                anchors.bottom: parent.bottom
                font.pointSize: 9
                color: themePresenter.Textcolor
                horizontalAlignment: Text.AlignHCenter
                text: (model.artist + " :: " + model.album).substr(0, parent.width / font.pointSize)
            }

            // selected or not
            CheckBox {
                id: selectedBox
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                checked: enterNameDialog.selectedIds.indexOf(model.id) !== -1 ? true : false
            }

            // select song
            MouseArea {
                id: fillArea
                anchors.fill: parent
                onClicked: {
                    if (selectedBox.checked) {
                        enterNameDialog.selectedIds.splice(enterNameDialog.selectedIds.indexOf(model.id), 1);
                        console.log(model.id);
                        console.log(enterNameDialog.selectedIds);
                        selectedBox.checked = false;
                    } else {
                        enterNameDialog.selectedIds.push(model.id);
                        console.log(model.id);
                        console.log(enterNameDialog.selectedIds);
                        selectedBox.checked = true;
                    }
                }
            }
        }
    }

    onAccepted: {
        if (enterNameDialog.insertedPlaylistId !== -1) {
            pTaskController.insertToPlaylist(enterNameDialog.selectedIds, enterNameDialog.insertedPlaylistId);
            enterNameDialog.selectedIds = [];
            enterNameDialog.insertedPlaylistId = -1;
        }
    }

    onDiscarded: {
        enterNameDialog.selectedIds = [];
    }

}
