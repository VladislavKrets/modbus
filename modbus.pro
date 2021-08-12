QT += core gui  serialbus  charts  serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeregister.cpp \
    changeregisterthreaddata.cpp \
    chartdata.cpp \
    dialogsettings.cpp \
    main.cpp \
    mainwindow.cpp \
    portinfo.cpp \
    qmodbusrtuserialslavelogger.cpp \
    serialPortSettingsDialog.cpp \
    signalcoefficientdata.cpp \
    signaldialog.cpp \
    signaldialogwidget.cpp

HEADERS += \
    changeregister.h \
    changeregisterthreaddata.h \
    chartdata.h \
    dialogsettings.h \
    mainwindow.h \
    portinfo.h \
    qmodbusrtuserialslavelogger.h \
    serialPortSettingsDialog.h \
    signalcoefficientdata.h \
    signaldialog.h \
    signaldialogwidget.h

FORMS += \
    dialogsettings.ui \
    mainwindow.ui \
    serialPortSettingsDialog.ui \
    signaldialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
