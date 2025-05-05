CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(FrameViewer)
TEMPLATE    = lib

HEADERS     = FrameViewer.h FrameViewerPlugin.h FrameViewer_global.h
SOURCES     = FrameViewer.cpp FrameViewerPlugin.cpp

RESOURCES   = icons.qrc
#LIBS        += -L. -lFrameViewer

QT += designer widgets


target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

# Exporting symbols to Windows (required with MSVC)
DEFINES += FRAMEVIEWER_LIBRARY
