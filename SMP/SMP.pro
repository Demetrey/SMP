QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Kernel/initializer.cpp \
        Kernel/playbackcontroller.cpp \
        main.cpp

HEADERS += \
    Kernel/initializer.h \
    Kernel/playbackcontroller.h

RESOURCES += qml.qrc

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
    android/res/values/libs.xml

ANDROID_EXTRA_LIBS = \
    $$PWD/../Libs/TagLib/Android/arm64-v8a/libtaglib.so \
    $$PWD/../Libs/TagLib/Android/armeabi-v7a/libtaglib.so \
    $$PWD/../Libs/TagLib/Android/x86/libtaglib.so \
    $$PWD/../Libs/TagLib/Android/x86_64/libtaglib.so \
    $$PWD/../Libs/Bass/Android/arm64-v8a/libbass.so \
    $$PWD/../Libs/Bass/Android/armeabi-v7a/libbass.so \
    $$PWD/../Libs/Bass/Android/x86/libbass.so \
    $$PWD/../Libs/Bass/Android/x86_64/libbass.so

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
