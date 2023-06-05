#include "CCompound.h"

CCompound::CCompound()
	: CBody("Compound", this->GetDensity())
{
}

double CCompound::GetVolume() const
{
	double volume = 0.0;

	for (const auto& bodyPtr : m_children)
	{
		volume += bodyPtr->GetVolume();
	}

	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0.0;

	for (const auto& bodyPtr : m_children)
	{
		mass += bodyPtr->GetMass();
	}

	return mass;
}

double CCompound::GetDensity() const
{

	return CCompound::GetMass() / CCompound::GetVolume();
}

void CCompound::AddChildBody(const std::shared_ptr<CBody>& child)
{
	m_children.push_back(child);
}

void CCompound::AppendProperties(std::ostream& strm) const
{
	strm << "Consists of:" << std::endl;

	for (const auto& bodyPtr : m_children)
	{
		strm << "\t" << bodyPtr->ToString() << std::endl;
	}
}