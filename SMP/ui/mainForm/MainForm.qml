import QtQuick 2.15
import QtQuick.Controls 2.15

// Основная форма
Item {
    // Поля контента
    SwipeView {
        id: swipeView
        anchors.fill: parent

        // Страница воспроизведения
        Item {
            id: playPage
            PlayPage {
            }
        }

        // Страница очереди воспроизведения
        Item {
            id: currentPlaylist
            PlayQueue{
            }
        }
    }

    // Индикатор страниц
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 12
        color: themePresenter.Background

        PageIndicator {
            id: pageIndicator
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            interactive: true
            count: swipeView.count
            currentIndex: swipeView.currentIndex

            delegate: Rectangle {
                implicitWidth: 15
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
}
