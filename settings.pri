# Global settings for the current project.
# This file is based on "qtcreator.pri", found on the Qt Creator source tree.
# Take a look there, if you ned to extend the functionality here.

!isEmpty(SETTINGS_PRI_INCLUDED): error("settings.pri file was already included")
SETTINGS_PRI_INCLUDED = 1

APP_VERSION = 0.1.0

APP_BUILD_TREE = $$clean_path($$PWD)
APP_BIN_PATH = $$APP_BUILD_TREE/bin
macx {
} else {
    APP_TARGET   = 2048-quick
    APP_LIB_PATH = $$APP_BUILD_TREE/lib
    APP_TMP_PATH = $$APP_BUILD_TREE/tmp
}

LIBS *= -L$$APP_LIB_PATH
