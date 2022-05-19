#ifndef MAIN_H
#define MAIN_H

// kernel
#include "Kernel/kernelstate.h"
#include "Kernel/kernel.h"
#include "presenters/kernelpresenter.h"
#include "presenters/imagepresenter.h"
// database
#include "dbcontroller/compositioncontroller.h"
#include "dbcontroller/playlistcontroller.h"
#include "dbcontroller/queuecontroller.h"
#include "dbcontroller/Models/mediamodel.h"
#include "dbcontroller/Models/playlistdatamodel.h"
#include "dbcontroller/Models/playlistmodel.h"
#include "dbcontroller/Models/playqueuemodel.h"
#include "dbcontroller/Models/urlmodel.h"
// file picker
#include "PlaybackController/playqueuecontroller.h"
#include "filegetter/filegetter.h"
// presenters
#include "presenters/themepresenter.h"
#include "presenters/compositionpresenter.h"
#include "PlaybackController/cyclestate.h"
// controllers
#include "playlisttaskcontroller/playlisttaskcontroller.h"
#include "translator/qmltranslator.h"
#include "notificationcontroller/nworker.h"
#include "afcontroller/afworker.h"
#include "settings/settings.h"

#endif // MAIN_H
