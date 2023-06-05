#pragma once

#include <vector>
#include <functional>
#include <map>
#include "CBody.h"
#include "CCompound.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"

class BodyController
{
public:
	BodyController(std::vector<std::shared_ptr<CBody>>& shapes, std::istream& input, std::ostream& output);

	void InitBodies();
	void PrintBodyWithMaxMass();
	void PrintBodyWithLeastWeightInWater();

	~BodyController() = default;

private:
	std::shared_ptr<CBody> CreateBody();
	std::shared_ptr<CSphere> CreateSphere(std::istream& args);
	std::shared_ptr<CParallelepiped> CreateParallelepiped(std::istream& args);
	std::shared_ptr<CCone> CreateCone(std::istream& args);
	std::shared_ptr<CCylinder> CreateCylinder(std::istream& args);
	std::shared_ptr<CCompound> CreateCompound(std::istream& args);
	void ShowShapesInfo();

	std::vector<std::shared_ptr<CBody>>& m_shapes;
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<std::shared_ptr<CBody>(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
	const int m_DENSITY_OF_WATER = 1000;
	const int m_ACCELERATION_OF_FREE_FALL = 10;
};