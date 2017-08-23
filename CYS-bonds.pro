TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    io.cpp

HEADERS += \
    io.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../gems/gmml/bin/release/ -lgmml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../gems/gmml/bin/debug/ -lgmml
else:unix: LIBS += -L$$PWD/../../gems/gmml/bin/ -lgmml

INCLUDEPATH += $$PWD/../../gems/gmml/bin
DEPENDPATH += $$PWD/../../gems/gmml/bin
