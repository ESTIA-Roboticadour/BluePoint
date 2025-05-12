CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(TogglePanel)
TEMPLATE    = lib

HEADERS     = TogglePanel.h TogglePanelPlugin.h TogglePanel_global.h
SOURCES     = TogglePanel.cpp TogglePanelPlugin.cpp
#RESOURCES   =
#LIBS        += -L. -lTogglePanel

QT += widgets designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

# Exporting symbols to Windows (required with MSVC)
DEFINES += TOGGLEPANEL_LIBRARY
