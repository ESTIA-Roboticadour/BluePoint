#include "RsiTrame.h"
#include <cstring> // memcpy

RsiTrame::RsiTrame() :
    m_pos(),
    m_ipoc()
{
    reset();
}

void RsiTrame::reset()
{
    m_ipoc.clear();
    m_pos[0] = 0.;
    m_pos[1] = 0.;
    m_pos[2] = 0.;
    m_pos[3] = 0.;
    m_pos[4] = 0.;
    m_pos[5] = 0.;
}

void RsiTrame::setPose(double pos[6])
{
    std::memcpy(m_pos, pos, 6 * sizeof(double));
}

void RsiTrame::setIPOC(const QString& ipoc)
{
    m_ipoc = ipoc;
}

bool RsiTrame::isValid() const
{
    return true;
}

QString RsiTrame::build() const
{
    return (
        "<Sen Type=\"ImFree\">\r\n"
        "<EStr></EStr>\r\n"
        "<RKorr"
        " X=\"" + QString::number(m_pos[0], 'g', 6) + "\""
        " Y=\"" + QString::number(m_pos[1], 'g', 6) + "\""
        " Z=\"" + QString::number(m_pos[2], 'g', 6) + "\""
        " A=\"" + QString::number(m_pos[3], 'g', 6) + "\""
        " B=\"" + QString::number(m_pos[4], 'g', 6) + "\""
        " C=\"" + QString::number(m_pos[5], 'g', 6) + "\""
        "/>\r\n"

        //"<FREE>0</FREE>\r\n"
        "<DiO>125</DiO>\r\n"
        "<IPOC>" + m_ipoc + "</IPOC>\r\n"
        "</Sen>"
        );
}
