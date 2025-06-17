#pragma once
#include "Trame.h"

class CartesianMoveTrame : public Trame
{
	CartesianMoveTrame(double dx, double dy, double dz, double da, double db, double dc);
	CartesianMoveTrame(double delta[6]);

	void set(double dx, double dy, double dz, double da, double db, double dc);
	void set(double delta[6]);

	// Inherited via Trame
	bool isValid() const override;
	QString build() const override;
	Type type() const override 
	{
		return Trame::Type::CartesianMovement;
	}

private:
	double m_dx;
	double m_dy;
	double m_dz;
	double m_da;
	double m_db;
	double m_dc;
};
