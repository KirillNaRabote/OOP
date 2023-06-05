#pragma once
#include "stdafx.h"

class CBody
{
public:
	CBody(const std::string& type, double density);

	virtual double GetDensity() const;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const;
	std::string ToString() const;

	virtual ~CBody() = default;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;

	double m_density;
	std::string m_type;
};