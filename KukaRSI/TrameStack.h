#pragma once
#include "Trame.h"
#include <QString>
#include <map>
#include <memory>

class TrameStack
{
public:
    explicit TrameStack();

    void addTrame(std::shared_ptr<Trame> trame);

    QString buildTrame();

private:
    std::map<Trame::Type, std::shared_ptr<Trame>> m_trames;
};
