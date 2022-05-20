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

#include "main.h"

int main(int argc, char *argv[]) {
    const int MAX_THREAD_COUNT = 5;
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

    //AFController afController;
#endif

    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    app.setWindowIcon(QIcon(":/ico/IMAGES/icon.ico"));

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
    qmlRegisterType<CycleState>("CycleState", 1, 0, "CycleState");

    QQmlApplicationEngine engine;

    Kernel _kernel;
    IKernel *kernel = &_kernel;
    KernelPresenter kernelPresenter(nullptr, kernel);
    kernel->initialize();
    ImagePresenter *imPresenter = new ImagePresenter();
    CompositionPresenter compositionPresenter;
    PlayQueueController playQController(kernel, queueModel, urlModel, &compositionPresenter, imPresenter);
    ThemePresenter themePresenter;
    FileGetter fileGetter;
    CompositionController compositionController(connectionName);
    PlaylistController playlistController(connectionName);
    PlaylistTaskController pTaskController;
    QmlTranslator qmlTranslator;
    Settings settings(&playQController, &kernelPresenter, &qmlTranslator, &themePresenter);

#ifdef Q_OS_ANDROID
    NWorker nWorker(&kernelPresenter, &playQController, &compositionPresenter);
    AFWorker afWorker(&kernelPresenter);
#endif

    engine.rootContext()->setContextProperty("kernelPresenter", &kernelPresenter);
    engine.rootContext()->setContextProperty("iKernel", kernel);
    engine.rootContext()->setContextProperty("imagePresenter", imPresenter);
    engine.addImageProvider("imgPresenter", imPresenter);
    engine.rootContext()->setContextProperty("compositionPresenter", &compositionPresenter);
    engine.rootContext()->setContextProperty("mediaModel", mediaModel.get());
    engine.rootContext()->setContextProperty("urlModel", urlModel.get());
    engine.rootContext()->setContextProperty("playlistModel", playlistModel.get());
    engine.rootContext()->setContextProperty("playlistDataModel", playlistDataModel.get());
    engine.rootContext()->setContextProperty("queueModel", queueModel.get());
    engine.rootContext()->setContextProperty("playQController", &playQController);
    engine.rootContext()->setContextProperty("themePresenter", &themePresenter);
    engine.rootContext()->setContextProperty("fileGetter", &fileGetter);
    engine.rootContext()->setContextProperty("compositionController", &compositionController);
    engine.rootContext()->setContextProperty("playlistController", &playlistController);
    engine.rootContext()->setContextProperty("pTaskController", &pTaskController);
    engine.rootContext()->setContextProperty("qmlTranslator", &qmlTranslator);
    settings.loadSettings();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
