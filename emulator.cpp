#include <iostream>
#include <vector>
#include "./src/data-setter.cpp"
#include "./src/path-provider.cpp"

using namespace std;

vector<int> passingPointsX, passingPointsY;
int counter = 0;
string pathToJsonFile = "./paths/basic.json";

int main()
{
	DataSetter setter(pathToJsonFile);

	for(int index = 0; index < setter.getCoordinatesSize(); index++)
	{
		passingPointsX.push_back(setter.get_X_ConsecutiveCoordinate(index));
		passingPointsY.push_back(setter.get_Y_ConsecutiveCoordinate(index));
	}

	Path path(passingPointsX, passingPointsY, setter.getPathIsClosed(), setter.getPathIsCurved());

	return 0;
}
