#pragma once
#include "CBody.h"
#include <vector>

class CCompound : public CBody
{
public:
	CCompound();

	double GetVolume() const override;
	double GetMass() const;
	double GetDensity() const;
	void AddChildBody(const std::shared_ptr<CBody>& child);

private:
	void AppendProperties(std::ostream& strm) const override;

	std::vector<std::shared_ptr<CBody>> m_children;
};