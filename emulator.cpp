#include <iostream>
#include <vector>
#include <unistd.h>
#include "./src/data-setter.hpp"
#include "./src/path-provider.hpp"

using namespace std;

/*
	anchors are hardcoded this needs to be changed
	after building websocket class that will connect with server
	and get anchors coordinates as json file,
	and allocate values in to anchors array,
	if there will be less anchors then anchors array size,
	than it needs to allocate {-1, -1} for each not existing anchor.
	*/
int anchors[10][2] = {{10, 20}, {100, 200}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
vector<int> passingPointsX, passingPointsY;
int counter = 0;
string pathToJsonFile = "./paths/basic.json";
array<int, 10> printableTable = {0};

int main()
{
	DataSetter setter(pathToJsonFile);

	for(int index = 0; index < setter.getCoordinatesSize(); index++)
	{
		passingPointsX.push_back(setter.get_X_ConsecutiveCoordinate(index));
		passingPointsY.push_back(setter.get_Y_ConsecutiveCoordinate(index));
	}

	Path path(passingPointsX, passingPointsY, setter.getPathIsClosed(), setter.getPathIsCurved(), anchors[0][0]);

	for(int a = 0;a < 100000; a++)
	{
		sleep(1);
		printableTable = path.getConsecutiveDistance();
		for (int z = 0; z < printableTable.size(); z++)
		{
			cout << "tag " << z << printableTable[z] << endl;
		}
	}

	return 0;
}
