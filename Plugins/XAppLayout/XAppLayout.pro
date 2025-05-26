QT       += widgets designer

TEMPLATE  = lib
TARGET    = $$qtLibraryTarget(XAppLayout)
CONFIG   += plugin debug_and_release

# ---- dépendances internes BluePoint (toutes déjà générées) ----
INCLUDEPATH += $$PWD/../../Libraries/NavigationWidgets/include \
               $$PWD/../../Libraries/TogglePanel/include \
               $$PWD/../../Libraries/LogTool/include \
               $$PWD/../../Libraries/LayeredWidget/include \
               $$PWD/../../Libraries/LogoWidget/include

LIBS += -L$$PWD/../../Libraries/NavigationWidgets/lib \
        -L$$PWD/../../Libraries/TogglePanel/lib \
        -L$$PWD/../../Libraries/LogTool/lib \
        -L$$PWD/../../Libraries/LayeredWidget/lib \
        -L$$PWD/../../Libraries/LogoWidget/lib

# Sélection Debug / Release
CONFIG(debug, debug|release) {
    LIBS += -lNavigationWidgetsd -lTogglePaneld \
            -lLogToold -lLayeredWidgetd -lLogoWidgetd
} else {
    LIBS += -lNavigationWidgets  -lTogglePanel \
            -lLogTool  -lLayeredWidget  -lLogoWidget
}

# ---- Fichiers sources du plugin ----
HEADERS += AppLayout_global.h AppLayoutWidget.h AppLayoutWidgetPlugin.h
SOURCES += AppLayoutWidget.cpp AppLayoutWidgetPlugin.cpp

# Installation dans le dossier des plugins Designer
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS   += target

# Export sous Windows
DEFINES += APPLAYOUT_LIBRARY
