#====================================================================
#          PROJECT CONFIGURATION
#====================================================================

message("Processing $${_FILE_}")
CONFIG(debug, debug|release): BUILD_TARGET = debug
CONFIG(release, debug|release): BUILD_TARGET = release
message("Building [$${BUILD_TARGET}] Makefile for [$${TARGET}] on [$${QMAKE_HOST.os}] [$${QMAKE_HOST.arch}]")

# Build configuration
#TARGET = target # If not defined: same as the file name
TEMPLATE = app
CONFIG *= qt thread
QT *= testlib # core gui
#greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets

# Build locations
DESTDIR = .
MOC_DIR = tmp
OBJECTS_DIR = $$MOC_DIR
RCC_DIR = $$MOC_DIR
UI_DIR = $$MOC_DIR
unix: QMAKE_DISTCLEAN *= -r $$MOC_DIR

# Additional configuration
#DEFINES *= MY_CODE=1
#DEFINES *= MY_TEXT=\\\"This is my text\\\"
include(compiler.pri) # Compiler configuration



#====================================================================
#          PROJECT FILES
#====================================================================

# ---- Project dependencies ----

#LIBS *= -Lsome/path -lsomelib


# ---- Project source files ----

INCLUDEPATH *= .

DEPENDPATH *= .

HEADERS *= \
    BoardTest.h \
    Board.h

SOURCES *= \
    BoardTest.cpp \
    Board.cpp

#FORMS *= MyForm.ui
#RESOURCES *= resources.qrc
#OTHER_FILES *= readme.txt
