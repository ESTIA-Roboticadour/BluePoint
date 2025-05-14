QT       += widgets designer
TEMPLATE  = lib
TARGET    = $$qtLibraryTarget(XNavigationLayout)
CONFIG   += plugin debug_and_release

# Headers
INCLUDEPATH += $$PWD/../../Libraries/NavigationWidgets/include \
               $$PWD/../../Libraries/TogglePanel/include

# Library (path)
LIBS += -L$$PWD/../../Libraries/NavigationWidgets/lib \
        -L$$PWD/../../Libraries/TogglePanel/lib

# Debug / Release Selection
CONFIG(debug, debug|release) {
    LIBS += -lNavigationWidgetsd -lTogglePaneld
}
else {
    LIBS += -lNavigationWidgets  -lTogglePanel
}

# Designer Installation
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS   += target

# Fichiers sources
HEADERS += NavigationLayout_global.h NavigationLayoutWidget.h NavigationLayoutWidgetPlugin.h
SOURCES += NavigationLayoutWidget.cpp NavigationLayoutWidgetPlugin.cpp

# Exporting symbols to Windows (required with MSVC)
DEFINES += NAVIGATIONLAYOUTWIDGET_LIBRARY
