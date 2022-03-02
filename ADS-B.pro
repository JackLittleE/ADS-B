QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ModeS/ADSBAirbornePosition.cpp \
    ModeS/ADSBAirborneVelocity.cpp \
    ModeS/ADSBIdentification.cpp \
    ModeS/ADSBSurfacePosition.cpp \
    ModeS/ModeSInfo.cpp \
    main.cpp \
    UI/mainwindow.cpp

HEADERS += \
    ModeS/ADSBAirbornePosition.h \
    ModeS/ADSBAirborneVelocity.h \
    ModeS/ADSBIdentification.h \
    ModeS/ADSBSurfacePosition.h \
    ModeS/ModeSInfo.h \
    ModeS/ModeS.h \
    UI/mainwindow.h

FORMS += \
    UI/mainwindow.ui

RESOURCES += \
	Resource/Map.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
