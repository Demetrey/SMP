import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    SwipeView {
        id: swipeView
        anchors.fill: parent

        Item {
            id: playPage
            PlayPage {
            }
        }

        Item {
            id: currentPlaylist
            PlayQueue{
            }
        }
    }

    PageIndicator {
        id: pageIndicator
        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: swipeView.horizontalCenter
        interactive: true
        count: swipeView.count
        currentIndex: swipeView.currentIndex

        delegate: Rectangle {
            implicitWidth: 8
            implicitHeight: 8

            radius: width / 2
            color: themePresenter.Textcolor

            opacity: index === pageIndicator.currentIndex ? 0.75 : 0.35

            Behavior on opacity {
                OpacityAnimator {
                    duration: 100
                }
            }
        }


        onCurrentIndexChanged: {
            swipeView.currentIndex = pageIndicator.currentIndex
        }
    }
}
