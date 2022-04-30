/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>

#include "Kernel/kernelstate.h"
#include "Kernel/kernel.h"
#include "presenters/kernelpresenter.h"

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SMP_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    qmlRegisterType<KernelState>("kernelState", 1, 0, "KernelState");
    qmlRegisterType<KernelPresenter>("kPresenter", 1, 0, "KPresenter");
    qmlRegisterInterface<IKernel>("IKernel", 1);

    QQmlApplicationEngine engine;

    Kernel _kernel;
    IKernel *kernel = &_kernel;
    KernelPresenter kp(nullptr, kernel);
    kernel->initialize();
    engine.rootContext()->setContextProperty("kp", &kp);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
