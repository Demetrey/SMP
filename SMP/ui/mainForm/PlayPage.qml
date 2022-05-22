/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

import kernelState 1.0

// Страница воспроизведения
Item {
    id: basePlayPage
    anchors.fill: parent
    property int marginSize: 40

    GridLayout {
        anchors.fill: parent
        rowSpacing: 20
        columnSpacing: 20
        flow: (width > height ? GridLayout.LeftToRight : GridLayout.TopToBottom)
        anchors.margins: marginSize

        // Cover art (обложка альбома)
        Item {
            id: vizBase
            Layout.fillWidth: true
            Layout.fillHeight: true

            property int vizCount: 75

            // Load image or visualizer (загрузка обложки или визуализатора)
            Loader {
                id: imgLoader
                anchors.fill: parent
                sourceComponent: art

                onWidthChanged: {
                    if (typeof(imgLoader.item.isImage) == "undefined") {
                        imgLoader.item.columnSize = imgLoader.width / vizBase.vizCount;
                    }
                }
            }

            // Событие загрузки
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // this is visualizer, load image
                    if (typeof(imgLoader.item.isImage) != "undefined") {
                        imgLoader.source = "qrc:/ui/visualizer/visualizer.qml";
                        imgLoader.item.columnSize = imgLoader.width / vizBase.vizCount;
                        imgLoader.item.dynamicAdd(vizBase.vizCount);
                    } else {
                        imgLoader.sourceComponent = art;
                    }
                }
            }
        }

        // Title, artist, timeline
        Item {
            Layout.fillWidth: true
            height: isAndroid ? 170 : 150

            Item {
                id: compositionData
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 70

                // title
                Text {
                    id: songTitle
                    color: themePresenter.Textcolor
                    font.pixelSize: 15
                    text: compositionPresenter.Title
                    font.bold: true
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                // artist
                Text {
                    id: artistName
                    color: themePresenter.Textcolor
                    font.pixelSize: 15
                    text: compositionPresenter.Artisr
                    anchors.top: songTitle.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                // timeline
                Item {
                    id: timeLine
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.top: artistName.bottom
                    anchors.margins: 10

                    // current time
                    Text {
                        id: current
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        text: kernelPresenter.CurrentTime <= 0 ? "00:00" :
                                         getCurrentTime(kernelPresenter.CurrentTime)
                        font.family: "Consolas"
                        color: themePresenter.Textcolor
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 15
                    }

                    // all composition time
                    Text {
                        id: allTime
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: kernelPresenter.CompositionTime <= 0 ? "00:00" :
                                     getCurrentTime(kernelPresenter.CompositionTime)
                        font.family: "Consolas"
                        color: themePresenter.Textcolor
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 15
                    }

                    // timeline
                    Slider {
                        id: timeSlider
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: current.right
                        anchors.right: allTime.left
                        from: 0
                        to: kernelPresenter.CompositionTime
                        stepSize: 1
                        value: kernelPresenter.CurrentTime
                        onMoved:  {
                            iKernel.setTime(timeSlider.value);
                        }
                    }
                }
            }

            // volume icon (volume off)
            Image {
                id: volumeOff
                anchors.top: compositionData.bottom
                anchors.left: parent.left
                anchors.leftMargin: 5
                height: 20
                width: height
                source: kernelPresenter.Volume  > 0 ?
                            "qrc:/controll/IMAGES/controlls/volume_up.svg" :
                            "qrc:/controll/IMAGES/controlls/volume_off.svg"
                sourceSize.width: width
                sourceSize.height: height

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        kernelPresenter.Volume = 0;
                    }
                }
            }

            ColorOverlay {
               anchors.fill: volumeOff
               source: volumeOff
               color: themePresenter.Textcolor
           }

            // volume
            Slider {
                id: volumeLevel
                anchors.top: compositionData.bottom
                anchors.left: volumeOff.right
                anchors.right: parent.right
                anchors.rightMargin: 20
                height: 20

                from: 0
                to: 100
                value: kernelPresenter.Volume

                onMoved: {
                    kernelPresenter.Volume = value;
                }
            }

            // control buttons
            Item {
                anchors.top: volumeLevel.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.bottom: parent.bottom

                // play button
                Button {
                    id: btnPlay
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height
                    width: parent.height

                    Image {
                        id: btnPlayImg
                        source: kernelPresenter.Statement === KernelState.Play ?
                                    "qrc:/controll/IMAGES/controlls/pause.svg" :
                                    "qrc:/controll/IMAGES/controlls/play.svg"
                        anchors.fill: parent
                        anchors.margins: 10
                        sourceSize.width: width
                        sourceSize.height: height
                    }

                    ColorOverlay {
                       anchors.fill: btnPlayImg
                       source: btnPlayImg
                       color: themePresenter.Textcolor
                   }

                    onClicked: {
                        kernelPresenter.Statement === KernelState.Play ?
                                    kernelPresenter.pause() :
                                    kernelPresenter.play();
                    }


                }

                // play prev button
                Button {
                    id: btnPrev
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: btnPlay.left
                    anchors.rightMargin: 5
                    height: btnPlay.height / 3 * 2
                    width: height

                    Image {
                        id: btnPrevImg
                        source: "qrc:/controll/IMAGES/controlls/arrow_back.svg"
                        anchors.fill: parent
                        anchors.margins: 10
                        anchors.leftMargin: parent.width / 3
                        sourceSize.width: width
                        sourceSize.height: height
                    }

                    ColorOverlay {
                       anchors.fill: btnPrevImg
                       source: btnPrevImg
                       color: themePresenter.Textcolor
                   }

                    onClicked: {
                        playQController.prevFile();
                    }
                }

                // play next button
                Button {
                    id: btnNext
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: btnPlay.right
                    anchors.leftMargin: 5
                    height: btnPlay.height / 3 * 2
                    width: height

                    Image {
                        id: btnNextImg
                        source: "qrc:/controll/IMAGES/controlls/arrow_forward.svg"
                        anchors.fill: parent
                        anchors.margins: 10
                        anchors.leftMargin: parent.width / 4
                        sourceSize.width: width
                        sourceSize.height: height
                    }

                    ColorOverlay {
                       anchors.fill: btnNextImg
                       source: btnNextImg
                       color: themePresenter.Textcolor
                   }

                    onClicked: {
                        playQController.nextFile();
                    }
                }
            }
        }
    }

    // album cover art
    Component {
        id: art
        Item {
            anchors.centerIn: parent
            width: parent.width < parent.height ? parent.width : parent.height
            height: parent.width < parent.height ? parent.width : parent.height
            property bool isImage: true

            Image {
                id: coverImage
                property int num: 0
                property string currenImage: "image://imgPresenter/image"
                anchors.fill: parent
                source: currenImage
                sourceSize.width: parent.width
                sourceSize.height: parent.height

                function update() {
                    if (num === 1)
                        num--;
                    else
                        num++;
                    source = "image://imgPresenter/image/" + num;
                    source = Qt.binding(function() { return currenImage });
                }

                Connections {
                    target: imagePresenter
                    function onImageChanged() {
                        console.log("new image");
                        coverImage.update();
                    }
                }
            }
        }
    }

    // Representing the current time in a given format
    function getCurrentTime(numTime) {
        let min = numTime / 1000 / 60;
        let secD = min % 1;
        let sec = Math.floor(secD * 60);
        if (sec < 10) {
            sec = "0" + sec;
        }
        min = Math.floor(min);
        if (min < 10) {
            min = "0" + min;
        }
        return min + ":" + sec;
    }
}
