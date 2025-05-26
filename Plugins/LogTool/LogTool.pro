QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

CONFIG      += plugin debug_and_release
TEMPLATE    = lib
TARGET      = $$qtLibraryTarget(LogTool)

# --- fichiers du projet ---
HEADERS     += LogTool_global.h \
               LogDispatcher.h \
               LogModel.h \
               LogWidget.h \
               LogWidgetPlugin.h \

SOURCES     += LogDispatcher.cpp \
               LogModel.cpp \
               LogWidget.cpp \
               LogWidgetPlugin.cpp

QT += widgets designer

# Dossier d'installation du plugin dans l’arbre Qt (Designer le trouvera ici)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

# Export des symboles côté Windows / MSVC
DEFINES += LOGTOOL_LIBRARY
