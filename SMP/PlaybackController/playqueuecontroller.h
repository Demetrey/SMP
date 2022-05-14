#ifndef PLAYQUEUECONTROLLER_H
#define PLAYQUEUECONTROLLER_H

#include <QObject>
#include <QSharedPointer>
#include <QThreadPool>

#include "Kernel/IKernel.h"
#include "dbcontroller/queuecontroller.h"
#include "dbcontroller/playlistcontroller.h"
#include "dbcontroller/Models/playqueuemodel.h"
#include "dbcontroller/Models/playlistmodel.h"
#include "dbcontroller/Models/playlistdatamodel.h"
#include "dbcontroller/Models/urlmodel.h"

#include "runnable/createqueuetask.h"
#include "runnable/inserttoqueuetask.h"
#include "runnable/removefromqueuetask.h"
#include "runnable/shufflequeue.h"
#include "runnable/getarttask.h"

#include "presenters/compositionpresenter.h"
#include "presenters/imagepresenter.h"

#include "cyclestate.h"

class PlayQueueController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int CurrentPlayId READ CurrentPlayId WRITE setCurrentPlayId NOTIFY CurrentPlayIdChanged)
    Q_PROPERTY(bool IsFile READ IsFile WRITE setIsFile NOTIFY IsFileChanged)
    Q_PROPERTY(int CurrentPlayIndex READ CurrentPlayIndex WRITE setCurrentPlayIndex NOTIFY CurrentPlayIndexChanged)
    Q_PROPERTY(CycleState::Cycle CurrentSycle READ CurrentSycle WRITE setCurrentSycle NOTIFY CurrentSycleChanged)
    Q_PROPERTY(bool IsShuffled READ IsShuffled WRITE setIsShuffled NOTIFY IsShuffledChanged)

public:
    explicit PlayQueueController(IKernel *kernel,
                                 QSharedPointer<PlayQueueModel> queueModel,
                                 QSharedPointer<UrlModel> urlModel,
                                 CompositionPresenter *compositionPresenter,
                                 ImagePresenter *imagePresenter,
                                 QObject *parent = nullptr);

    int CurrentPlayId() const;
    void setCurrentPlayId(int newCurrentPlayId);
    bool IsFile() const;
    void setIsFile(bool newIsFile);
    int CurrentPlayIndex() const;
    void setCurrentPlayIndex(int newCurrentPlayIndex);
    const CycleState::Cycle &CurrentSycle() const;
    void setCurrentSycle(const CycleState::Cycle &newCurrentSycle);
    bool IsShuffled() const;
    void setIsShuffled(bool newIsShuffled);

public slots:
    void createQueue(int id);       // Создать очередь из плейлиста или медиатеки
    void insertToQueue(int id);     // Добавить файлик в очередь
    void removeFromQueue(int id);   // Удалить файлик из очереди

    void onCreatedQueue();
    void onInsertCompleted();
    void onRemovedFromQueue();

    void onShuffledQueue();

    void onCompletedArt(QImage result);

    void onEndOfFile();             // Переключиться на следующий файл после завершения текущего

    void play(int index);           // Играть выбранный из очереди файл
    void playURL(int index);           // Играть выбранный из списка URL
    void nextFile();                // Перейти на следующий файл
    void prevFile();                // Перейти на предыдущий файл
    void cycle();                   // Зациклить воспроизведение очереди/файла
    void shuffle();                 // Перемешать очередь
    void shuffleBack();             // Отменить перемешивание
    void compositionRemoved();    // Удалено из медиатеки, удаление из плейлиста не рассматривается

signals:
    void startCreateQueue();
    void createdQueue();
    void changedQueue();

    void startInsertToQueue();
    void endInsertToQueue();

    void startRemoveFromQueue();
    void stopRemoveFromQueue();

    void startShuffle();
    void endShuffle();

    void CurrentPlayIdChanged();
    void IsFileChanged();
    void CurrentPlayIndexChanged();
    void CurrentSycleChanged();
    void IsShuffledChanged();

private:
    IKernel* kernel;
    QSharedPointer<PlayQueueModel> queueModel;
    QSharedPointer<UrlModel> urlModel;
    CompositionPresenter *compositionPresenter;
    ImagePresenter *imagePresenter;
    CycleState::Cycle m_CurrentSycle;

    int m_CurrentPlayId;
    bool m_IsFile;
    int m_CurrentPlayIndex;
    bool m_IsShuffled;

    void updateIndex();
    void updateImage();

};

#endif // PLAYQUEUECONTROLLER_H
