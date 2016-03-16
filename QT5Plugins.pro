#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T14:11:46
#
#-------------------------------------------------

QT      += core gui
QT      += network

TARGET = ./launch_organ
TEMPLATE = app


SOURCES += main.cpp\
    src/Com/ClientLoop.cpp \
    src/Com/SpinalCore.cpp \
    src/Database/Database.cpp \
    src/Model/Bool.cpp \
    src/Model/Directory.cpp \
    src/Model/Lst.cpp \
    src/Model/LstWithType.cpp \
    src/Model/Model.cpp \
    src/Model/ModelWithAttr.cpp \
    src/Model/ModelWithAttrAndName.cpp \
    src/Model/Path.cpp \
    src/Model/Ptr.cpp \
    src/Model/Str.cpp \
    src/Model/Val.cpp \
    src/Sys/BinRd.cpp \
    src/MP.cpp \
    src/Updater.cpp \
    Process.cpp \
    config.cpp

HEADERS  += src/Com/ClientLoop.h \
    src/Com/ClientLoop_parser.h \
    src/Com/SpinalCore.h \
    src/Database/Database.h \
    src/Model/Bool.h \
    src/Model/Directory.h \
    src/Model/Lst.h \
    src/Model/LstWithType.h \
    src/Model/Model.h \
    src/Model/ModelWithAttr.h \
    src/Model/ModelWithAttrAndName.h \
    src/Model/Path.h \
    src/Model/Ptr.h \
    src/Model/Str.h \
    src/Model/TypedArray.h \
    src/Model/Val.h \
    src/Sys/BinOut.h \
    src/Sys/BinRd.h \
    src/Sys/S.h \
    src/MP.h \
    src/Updater.h \
    Process.h \
    config.h

OTHER_FILES += \
    README.txt
