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
    addadminrequest.cpp \
    addsubmissionrequest.cpp \
    addteammemberrequest.cpp \
    addusertochatrequest.cpp \
    admin.cpp \
    adminlistrequest.cpp \
    afile.cpp \
    amessage.cpp \
    arequest.cpp \
    aresponse.cpp \
    assignment.cpp \
    assignmentsrequest.cpp \
    asubmission.cpp \
    ateam.cpp \
    auser.cpp \
    changeprofilephotorequest.cpp \
    changeteamphotorequest.cpp \
    channelfilerequest.cpp \
    channelrequest.cpp \
    chatsrequest.cpp \
    chatuserlistrequest.cpp \
    createassignmentrequest.cpp \
    createchannelrequest.cpp \
    createdirectmessagechatrequest.cpp \
    creategroupchatrequest.cpp \
    createteamrequest.cpp \
    datatransferhandler.cpp \
    deletegrouprequest.cpp \
    deleteteamrequest.cpp \
    directmessagechat.cpp \
    emptyrequest.cpp \
    errorexception.cpp \
    errorresponse.cpp \
    exception.cpp \
    file.cpp \
    filemessage.cpp \
    filerequest.cpp \
    gradesubmissionrequest.cpp \
    groupchat.cpp \
    iassignment.cpp \
    ichannel.cpp \
    ichat.cpp \
    ifile.cpp \
    imessage.cpp \
    irequest.cpp \
    iresponse.cpp \
    iserializable.cpp \
    isubmission.cpp \
    iteam.cpp \
    iuser.cpp \
    leavedirectchatrequest.cpp \
    leavegroupchatrequest.cpp \
    leaveteamrequest.cpp \
    logger.cpp \
    loginrequest.cpp \
    loginresponse.cpp \
    main.cpp \
    mainwindow.cpp \
    mytcpserver.cpp \
    okresponse.cpp \
    privatechannel.cpp \
    publicchannel.cpp \
    queryhandler.cpp \
    registerrequest.cpp \
    removeuserfromchatrequest.cpp \
    removeuserfromteamrequest.cpp \
    sendmessagechannelrequest.cpp \
    sendmessagerequest.cpp \
    specificassignmentrequest.cpp \
    specificchatrequest.cpp \
    specificteamrequest.cpp \
    submission.cpp \
    submissionsrequest.cpp \
    team.cpp \
    teamsrequest.cpp \
    teamuserlistrequest.cpp \
    textmessage.cpp \
    updateprofilerequest.cpp \
    user.cpp \
    workerthread.cpp

HEADERS += \
    aassignment.h \
    achannel.h \
    achat.h \
    addadminrequest.h \
    addsubmissionrequest.h \
    addteammemberrequest.h \
    addusertochatrequest.h \
    admin.h \
    adminlistrequest.h \
    afile.h \
    amessage.h \
    arequest.h \
    aresponse.h \
    assignment.h \
    assignmentsrequest.h \
    asubmission.h \
    ateam.h \
    auser.h \
    changeprofilephotorequest.h \
    changeteamphotorequest.h \
    channelfilerequest.h \
    channelrequest.h \
    chatsrequest.h \
    chatuserlistrequest.h \
    createassignmentrequest.h \
    createchannelrequest.h \
    createdirectmessagechatrequest.h \
    creategroupchatrequest.h \
    createteamrequest.h \
    datatransferhandler.h \
    deletegrouprequest.h \
    deleteteamrequest.h \
    directmessagechat.h \
    emptyrequest.h \
    errorexception.h \
    errorresponse.h \
    exception.h \
    file.h \
    filemessage.h \
    filerequest.h \
    gradesubmissionrequest.h \
    groupchat.h \
    iassignment.h \
    ichannel.h \
    ichat.h \
    ifile.h \
    imessage.h \
    irequest.h \
    iresponse.h \
    iserializable.h \
    isubmission.h \
    iteam.h \
    iuser.h \
    leavedirectchatrequest.h \
    leavegroupchatrequest.h \
    leaveteamrequest.h \
    logger.h \
    loginrequest.h \
    loginresponse.h \
    mainwindow.h \
    mytcpserver.h \
    okresponse.h \
    privatechannel.h \
    publicchannel.h \
    queryhandler.h \
    registerrequest.h \
    removeuserfromchatrequest.h \
    removeuserfromteamrequest.h \
    sendmessagechannelrequest.h \
    sendmessagerequest.h \
    specificassignmentrequest.h \
    specificchatrequest.h \
    specificteamrequest.h \
    submission.h \
    submissionsrequest.h \
    team.h \
    teamsrequest.h \
    teamuserlistrequest.h \
    textmessage.h \
    updateprofilerequest.h \
    user.h \
    workerthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
