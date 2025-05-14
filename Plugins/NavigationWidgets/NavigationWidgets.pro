CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(NavigationWidgets)
TEMPLATE    = lib

HEADERS     = NavigationBranchWidgetPlugin.h NavigationBreadcrumbWidgetPlugin.h NavigationWidgetsCollectionPlugin.h \
    NavigationBranchWidget.h \
    NavigationBreadcrumbWidget.h \
    NavigationNode.h \
    NavigationTree.h \
    NavigationTreeParser.h \
    NavigationWidgets_global.h
SOURCES     = NavigationBranchWidgetPlugin.cpp NavigationBreadcrumbWidgetPlugin.cpp NavigationWidgetsCollectionPlugin.cpp \
    NavigationBranchWidget.cpp \
    NavigationBreadcrumbWidget.cpp \
    NavigationNode.cpp \
    NavigationTree.cpp \
    NavigationTreeParser.cpp

#RESOURCES   =
#LIBS        += -L. -lNavigationBreadcrumbWidget -lNavigationBranchWidget

QT += widgets designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

# Exporting symbols to Windows (required with MSVC)
DEFINES += NAVIGATIONWIDGETS_LIBRARY
