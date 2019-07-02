#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T14:15:21
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProceduralTerrainGenerator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    algos/perlinnoise.cpp \
    main.cpp \
    mainwindow.cpp \
    algos/diamond_square.cpp \
    pages/aboutpage.cpp \
    pages/generationpage.cpp \
    pages/instructionpage.cpp \
    pages/page.cpp \
    pages/terrainpage.cpp \
    pages/welcomepage.cpp \
    view/ptgbutton.cpp \
    view/terraintools.cpp \
    view/terrainview.cpp

HEADERS += \
    algos/biome.h \
    algos/perlinnoise.h \
    algos/terrain_data.h \
    mainwindow.h \
    algos/diamond_square.h \
    pages/aboutpage.h \
    pages/generationpage.h \
    pages/instructionpage.h \
    pages/page.h \
    pages/terrainpage.h \
    pages/welcomepage.h \
    view/ptgbutton.h \
    view/terraintools.h \
    view/terrainview.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    classhierarchydiagram.qmodel

RESOURCES += \
    pictures.qrc
