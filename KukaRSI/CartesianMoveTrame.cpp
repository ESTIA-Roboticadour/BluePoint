#include "CartesianMoveTrame.h"

CartesianMoveTrame::CartesianMoveTrame(double dx, double dy, double dz, double da, double db, double dc) :
    m_dx(0.),
    m_dy(0.),
    m_dz(0.),
    m_da(0.),
    m_db(0.),
    m_dc(0.)
{
    set(dx, dy, dz, da, db, dc);
}

CartesianMoveTrame::CartesianMoveTrame(double delta[6]) :
    m_dx(0.),
    m_dy(0.),
    m_dz(0.),
    m_da(0.),
    m_db(0.),
    m_dc(0.)
{
    set(delta);
}

void CartesianMoveTrame::set(double dx, double dy, double dz, double da, double db, double dc)
{
    m_dx = dx;
    m_dy = dy;
    m_dz = dz;
    m_da = da;
    m_db = db;
    m_dc = dc;
}

void CartesianMoveTrame::set(double delta[6])
{
    m_dx = delta[0];
    m_dy = delta[1];
    m_dz = delta[2];
    m_da = delta[3];
    m_db = delta[4];
    m_dc = delta[5];
}

bool CartesianMoveTrame::isValid() const
{
    return true;
}

QString CartesianMoveTrame::build() const
{
    return QString("PTP %1 %2 %3 %4 %5 %6")
        .arg(m_dx)
        .arg(m_dy)
        .arg(m_dz)
        .arg(m_da)
        .arg(m_db)
        .arg(m_dc);
}
