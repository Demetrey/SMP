#ifndef PLAYLISTCOMPOSITION_H
#define PLAYLISTCOMPOSITION_H

#include "base/basemanytomany.h"

class PlaylistComposition : public BaseManyToMany
{
public:
    PlaylistComposition(QString &connectionName);
};

#endif // PLAYLISTCOMPOSITION_H
