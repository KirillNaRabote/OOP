#include <iostream>
#include "Car.h"
#include "CarControl.h"

using namespace std;
//проверять нечисловые значения, добавить в тесты
int main()
{
	Car car;
	CarControl carControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!carControl.HandleCommand())
		{//сделать так чтобы не выводил когда не нужно
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}