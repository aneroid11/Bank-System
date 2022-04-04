QT       += core gui sql

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
    administrator.cpp \
    adminpersonalaccountwindow.cpp \
    authorizationwindow.cpp \
    banksystemmodel.cpp \
    client.cpp \
    clientaccountswindow.cpp \
    clientcreditswindow.cpp \
    clientdepositswindow.cpp \
    clientinstallmentswindow.cpp \
    clientpersonalaccountwindow.cpp \
    database.cpp \
    enterprisespecialist.cpp \
    hashcomputer.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    managerpersonalaccountwindow.cpp \
    operator.cpp \
    operatorpersonalaccountwindow.cpp \
    signuprequestswindow.cpp \
    signupwindow.cpp \
    somethingholdingmoney.cpp \
    user.cpp

HEADERS += \
    administrator.h \
    adminpersonalaccountwindow.h \
    authorizationwindow.h \
    banksystemmodel.h \
    cannotopendbexception.h \
    client.h \
    clientaccountswindow.h \
    clientcreditswindow.h \
    clientdepositswindow.h \
    clientinstallmentswindow.h \
    clientpersonalaccountwindow.h \
    database.h \
    dbexception.h \
    dbnotopenedexception.h \
    enterprisespecialist.h \
    hashcomputer.h \
    ibanksystemmodel.h \
    mainwindow.h \
    manager.h \
    managerpersonalaccountwindow.h \
    nouserindbexception.h \
    operator.h \
    operatorpersonalaccountwindow.h \
    signuprequestswindow.h \
    signupwindow.h \
    somethingholdingmoney.h \
    user.h \
    useralreadyexistsexception.h \
    wronguserpasswordexception.h

LIBS += -lcrypto++# -lsqlite3

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
