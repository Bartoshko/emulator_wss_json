#include <iostream>
#include <vector>
#include "./src/data-setter.cpp"
#include "./src/path-provider.cpp"

using namespace std;


int anchors[10][2];
vector<int> passingPointsX, passingPointsY;
int counter = 0;
string pathToJsonFile = "./paths/basic.json";

int main()
{
	DataSetter setter(pathToJsonFile);

	/*
	anchors are hardcoded by loop below for now,
	this needs to be changed after building websocket class
	that will connect with server getting anchors coordinates
	as json file
	*/
	for(int i = 0; i < sizeof(anchors) / sizeof(*anchors); i++)
	{
		anchors[i][0] = i * 10;
		anchors[i][1] = i * 10;
	}

	for(int index = 0; index < setter.getCoordinatesSize(); index++)
	{
		passingPointsX.push_back(setter.get_X_ConsecutiveCoordinate(index));
		passingPointsY.push_back(setter.get_Y_ConsecutiveCoordinate(index));
	}

	Path path(passingPointsX, passingPointsY, setter.getPathIsClosed(), setter.getPathIsCurved(), anchors[10][2]);

	return 0;
}
