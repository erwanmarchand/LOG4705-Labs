#include "sentier.h"


sentier::sentier(pointDInteret* origin, pointDInteret* destination){ m_origin = origin; m_destination = destination; m_cout = origin->getCouts()[destination]; };
pointDInteret* sentier::origin() { return m_origin; };
//void setorigin(pointDInteret* origin) { m_origin=origin; };
pointDInteret* sentier::destination() { return m_destination; };
//void setdestination(pointDInteret* destination) { m_destination = destination; };
double sentier::cout(){ return m_cout; };
