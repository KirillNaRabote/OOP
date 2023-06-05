#pragma once
#include "CBody.h"

class CCylinder : public CBody
{
public:
	CCylinder(double density, double baseRadius, double height);

	double GetBaseRadius() const;
	double GetHeight() const;

	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;

	double m_baseRadius;
	double m_height;
};