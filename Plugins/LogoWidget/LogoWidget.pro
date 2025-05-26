CONFIG      += plugin debug_and_release
TEMPLATE    = lib
TARGET      = $$qtLibraryTarget(LogoWidget)

HEADERS += LogoWidget_global.h \
           LogoWidget.h \
           LogoWidgetPlugin.h \


SOURCES += LogoWidget.cpp \
           LogoWidgetPlugin.cpp

QT += widgets designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

DEFINES += LOGOWIDGET_LIBRARY
