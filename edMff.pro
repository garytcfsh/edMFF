QT += gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
        boxregion.cpp \
        dfn2hybrid.cpp \
        edmff.cpp \
        face.cpp \
        fixhybriddefinition.cpp \
        inputboundaryregion.cpp \
        main.cpp \
        mergefile.cpp \
        modifydefinitionfile.cpp \
        modifyfile.cpp \
        node.cpp \
        searchnodeonregionface.cpp \
        setconstanthead.cpp \
        slabregion.cpp \
        storedefinitionfilenodeonregionface.cpp \
        storerestartfilenodeonregionface.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    boxregion.h \
    dfn2hybrid.h \
    edmff.h \
    face.h \
    fixhybriddefinition.h \
    inputboundaryregion.h \
    mergefile.h \
    modifydefinitionfile.h \
    modifyfile.h \
    node.h \
    searchnodeonregionface.h \
    setconstanthead.h \
    slabregion.h \
    storedefinitionfilenodeonregionface.h \
    storerestartfilenodeonregionface.h
