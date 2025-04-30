# Déclaration du projet
TEMPLATE = lib
CONFIG += plugin debug_and_release

# Nom de la cible
TARGET = $$qtLibraryTarget(ParametersWidgetCollectionPlugin)

# Qt modules nécessaires
QT += widgets designer

# Déclaration des fichiers
HEADERS += \
    ParametersWidgetCollection_global.h \
    ParameterBase.h \
    ListParameterBase.h \
    BoolParameter.h \
    BoolParameterWidget.h \
    NumericalParameter.h \
    NumericalParameterWidget.h \
    StringParameter.h \
    StringParameterWidget.h \
    ListParameter.h \
    ListParameterWidget.h \
    ParameterGroup.h \
    ParametersView.h \
    ParametersWidgetCollection.h \
    BoolParameterWidgetPlugin.h \
    NumericalParameterWidgetPlugin.h \
    StringParameterWidgetPlugin.h \
    ListParameterWidgetPlugin.h \
    ParametersViewPlugin.h

SOURCES += \
    ParameterBase.cpp \
    BoolParameter.cpp \
    BoolParameterWidget.cpp \
    NumericalParameter.cpp \
    NumericalParameterWidget.cpp \
    StringParameter.cpp \
    StringParameterWidget.cpp \
    ListParameterWidget.cpp \
    ParameterGroup.cpp \
    ParametersView.cpp \
    ParametersWidgetCollection.cpp \
    BoolParameterWidgetPlugin.cpp \
    NumericalParameterWidgetPlugin.cpp \
    StringParameterWidgetPlugin.cpp \
    ListParameterWidgetPlugin.cpp \
    ParametersViewPlugin.cpp

RESOURCES += icons.qrc
#LIBS        += -L. -lListParameterWidget -lParametersView -lBoolParameterWidget -lStringParameterWidget -lNumericalParameterWidget

# Pour l'installation en tant que plugin Qt Designer (facultatif)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

# Exportation des symboles sous Windows (nécessaire avec MSVC)
DEFINES += PARAMETERSWIDGETCOLLECTION_LIBRARY
