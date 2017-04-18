#pragma once
#include "pointDInteret.h"

class sentier
{
private:
	pointDInteret* m_origin;
	pointDInteret* m_destination;
	double m_cout;

public:
	sentier(pointDInteret* origin, pointDInteret* destination);
	~sentier();
	pointDInteret* origin();
	//void setorigin(pointDInteret* origin) { m_origin=origin; };
	pointDInteret* destination();
	//void setdestination(pointDInteret* destination) { m_destination = destination; };
	double cout();

};

