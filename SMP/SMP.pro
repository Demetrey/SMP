QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Kernel/initializer.cpp \
        main.cpp

HEADERS += \
    Kernel/initializer.h \

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

# Linking Linux Libraries
unix:!macx: LIBS += -L$$PWD/../Libs/Bass/Linux/x64/ -lbass
unix:!macx: LIBS += -L$$PWD/../Libs/TagLib/Linux/x64/ -ltaglib

INCLUDEPATH += $$PWD/../Libs/TagLib/headers
DEPENDPATH += $$PWD/../Libs/TagLib/headers
INCLUDEPATH += $$PWD/../Libs/Bass
DEPENDPATH += $$PWD/../Libs/Bass
