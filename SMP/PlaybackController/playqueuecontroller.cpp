/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playqueuecontroller.h"

PlayQueueController::PlayQueueController(IKernel *kernel,
                                         QSharedPointer<PlayQueueModel> queueModel,
                                         QSharedPointer<UrlModel> urlModel,
                                         CompositionPresenter *compositionPresenter,
                                         ImagePresenter *imagePresenter,
                                         QObject *parent)
    : QObject(parent) {
    this->kernel = kernel;
    this->queueModel = queueModel;
    this->urlModel = urlModel;
    this->compositionPresenter = compositionPresenter;
    this->imagePresenter = imagePresenter;
    this->m_CurrentPlayId = -1;
    this->m_CurrentPlayIndex = -1;
    this->m_CurrentSycle = CycleState::Cycle::CycleNo;
    this->m_IsFile = true;
    this->m_IsShuffled = false;

    connect(this->kernel, SIGNAL(endOfFile()), this, SLOT(onEndOfFile()));
}

/**
 * @brief Создание очереди по ID плейлиста
 * @param id плейлиста
 */
void PlayQueueController::createQueue(int id) {
    emit startCreateQueue();
    CreateQueueTask* task = new CreateQueueTask(id);
    connect(task, SIGNAL(createdQueue()), this, SLOT(onCreatedQueue()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}

/**
 * @brief Добавление в очередь по id композиции
 *
 * При добавлении композиции необходимо обновить текущий индекс воспроизведения
 *
 * @param id композиции
 */
void PlayQueueController::insertToQueue(int id) {
    emit startInsertToQueue();
    InsertToQueueTask *task = new InsertToQueueTask(id);
    connect(task, SIGNAL(insertCompleted()), this, SLOT(onInsertCompleted()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}

/**
 * @brief Удаление из очереди по id композиции
 *
 * При удалении композиции необходимо обновить текущий индекс воспроизведения
 *
 * @param id композиции
 */
void PlayQueueController::removeFromQueue(int id) {
    emit startRemoveFromQueue();
    RemoveFromQueueTask *task = new RemoveFromQueueTask(id);
    connect(task, SIGNAL(removedCompleted()), this, SLOT(onRemovedFromQueue()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}

void PlayQueueController::shuffle() {
    emit startShuffle();
    ShuffleQueue *task = new ShuffleQueue(m_CurrentPlayId);
    connect(task, SIGNAL(shuffledQueue()), this, SLOT(onShuffledQueue()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}

void PlayQueueController::shuffleBack() {
    setIsShuffled(false);
    queueModel->updateModel(m_IsShuffled);
    updateIndex();
    emit endShuffle();
    emit changedQueue();
}

void PlayQueueController::compositionRemoved() {
    queueModel->updateModel(m_IsShuffled);
    updateIndex();
}

/**
 * @brief Создание очереди завершено в отдельном потоке
 */
void PlayQueueController::onCreatedQueue() {
    kernel->stop();
    setIsShuffled(false);
    queueModel->updateModel(m_IsShuffled);
    updateIndex();
    play(m_CurrentPlayIndex);
    emit createdQueue();
    emit changedQueue();
    setIsFile(true);
}

/**
 * @brief Добавление в очередь завершено в отдельном потоке
 */
void PlayQueueController::onInsertCompleted() {
    queueModel->updateModel(m_IsShuffled);
    updateIndex();
    emit endInsertToQueue();
    emit changedQueue();
}

/**
 * @brief Удаление из очереди завершено в отдельном потоке
 */
void PlayQueueController::onRemovedFromQueue() {
    queueModel->updateModel(m_IsShuffled);
    updateIndex();
    emit stopRemoveFromQueue();
    emit changedQueue();
}

void PlayQueueController::onShuffledQueue() {
    setIsShuffled(true);
    queueModel->updateModel(m_IsShuffled);
    updateIndex();
    emit endShuffle();
    emit changedQueue();
}

void PlayQueueController::onCompletedArt(QImage result) {
    qDebug() << "onCompleted" << result;
    imagePresenter->updateImage(result);
}

/**
 * @brief Достигнут конец файла при воспроизведении
 *
 * Может быть конец очереди
 * Может быть переход на следующий файл
 * Может быть переход на начало
 * В любом случае это должно быть реализовано в NEXT FILE
 */
void PlayQueueController::onEndOfFile() {
    qDebug() << "PQ end of file!!!";
    if (m_IsFile) {
        qDebug() << "Next File";
        nextFile();
    }
    else {
        kernel->stop();
    }
}

/**
 * @brief Играть файл из очереди с указанным индексом
 * @param index
 */
void PlayQueueController::play(int index) {
    if (queueModel->rowCount() > 0) {
        QString path = queueModel->data(queueModel->index(index, 0), queueModel->pathRole).toString();
        if (!path.isNull() && !path.isEmpty()) {
            setIsFile(true);

            kernel->play(path, m_IsFile);
            setCurrentPlayId(queueModel->getId(index));
            setCurrentPlayIndex(index);

            compositionPresenter->setAlbum
                    (queueModel->data(queueModel->index(index, 0),
                                      queueModel->albumRole).toString());
            compositionPresenter->setArtists
                    (queueModel->data(queueModel->index(index, 0),
                                      queueModel->artistRole).toString());
            compositionPresenter->setTitle
                    (queueModel->data(queueModel->index(index, 0),
                                      queueModel->nameRole).toString());
            compositionPresenter->setYear
                    (queueModel->data(queueModel->index(index, 0),
                                      queueModel->yearRole).toInt());
            updateImage();
        }
    }
}

/**
 * @brief Играем URL
 * @param index индекс URL в модели
 */
void PlayQueueController::playURL(int index) {
    if (urlModel->rowCount() > 0) {
        setIsFile(false);
        QString path = urlModel->data(urlModel->index(index, 0), urlModel->urlRole).toString();
        if (!path.isNull() && !path.isEmpty()) {
            qDebug() << "url" << path;
            kernel->play(path, m_IsFile);
            setCurrentPlayId(urlModel->getId(index));

            compositionPresenter->setAlbum("...");
            compositionPresenter->setArtists("...");
            compositionPresenter->setTitle
                    (urlModel->data(urlModel->index(index, 0),
                                    urlModel->nameRole).toString());
            compositionPresenter->setYear(0);
        }
    }
}

/**
 * @brief Переключение на следующий файл в очереди
 */
void PlayQueueController::nextFile() {
    if (!m_IsFile)
        return;
    // Мы не дошли до конца очереди
    // Нет зацикливания по файлу
    // Просто играем файл со следующийм индексом
    if (m_CurrentPlayIndex < queueModel->rowCount() - 1
            && m_CurrentSycle != CycleState::Cycle::CycleOne) {
        setCurrentPlayIndex(m_CurrentPlayIndex + 1);
        setCurrentPlayId(queueModel->getId(m_CurrentPlayIndex));
    }
    // Мы дошли до последнего файла в очереди
    // Нет зацикливания воспроизведения
    // Останавливаем воспроизведение
    else if (m_CurrentPlayIndex == queueModel->rowCount() - 1
             && m_CurrentSycle == CycleState::Cycle::CycleNo) {
        kernel->stop();
        return;
    }
    // Мы дошли до последнего файла в очереди
    // Зацикливание всей очереди
    // Переключаемся на первый файл в очереди
    else if (m_CurrentPlayIndex == queueModel->rowCount() - 1
               && m_CurrentSycle == CycleState::Cycle::CycleQueue) {
        setCurrentPlayIndex(0);
        setCurrentPlayId(queueModel->getId(m_CurrentPlayIndex));
    }
    // Мы на любом файле
    // Мы зациклены на файле
    // Ничего не делаем
    else if (m_CurrentSycle == CycleState::Cycle::CycleOne) {
        return;
    }

    qDebug() << "index" << m_CurrentPlayIndex;
    qDebug() << "id" << m_CurrentPlayId;
    play(m_CurrentPlayIndex);
}

void PlayQueueController::prevFile() {
    if (!m_IsFile)
        return;
    // Мы не дошли до начала очереди
    // Нет зацикливания по файлу
    // Просто играем файл с предыдущим индексом
    if (m_CurrentPlayIndex > 0
            && m_CurrentSycle != CycleState::Cycle::CycleOne) {
        setCurrentPlayIndex(m_CurrentPlayIndex - 1);
        setCurrentPlayId(queueModel->getId(m_CurrentPlayIndex));
    }
    // Мы дошли до первого файла в очереди
    // Нет зацикливания воспроизведения
    // Останавливаем воспроизведение
    else if (m_CurrentPlayIndex == 0
             && m_CurrentSycle == CycleState::Cycle::CycleNo) {
        kernel->stop();
        return;
    }
    // Мы дошли до первого файла в очереди
    // Зацикливание всей очереди
    // Переключаемся на последний файл в очереди
    else if (m_CurrentPlayIndex == 0
               && m_CurrentSycle == CycleState::Cycle::CycleQueue) {
        setCurrentPlayIndex(queueModel->rowCount() - 1);
        setCurrentPlayId(queueModel->getId(m_CurrentPlayIndex));
    }
    // Мы на любом файле
    // Мы зациклены на файле
    // Ничего не делаем
    else if (m_CurrentSycle == CycleState::Cycle::CycleOne) {
        return;
    }

    qDebug() << "index" << m_CurrentPlayIndex;
    qDebug() << "id" << m_CurrentPlayId;
    play(m_CurrentPlayIndex);
}

/**
 * @brief Переключение зацикливания
 */
void PlayQueueController::cycle() {
    switch (m_CurrentSycle) {
    // Состояния проматываются по очереди в указанном порядке
    case CycleState::Cycle::CycleNo:
        setCurrentSycle(CycleState::Cycle::CycleQueue);
        break;
    case CycleState::Cycle::CycleQueue:
        kernel->cycleFile();
        setCurrentSycle(CycleState::Cycle::CycleOne);
        break;
    case CycleState::Cycle::CycleOne:
        kernel->cycleFile();
        setCurrentSycle(CycleState::Cycle::CycleNo);
        break;
    }
}



/**
 * @brief Обновление текущего индекса по модели
 */
void PlayQueueController::updateIndex() {
    bool isCorrect = false;
    for (int i = 0; i < queueModel->rowCount(); i++) {
        if (queueModel->data(queueModel->index(i, 0), queueModel->idRole) == m_CurrentPlayId) {
            isCorrect = true;
            setCurrentPlayIndex(i);
        }
    }
    // Если индекса нет, то файл был удален
    // Уменьшим индекс на 1 и попробуем перейти на следующий файл
    // Даже если текущий индекс будет -1, то переход на следующий файл установит его заново
    if (!isCorrect) {
        m_CurrentPlayIndex--;
        nextFile();
    }
    qDebug() << "index" << m_CurrentPlayIndex;
    qDebug() << "id" << m_CurrentPlayId;
}

void PlayQueueController::updateImage() {
    QString path = queueModel->data(queueModel->index(m_CurrentPlayIndex, 0),
                                    queueModel->pathRole).toString();
    qDebug() << "Composition path" << path;
    GetArtTask* task = new GetArtTask(path);
    connect(task, SIGNAL(completed(QImage)), this, SLOT(onCompletedArt(QImage)));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}




int PlayQueueController::CurrentPlayId() const
{
    return m_CurrentPlayId;
}

void PlayQueueController::setCurrentPlayId(int newCurrentPlayId)
{
    if (m_CurrentPlayId == newCurrentPlayId)
        return;
    m_CurrentPlayId = newCurrentPlayId;
    emit CurrentPlayIdChanged();
}

bool PlayQueueController::IsFile() const
{
    return m_IsFile;
}

void PlayQueueController::setIsFile(bool newIsFile)
{
    if (m_IsFile == newIsFile)
        return;
    m_IsFile = newIsFile;
    emit IsFileChanged();
}

int PlayQueueController::CurrentPlayIndex() const
{
    return m_CurrentPlayIndex;
}

void PlayQueueController::setCurrentPlayIndex(int newCurrentPlayIndex)
{
    if (m_CurrentPlayIndex == newCurrentPlayIndex)
        return;
    m_CurrentPlayIndex = newCurrentPlayIndex;
    emit CurrentPlayIndexChanged();
}

const CycleState::Cycle &PlayQueueController::CurrentSycle() const
{
    return m_CurrentSycle;
}

void PlayQueueController::setCurrentSycle(const CycleState::Cycle &newCurrentSycle)
{
    if (m_CurrentSycle == newCurrentSycle)
        return;
    m_CurrentSycle = newCurrentSycle;
    emit CurrentSycleChanged();
}

bool PlayQueueController::IsShuffled() const
{
    return m_IsShuffled;
}

void PlayQueueController::setIsShuffled(bool newIsShuffled)
{
    if (m_IsShuffled == newIsShuffled)
        return;
    m_IsShuffled = newIsShuffled;
    emit IsShuffledChanged();
}

void PlayQueueController::settingsSet(int id, bool isFile, bool isShuffled) {
    setIsFile(isFile);
    setIsShuffled(isShuffled);
    setCurrentPlayId(id);
    queueModel->updateModel(isShuffled);
    updateIndex();
    play(m_CurrentPlayIndex);
    kernel->pause();
}
