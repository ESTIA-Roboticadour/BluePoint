#include "Camera.h"
#include <exception>

Camera::Camera(QObject* parent) :
	ImageProvider(parent)
{
}

void Camera::addTransformer(ImageTransformer* t)
{
    if (!t || m_transformers.contains(t))
        return;
    m_transformers.append(t);
}

void Camera::clearTransformers(bool deleteTransformers)
{
    if (deleteTransformers)
        qDeleteAll(m_transformers);
    m_transformers.clear();
}

QList<ImageTransformer*> Camera::transformers() const
{
    return m_transformers;
}

QImage Camera::applyPipeline(const QImage& raw)
{
    QImage img = raw;
    int i = -1;
    for (auto* t : m_transformers)
    {
        i++;
        if (!t)
            continue;

        try {
            img = t->transform(img);
        }
        catch (const std::exception& ex) {
            qDebug() << "[Camera] Transform exception:" << ex.what();
            emit transformError(t, i, QString::fromLatin1(ex.what()));
            return QImage();                 // stop pipe
        }
        catch (...) {
            qDebug() << "[Camera] Unknown transform exception";
            emit transformError(t, i, QStringLiteral("Unknown error"));
            return QImage();
        }

        if (img.isNull()) {                  // transformer a "échoué" silencieusement
            emit transformError(t, i, QStringLiteral("Transformer returned null image"));
            return QImage();
        }
    }
    return img;
}
