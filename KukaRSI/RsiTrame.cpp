#include "RsiTrame.h"
#include <cstring> // memcpy

RsiTrame::RsiTrame() :
	m_pos(),
	m_ipoc(),
	m_isCartesian(true)
{
	reset();
}

void RsiTrame::reset()
{
	m_isCartesian = true;
	m_ipoc.clear();
	m_pos[0] = 0.;
	m_pos[1] = 0.;
	m_pos[2] = 0.;
	m_pos[3] = 0.;
	m_pos[4] = 0.;
	m_pos[5] = 0.;
}

void RsiTrame::setPose(bool isCartesian, double pos[6], bool isInRobotBase)
{
	m_isCartesian = isCartesian;
	m_isInRobotBase = isInRobotBase;
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
	QString trame = 
		"<Sen Type=\"ImFree\">\r\n"
		"<EStr></EStr>\r\n";
	trame += m_isCartesian ?
		"<Corr"
		" X=\"" + QString::number(m_pos[0], 'g', 6) + "\""
		" Y=\"" + QString::number(m_pos[1], 'g', 6) + "\""
		" Z=\"" + QString::number(m_pos[2], 'g', 6) + "\""
		" A=\"" + QString::number(m_pos[3], 'g', 6) + "\""
		" B=\"" + QString::number(m_pos[4], 'g', 6) + "\""
		" C=\"" + QString::number(m_pos[5], 'g', 6) + "\""
		" J1=\"0.0\""
		" J2=\"0.0\""
		" J3=\"0.0\""
		" J4=\"0.0\""
		" J5=\"0.0\""
		" J6=\"0.0\""
		" />\r\n"
		:
	"<Corr"
		" X=\"0.0\""
		" Y=\"0.0\""
		" Z=\"0.0\""
		" A=\"0.0\""
		" B=\"0.0\""
		" C=\"0.0\""
		" J1=\"" + QString::number(m_pos[0], 'g', 6) + "\""
		" J2=\"" + QString::number(m_pos[1], 'g', 6) + "\""
		" J3=\"" + QString::number(m_pos[2], 'g', 6) + "\""
		" J4=\"" + QString::number(m_pos[3], 'g', 6) + "\""
		" J5=\"" + QString::number(m_pos[4], 'g', 6) + "\""
		" J6=\"" + QString::number(m_pos[5], 'g', 6) + "\""
		" />\r\n";

	trame +=
		"<IPOC>" + m_ipoc + "</IPOC>\r\n"
		"</Sen>";

	return trame;
}
