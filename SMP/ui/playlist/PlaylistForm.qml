import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    SwipeView {
        id: swipeView
        anchors.fill: parent
        interactive: false

        Item {
            id: playlistPage
            PlaylistPage {
                id:playlists
            }
        }

        Item {
            id: currentPlaylistData
            PlaylistData{
            }
        }
    }
}
