/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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
