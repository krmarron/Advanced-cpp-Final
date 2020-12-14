QT -= gui
QT += sql
QT += network

CONFIG += c++14 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        database.cpp \
        gamerequest.cpp \
        library.cpp \
        multiplayergame.cpp \
        user.cpp \
        videogame.cpp
LIBS += -lws2_32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    database.h \
    gamerequest.h \
    httplib.h \
    httpserver.h \
    library.h \
    multiplayergame.h \
    qtservice.h \
    user.h \
    videogame.h

DISTFILES +=
