#include "../lib/json.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace std;

class DataSetter
{
public:
	DataSetter(string pathToJson)
	{
		jsonFilePath = pathToJson;
		fstream fileRead(jsonFilePath);
		fileRead >> jsonObj;
	}

	int getCoordinatesSize()
	{
		return jsonObj["path"]["coordinates"].size();
	}

	int get_X_ConsecutiveCoordinate(int index)
	{
		return jsonObj["path"]["coordinates"][index]["x"];
	}

	int get_Y_ConsecutiveCoordinate(int index)
	{
		return jsonObj["path"]["coordinates"][index]["y"];
	}

	int getTagId()
	{
		return jsonObj["tag_short_id"];
	}

	int getMovingSpeed()
	{
		return jsonObj["path"]["parameters"]["speed"];
	}

	int getLossValue()
	{
		return jsonObj["path"]["parameters"]["loss"];
	}

	bool getPathIsCurved()
	{
		return jsonObj["path"]["parameters"]["curved"];
	}

	bool getPathIsClosed()
	{
		return jsonObj["path"]["parameters"]["closed"];
	}


private:
	json jsonObj;
	string jsonFilePath;
	int coordinatesSize;
	int numberOf_X_coordinates = 0;
	int numberOf_Y_coordinates = 0;
};
