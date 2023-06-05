#include "CCone.h"

CCone::CCone(double density, double baseRadius, double height)
	: CBody("Cone", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
}

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}
double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return 1.0 / 3.0 * M_PI * pow(GetBaseRadius(), 2) * GetHeight();
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase radius = " << GetBaseRadius() << std::endl
		<< "\theight = " << GetHeight() << std::endl;
}