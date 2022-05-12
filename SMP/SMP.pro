QT += quick svg sql widgets
android: QT += androidextras

CONFIG += c++11 exceptions

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Kernel/initializer.cpp \
        Kernel/kernel.cpp \
        Kernel/playbackcontroller.cpp \
        Kernel/playbackparameters.cpp \
        PlaybackController/playqueuecontroller.cpp \
        PlaybackController/runnable/createqueuetask.cpp \
        PlaybackController/runnable/inserttoqueuetask.cpp \
        PlaybackController/runnable/removefromqueuetask.cpp \
        PlaybackController/runnable/shufflequeue.cpp \
        dbcontroller/Models/mediamodel.cpp \
        dbcontroller/Models/playlistdatamodel.cpp \
        dbcontroller/Models/playlistmodel.cpp \
        dbcontroller/Models/playqueuemodel.cpp \
        dbcontroller/Models/urlmodel.cpp \
        dbcontroller/Tables/album.cpp \
        dbcontroller/Tables/artist.cpp \
        dbcontroller/Tables/artistcomposition.cpp \
        dbcontroller/Tables/base/basemanytomany.cpp \
        dbcontroller/Tables/base/basetable.cpp \
        dbcontroller/Tables/composition.cpp \
        dbcontroller/Tables/playbackqueue.cpp \
        dbcontroller/Tables/playlist.cpp \
        dbcontroller/Tables/playlistcomposition.cpp \
        dbcontroller/Tables/urlaudio.cpp \
        dbcontroller/basecontroller.cpp \
        dbcontroller/compositioncontroller.cpp \
        dbcontroller/dbconnect.cpp \
        dbcontroller/dbnames.cpp \
        dbcontroller/playlistcontroller.cpp \
        dbcontroller/queuecontroller.cpp \
        filegetter/androidgetter.cpp \
        filegetter/filegetter.cpp \
        filegetter/getfilestask.cpp \
        main.cpp \
        mimetyper/mimetyper.cpp \
        presenters/imagepresenter.cpp \
        presenters/kernelpresenter.cpp \
        readers/xmlloader.cpp \
        tagreader/taggetter.cpp \
        tagreader/tagreader.cpp

HEADERS += \
    Kernel/IKernel.h \
    Kernel/initializer.h \
    Kernel/kernel.h \
    Kernel/kernelstate.h \
    Kernel/playbackcontroller.h \
    Kernel/playbackparameters.h \
    PlaybackController/cyclestate.h \
    PlaybackController/playqueuecontroller.h \
    PlaybackController/runnable/createqueuetask.h \
    PlaybackController/runnable/inserttoqueuetask.h \
    PlaybackController/runnable/removefromqueuetask.h \
    PlaybackController/runnable/shufflequeue.h \
    dbcontroller/Interfaces/IBaseController.h \
    dbcontroller/Interfaces/ICompositionController.h \
    dbcontroller/Interfaces/IPlaybackQueueController.h \
    dbcontroller/Interfaces/IPlaylistController.h \
    dbcontroller/Models/mediamodel.h \
    dbcontroller/Models/playlistdatamodel.h \
    dbcontroller/Models/playlistmodel.h \
    dbcontroller/Models/playqueuemodel.h \
    dbcontroller/Models/urlmodel.h \
    dbcontroller/Tables/album.h \
    dbcontroller/Tables/artist.h \
    dbcontroller/Tables/artistcomposition.h \
    dbcontroller/Tables/base/basemanytomany.h \
    dbcontroller/Tables/base/basetable.h \
    dbcontroller/Tables/composition.h \
    dbcontroller/Tables/playbackqueue.h \
    dbcontroller/Tables/playlist.h \
    dbcontroller/Tables/playlistcomposition.h \
    dbcontroller/Tables/urlaudio.h \
    dbcontroller/basecontroller.h \
    dbcontroller/compositioncontroller.h \
    dbcontroller/dbconnect.h \
    dbcontroller/dbnames.h \
    dbcontroller/playlistcontroller.h \
    dbcontroller/queuecontroller.h \
    filegetter/androidgetter.h \
    filegetter/filegetter.h \
    filegetter/getfilestask.h \
    mimetyper/FileTypes.h \
    mimetyper/mimetyper.h \
    presenters/imagepresenter.h \
    presenters/kernelpresenter.h \
    readers/xmlloader.h \
    tagreader/itagreader.h \
    tagreader/taggetter.h \
    tagreader/tagreader.h \
    tagreader/tagstructs.h

RESOURCES += qml.qrc \
    resources/images.qrc \
    resources/workresources.qrc

CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Linking Windows libraries
win32 {
    contains(QT_ARCH, i386) {
        message("32")
        LIBS += -L$$PWD/../Libs/Bass/Windows/ -lbass
        LIBS += -L$$PWD/../Libs/TagLib/Windows/ -ltaglib
    } else {
        message("64")
        LIBS += -L$$PWD/../Libs/Bass/Windows/x64/ -lbass
        LIBS += -L$$PWD/../Libs/TagLib/Windows/x64/ -ltaglib
    }
}

# Linking Android Libraries
android {
    contains(ANDROID_TARGET_ARCH, arm64-v8a) {
        LIBS += -L$$PWD/../Libs/Bass/Android/arm64-v8a/ -lbass
        LIBS += -L$$PWD/../Libs/TagLib/Android/arm64-v8a/ -ltaglib
    }
    contains(ANDROID_TARGET_ARCH, armeabi-v7a) {
        LIBS += -L$$PWD/../Libs/Bass/Android/armeabi-v7a/ -lbass
        LIBS += -L$$PWD/../Libs/TagLib/Android/armeabi-v7a/ -ltaglib
    }
    contains(ANDROID_TARGET_ARCH, x86) {
        LIBS += -L$$PWD/../Libs/Bass/Android/x86/ -lbass
        LIBS += -L$$PWD/../Libs/TagLib/Android/x86/ -ltaglib
    }
    contains(ANDROID_TARGET_ARCH, x86_64) {
        LIBS += -L$$PWD/../Libs/Bass/Android/x86_64/ -lbass
        LIBS += -L$$PWD/../Libs/TagLib/Android/x86_64/ -ltaglib
    }
}

# Linking Linux Libraries
unix:!macx {
    LIBS += -L$$PWD/../Libs/Bass/Linux/x64/ -lbass
    LIBS += -L$$PWD/../Libs/TagLib/Linux/x64/ -ltaglib
}

INCLUDEPATH += $$PWD/../Libs/TagLib/headers
DEPENDPATH += $$PWD/../Libs/TagLib/headers
INCLUDEPATH += $$PWD/../Libs/Bass
DEPENDPATH += $$PWD/../Libs/Bass

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/com/demetrey/getpath/PathUtil.java

ANDROID_EXTRA_LIBS = \
    $$PWD/../Libs/TagLib/Android/arm64-v8a/libtaglib.so \
    $$PWD/../Libs/Bass/Android/arm64-v8a/libbass.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbassopus.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbassflac.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbassalac.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbassape.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbasshls.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbasswebm.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbasswv.so \
    $$PWD/../Libs/Bass/Android/plugins/arm64-v8a/libbassdsd.so \
    $$PWD/../Libs/TagLib/Android/armeabi-v7a/libtaglib.so \
    $$PWD/../Libs/Bass/Android/armeabi-v7a/libbass.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbassopus.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbassflac.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbassalac.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbassape.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbasshls.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbasswebm.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbasswv.so \
    $$PWD/../Libs/Bass/Android/plugins/armeabi-v7a/libbassdsd.so \
    $$PWD/../Libs/TagLib/Android/x86/libtaglib.so \
    $$PWD/../Libs/Bass/Android/x86/libbass.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbassopus.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbassflac.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbassalac.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbassape.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbasshls.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbasswebm.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbasswv.so \
    $$PWD/../Libs/Bass/Android/plugins/x86/libbassdsd.so \
    $$PWD/../Libs/TagLib/Android/x86_64/libtaglib.so \
    $$PWD/../Libs/Bass/Android/x86_64/libbass.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbassopus.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbassflac.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbassalac.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbassape.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbasshls.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbasswebm.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbasswv.so \
    $$PWD/../Libs/Bass/Android/plugins/x86_64/libbassdsd.so

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
