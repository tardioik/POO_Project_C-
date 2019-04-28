QT += widgets
CONFIG   -= x86_64
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    autocell.cpp \
    automate2.cpp \
    FenPrincipale.cpp

HEADERS += \
    autocell.h \
    etat2.h \
    simulateur2.h \
    automate2.h \
    automatemanager2.h \
    FenPrincipale.h

FORMS += \
    menu.ui
