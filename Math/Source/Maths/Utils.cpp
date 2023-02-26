#include "Maths/Utils.h"

const double Maths::radiansToDegrees(const double pRad)
{
	return pRad * (HALF_CIRCLE / PI);
}

const double Maths::degreesToRadians(const double pDeg)
{
	return pDeg * (PI / HALF_CIRCLE);
}
