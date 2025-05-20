#ifndef IPARAMETRABLE_H
#define IPARAMETRABLE_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>

class PARAMETERS_WIDGETS_API IParametrable
{
public:
    virtual ~IParametrable() = default;	
    virtual void addParameter(ParameterBase* parameter) = 0;
    virtual ParameterBase* getParameter(const QString& name) const = 0;
    virtual QList<ParameterBase*> getParameters() const = 0;
};

// --------------------------------------------------------------------
// Enregistrez ici **votre** IID (reverse-DNS + /version)
#define IParametrable_iid "com.compositadour.bluepoint.IParametrable/1.0"

// Rend l'interface reconnue par qobject_cast & le système de plugins
Q_DECLARE_INTERFACE(IParametrable, IParametrable_iid)

#endif // IPARAMETRABLE_H
