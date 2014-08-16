#====================================================================
#          PROJECT CONFIGURATION
#====================================================================

include(../../settings.pri)

# Build configuration
TARGET = $$APP_TARGET # If not defined: same target as the name of this file
TEMPLATE = app
CONFIG *= qt
QT *= qml quick

# Build locations
DESTDIR = $$APP_BIN_PATH
OBJECTS_DIR = $$APP_TMP_PATH/$$TARGET
MOC_DIR = $$OBJECTS_DIR
RCC_DIR = $$OBJECTS_DIR
UI_DIR = $$OBJECTS_DIR
unix: QMAKE_DISTCLEAN *= -r $$OBJECTS_DIR

# Additional configuration
include(../../compiler.pri)

CONFIG(debug, debug|release) {
    CONFIG *= QRC_LOCAL_FILES
    DEFINES *= QRC_LOCAL_FILES
}



#====================================================================
#          PROJECT FILES
#====================================================================

# ---- Project dependencies ----

# Core lib
INCLUDEPATH *= .. ../core
LIBS *= -l$${APP_TARGET}-core


# ---- Source files ----

INCLUDEPATH *= .
DEPENDPATH *= .

HEADERS *= \
    qml/BaseUi.h \
    qml/MainWindowUi.h \
    qml/BoardUi.h

SOURCES *= main.cpp \
    qml/MainWindowUi.cpp \
    qml/BoardUi.cpp

OTHER_FILES += \
    qml/Board.qml \
    qml/Tile.qml \
    qml/MainWindow.qml
