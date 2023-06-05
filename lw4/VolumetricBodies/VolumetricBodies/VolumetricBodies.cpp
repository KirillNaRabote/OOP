#include <iostream>
#include <vector>
#include "CBody.h"
#include "CCompound.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "BodyController.h"

using namespace std;



int main()
{
	vector<shared_ptr<CBody>> shapes;
	BodyController BController(shapes, cin, cout);
	BController.InitBodies();
	BController.PrintBodyWithMaxMass();
	BController.PrintBodyWithLeastWeightInWater();
}