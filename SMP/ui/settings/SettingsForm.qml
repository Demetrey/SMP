import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    anchors.fill: parent
    anchors.margins: 5

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
                Layout.minimumWidth: parent.width / 10
                color: themePresenter.Textcolor
                text: qsTr("Playback devices:")
                verticalAlignment: Text.AlignVCenter
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
                Layout.minimumWidth: parent.width / 10
                color: themePresenter.Textcolor
                text: qsTr("Sample Rate (Hz):")
                verticalAlignment: Text.AlignVCenter
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
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: themePresenter.Textcolor
                font.pixelSize: 15
            }

            onClicked: {
                iKernel.initDevice(currentDevice.currentValue, sampleRate.currentValue);
            }
        }

        RowLayout {
            width: parent.width
            height: 40

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width / 10
                color: themePresenter.Textcolor
                text: qsTr("Sample Rate (Hz):")
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 15
            }

            ComboBox {
                id: currentTheme
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: themePresenter.getThemes();
                currentIndex: themePresenter.CurrentThemeIndex

                onCurrentIndexChanged: {
                    themePresenter.setTheme(currentIndex);
                }
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
