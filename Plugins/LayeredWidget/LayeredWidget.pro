CONFIG      += plugin debug_and_release
TEMPLATE    = lib
TARGET      = $$qtLibraryTarget(LayeredWidget)

# ----- sources -----
HEADERS += LayeredWidget_global.h \
           LayeredWidget.h \
           LayeredWidgetPlugin.h \


SOURCES += LayeredWidget.cpp \
           LayeredWidgetPlugin.cpp

QT += widgets designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

# pour l’export sous Windows
DEFINES += LAYEREDWIDGET_LIBRARY
