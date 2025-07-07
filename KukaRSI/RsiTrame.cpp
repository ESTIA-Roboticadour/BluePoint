#include "RsiTrame.h"
#include <cstring> // memcpy
#include <QDebug>

RsiTrame::RsiTrame() :
	m_pos(),
	m_ipoc(),
	m_isCartesian(true),
	m_digout(0)
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
	m_digout = 0;
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

ushort RsiTrame::getOutputs()
{
	return m_digout;
}

void RsiTrame::setOutputs(bool outputs[16])
{
	encodeBoolArrayToShort(outputs, m_digout);
}

void RsiTrame::encodeBoolArrayToShort(bool io[16], ushort& nIO)
{
	nIO = 0;
	for (int i = 0; i < 16; i++)
	{
		if (io[i])
			nIO += pow(2, i);
	}
}

bool RsiTrame::isValid() const
{
	return true;
}

QString RsiTrame::build() const
{
	return
		"<Sen Type=\"ImFree\">\r\n"
		"<EStr></EStr>\r\n"
		"<MoveType>" + QString(m_isCartesian ? "1" : "0") + "</MoveType>\r\n"		// 1 : CARTESIAN (POSCORR) | 0 : ARTICULAR (AXISCORR)
		"<RobotBase>" + QString(m_isInRobotBase ? "1" : "0") + "</RobotBase>\r\n"	// 1 : BASE | 0 : TOOL
		"<DeltaPos"
		" X=\"" + QString::number(m_pos[0], 'g', 6) + "\""
		" Y=\"" + QString::number(m_pos[1], 'g', 6) + "\""
		" Z=\"" + QString::number(m_pos[2], 'g', 6) + "\""
		" A=\"" + QString::number(m_pos[3], 'g', 6) + "\""
		" B=\"" + QString::number(m_pos[4], 'g', 6) + "\""
		" C=\"" + QString::number(m_pos[5], 'g', 6) + "\""
		"/>\r\n"
		"<Digout>" + QString::number(m_digout) + "</Digout>\r\n"
		"<IPOC>" + m_ipoc + "</IPOC>\r\n"
		"</Sen>";

}
