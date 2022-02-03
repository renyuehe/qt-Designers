QT -= gui

QT += sql
QT += core
#QT += gui xml

#QMAKE_USE += mysql

CONFIG += c++14 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    SqlStr.h \
    SqlGenerator.h

SOURCES += \
    main.cpp \

#INCLUDEPATH += D:/Program_Files/Qt/5.9.8/Src/qtbase/src/plugins/sqldrivers/mysql/include
#LIBS += D:/Program_Files/Qt/5.9.8/Src/qtbase/src/plugins/sqldrivers/mysql/lib/libmysql.lib
