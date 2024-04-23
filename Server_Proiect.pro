QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aassignment.cpp \
    achannel.cpp \
    achat.cpp \
    amessage.cpp \
    asubmission.cpp \
    ateam.cpp \
    chatsrequest.cpp \
    clientthread.cpp \
    createdirectmessagechatrequest.cpp \
    directmessagechat.cpp \
    filemessage.cpp \
    groupchat.cpp \
    iassignment.cpp \
    ichannel.cpp \
    ichat.cpp \
    imessage.cpp \
    irequest.cpp \
    iserializable.cpp \
    isubmission.cpp \
    iteam.cpp \
    logger.cpp \
    loginrequest.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpserver.cpp \
    queryhandler.cpp \
    registerrequest.cpp \
    sendmessagerequest.cpp \
    textmessage.cpp \
    updateprofilerequest.cpp \
    user.cpp

HEADERS += \
    aassignment.h \
    achannel.h \
    achat.h \
    amessage.h \
    asubmission.h \
    ateam.h \
    chatsrequest.h \
    clientthread.h \
    createdirectmessagechatrequest.h \
    directmessagechat.h \
    filemessage.h \
    groupchat.h \
    iassignment.h \
    ichannel.h \
    ichat.h \
    imessage.h \
    irequest.h \
    iserializable.h \
    isubmission.h \
    iteam.h \
    logger.h \
    loginrequest.h \
    mainwindow.h \
    mytcpserver.h \
    queryhandler.h \
    registerrequest.h \
    sendmessagerequest.h \
    textmessage.h \
    updateprofilerequest.h \
    user.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
