QT       += core gui
QT += opengl
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += QtGui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

INCLUDEPATH += Bezier/

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Bezier/beziercurve.cpp \
    Curves/compositecurve.cpp \
    Curves/curve.cpp \
    Curves/simplecurve.cpp \
    Point/controlpoint.cpp \
    Point/linepoint.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Bezier/beziercurve.h \
    Bezier/cubicbeziercurve.h \
    Bezier/quadraticbeziercurve.h \
    Curves/compositecurve.h \
    Curves/curve.h \
    Curves/simplecurve.h \
    Point/controlpoint.h \
    Point/linepoint.h \
    Point/point.h \
    Utils/Utils.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += "C:\Program Files\boost\boost_1_75_0" \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


unix|win32: LIBS += -lOpenGL32
