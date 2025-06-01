CONFIG      += plugin debug_and_release
TEMPLATE    = lib
QT += widgets designer

# Library / plugin name (without platform‑specific prefix/suffix)
TARGET    = $$qtLibraryTarget(TransparentScrollArea)

# Export symbols when building the library
DEFINES  += TRANSPARENTSCROLLAREA_LIBRARY

# Include paths
INCLUDEPATH += $$PWD

# Headers / Sources
HEADERS  += \
    TransparentScrollArea_global.h \
    TransparentScrollArea.h \
    TransparentScrollAreaPlugin.h

SOURCES  += \
    TransparentScrollArea.cpp \
    TransparentScrollAreaPlugin.cpp

# MOC / RCC handled automatically by qmake

# Install plugin into Qt Designer's plugin directory on 'make install'
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
