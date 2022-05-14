/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>

#include <QThreadPool>

#include <QQuickStyle>

#include "Kernel/kernelstate.h"
#include "Kernel/kernel.h"
#include "presenters/kernelpresenter.h"
#include "presenters/imagepresenter.h"

#include "dbcontroller/compositioncontroller.h"
#include "dbcontroller/playlistcontroller.h"
#include "dbcontroller/queuecontroller.h"

#include "dbcontroller/Models/mediamodel.h"
#include "dbcontroller/Models/playlistdatamodel.h"
#include "dbcontroller/Models/playlistmodel.h"
#include "dbcontroller/Models/playqueuemodel.h"
#include "dbcontroller/Models/urlmodel.h"

#include "PlaybackController/playqueuecontroller.h"
#include "filegetter/filegetter.h"

#include "presenters/themepresenter.h"
#include "presenters/compositionpresenter.h"

int main(int argc, char *argv[]) {
    const int MAX_THREAD_COUNT = 10;
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_THREAD_COUNT);

    QString connectionName = "main";
    DBConnect dbc(connectionName);
    dbc.connect();

    // composition model
    auto mediaModel =
            QSharedPointer<MediaModel>(new MediaModel(dbc.getDB()));
    auto urlModel =
            QSharedPointer<UrlModel>(new UrlModel(dbc.getDB()));

    // playlist model
    auto playlistModel =
            QSharedPointer<PlaylistModel>(new PlaylistModel(dbc.getDB()));
    auto playlistDataModel =
            QSharedPointer<PlaylistDataModel>(new PlaylistDataModel(dbc.getDB()));

    // queue model
    auto queueModel =
            QSharedPointer<PlayQueueModel>(new PlayQueueModel(dbc.getDB()));


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

#ifdef Q_OS_ANDROID
    // Запрос разрешений на доступ к анешней памяти устройства
    auto result = QtAndroid::checkPermission(QString("android.permission.READ_EXTERNAL_STORAGE"));
    if(result == QtAndroid::PermissionResult::Denied)
    {
        QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.READ_EXTERNAL_STORAGE"}));
        if(resultHash["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
            return 0;
    }
    result = QtAndroid::checkPermission(QString("android.permission.WRITE_EXTERNAL_STORAGE"));
    if(result == QtAndroid::PermissionResult::Denied)
    {
        QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.WRITE_EXTERNAL_STORAGE"}));
        if(resultHash["android.permission.WRITE_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
            return 0;
    }
#endif


    QApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SMP_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // Register types and interfaces
    qmlRegisterType<KernelState>("kernelState", 1, 0, "KernelState");
    qmlRegisterType<KernelPresenter>("kPresenter", 1, 0, "KPresenter");
    qmlRegisterInterface<IKernel>("IKernel", 1);
    qmlRegisterType<KernelPresenter>("compositionController", 1, 0, "CompositionController");
    qmlRegisterType<KernelPresenter>("playlistController", 1, 0, "PlaylistController");
    qmlRegisterType<KernelPresenter>("queueController", 1, 0, "QueueController");
    qmlRegisterType<KernelPresenter>("themePresenter", 1, 0, "ThemePresenter");
    qmlRegisterType<KernelPresenter>("compositionPresenter", 1, 0, "CompositionPresenter");

    QQmlApplicationEngine engine;

    // set context properties
    Kernel _kernel;
    IKernel *kernel = &_kernel;
    KernelPresenter kernelPresenter(nullptr, kernel);
    kernel->initialize();
    engine.rootContext()->setContextProperty("kernelPresenter", &kernelPresenter);
    engine.rootContext()->setContextProperty("iKernel", kernel);
    ImagePresenter *imPresenter = new ImagePresenter();
    engine.rootContext()->setContextProperty("imagePresenter", imPresenter);
    engine.addImageProvider("imgPresenter", imPresenter);


    CompositionPresenter compositionPresenter;
    engine.rootContext()->setContextProperty("compositionPresenter", &compositionPresenter);

    PlayQueueController pq(kernel, queueModel, urlModel, &compositionPresenter, imPresenter);

    engine.rootContext()->setContextProperty("mediaModel", mediaModel.get());
    engine.rootContext()->setContextProperty("urlModel", urlModel.get());
    engine.rootContext()->setContextProperty("playlistModel", playlistModel.get());
    engine.rootContext()->setContextProperty("playlistDataModel", playlistDataModel.get());
    engine.rootContext()->setContextProperty("queueModel", queueModel.get());
    engine.rootContext()->setContextProperty("pq", &pq);

    ThemePresenter themePresenter;
    engine.rootContext()->setContextProperty("themePresenter", &themePresenter);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    /*pq.createQueue(2);*/
    /*FileGetter fg;
    fg.getFiles();*/
    pq.play(0);
    pq.cycle();
    pq.cycle();
    //pq.shuffle();
    //pq.insertToQueue(2428);
    pq.nextFile();
    pq.play(3);

    qDebug() << XmlLoader::loadThem(":/themes/XML/themes/light.xml");

    return app.exec();
}
