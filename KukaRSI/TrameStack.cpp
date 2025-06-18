#include "TrameStack.h"
#include <QStringList>

TrameStack::TrameStack() :
    m_trames()
{
}

void TrameStack::addTrame(std::shared_ptr<Trame> trame)
{
	// Remplace toute trame existante du même type
    m_trames[trame->type()] = std::move(trame);  // Transfert de propriété
}

QString TrameStack::buildTrame()
{
    QStringList frame;
    for (const auto& [type, trame] : m_trames)
    {
        frame << trame->build();
    }

    m_trames.clear(); // Toutes les shared_ptr seront automatiquement détruites
    return frame.join(";");
}
