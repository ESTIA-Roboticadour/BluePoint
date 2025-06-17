#pragma once
#include "Trame.h"
#include <QString>
#include <map>
#include <memory>

class TrameStack
{
public:
    explicit TrameStack();

    void addTrame(std::unique_ptr<Trame> trame);

    QString buildTrame();

private:
    std::map<Trame::Type, std::unique_ptr<Trame>> m_trames;
};
