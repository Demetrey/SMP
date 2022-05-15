import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    anchors.fill: parent



    Column {
        id: deviceSettings
        anchors.fill: parent
        spacing: 10

        RowLayout {
            width: parent.width
            height: 40

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width / 4
                color: themePresenter.Textcolor
                text: qsTr("Playback devices:")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
            }

            ComboBox {
                id: currentDevice
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: iKernel.getDevices();
            }
        }
        RowLayout {
            width: parent.width
            height: 40

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width / 4
                color: themePresenter.Textcolor
                text: qsTr("Sample Rate (Hz):")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 15
            }

            ComboBox {
                id: sampleRate
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: sampleRateModel
            }
        }

        Button {
            width: parent.width / 4
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                anchors.fill: parent
                text: qsTr("Apply")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                color: themePresenter.Textcolor
                font.pixelSize: 15
            }

            onClicked: {
                iKernel.initDevice(currentDevice.currentValue, sampleRate.currentValue);
            }
        }
    }

    ListModel {
        id: sampleRateModel

        ListElement {sampleRateF: 44100}
        ListElement {sampleRateF: 48000}
        ListElement {sampleRateF: 88200}
        ListElement {sampleRateF: 96000}
        ListElement {sampleRateF: 176400}
        ListElement {sampleRateF: 192000}
    }
}
