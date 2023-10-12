QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorization.cpp \
    bouquet.cpp \
    bouquetsedit.cpp \
    database.cpp \
    main.cpp \
    makingorder.cpp \
    newemployee.cpp \
    order.cpp \
    orderinformation.cpp \
    orderlist.cpp \
    registration.cpp \
    user.cpp

HEADERS += \
    authorization.h \
    bouquet.h \
    bouquetsedit.h \
    database.h \
    makingorder.h \
    newemployee.h \
    order.h \
    orderinformation.h \
    orderlist.h \
    registration.h \
    user.h

FORMS += \
    authorization.ui \
    bouquetsedit.ui \
    makingorder.ui \
    newemployee.ui \
    orderinformation.ui \
    orderlist.ui \
    registration.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
