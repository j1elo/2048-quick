#====================================================================
#          PROJECT CONFIGURATION
#====================================================================

include(../../settings.pri)

# Build configuration
TARGET = $${APP_TARGET}-core # If not defined: same target as the name of this file
TEMPLATE = lib
CONFIG *= qt shared
QT -= gui # Only the core module is used

# Build locations
DESTDIR = $$APP_LIB_PATH
OBJECTS_DIR = $$APP_TMP_PATH/$$TARGET
MOC_DIR = $$OBJECTS_DIR
RCC_DIR = $$OBJECTS_DIR
UI_DIR = $$OBJECTS_DIR
unix: QMAKE_DISTCLEAN *= -r $$OBJECTS_DIR

# Additional configuration
include(../../compiler.pri)
#DEFINES *= CORE_LIBRARY



#====================================================================
#          PROJECT FILES
#====================================================================

# ---- Source files ----

INCLUDEPATH *= .
DEPENDPATH *= .

HEADERS *= \
    GameManager.h \
    BoardItem.h

SOURCES *= \
    GameManager.cpp \
    BoardItem.cpp
