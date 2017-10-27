#include <iostream>
// #include <array>
#include "./src/data-setter.cpp"

using namespace std;

int coordinate;
string dir = "x";

int main()
{
	DataSetter setter("./paths/basic.json");
	setter.printOutPath();
	setter.setJsonObj();
	cout << setter.getJsonObjectAsString() << endl;
	cout << "Coordinate " << coordinate << endl;
	return 0;
}