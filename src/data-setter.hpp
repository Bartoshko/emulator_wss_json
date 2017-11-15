#include "../lib/json.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace std;

/* class DataSetter */
/* ======================================================= */

class DataSetter
{
public:
	DataSetter(string pathToJson);
	~DataSetter();
	int GetCoordinatesSize(void);
	int Get_X_ConsecutiveCoordinate(int index);
	int Get_Y_ConsecutiveCoordinate(int index);
	int GetTagId(void);
	int GetMovingSpeed(void);
	int GetLossValue(void);
	bool GetPathIsCurved(void);
	bool GetPathIsClosed(void);
	void CheckJsonCompatibility(bool &compatibility);

private:
	json jsonPathObject;
	string jsonFilePath;
	int coordinatesSize;
	int numberOf_X_coordinates = 0;
	int numberOf_Y_coordinates = 0;
};

DataSetter::DataSetter(string pathToJson)
{
	jsonFilePath = pathToJson;
	fstream fileRead(jsonFilePath);
	fileRead >> jsonPathObject;
}
DataSetter::~DataSetter(){}

void DataSetter::CheckJsonCompatibility(bool &compatibility)
{
	compatibility = false;
	if(jsonPathObject.size() > 0 &&
		jsonPathObject["path"].size() > 0 &&
		jsonPathObject["path"]["parameters"].size() > 0 &&
		jsonPathObject["path"]["parameters"]["closed"].size() > 0 &&
		jsonPathObject["path"]["parameters"]["curved"].size() > 0 &&
		jsonPathObject["path"]["parameters"]["loss"].size() > 0 &&
		jsonPathObject["path"]["parameters"]["speed"].size() > 0 &&
		jsonPathObject["path"]["coordinates"].size() > 0)
	{
		compatibility = true;
	}
}

bool DataSetter::GetPathIsClosed()
{
	return jsonPathObject["path"]["parameters"]["closed"];
}
bool DataSetter::GetPathIsCurved()
{
	return jsonPathObject["path"]["parameters"]["curved"];
}
int DataSetter::GetLossValue()
{
	return jsonPathObject["path"]["parameters"]["loss"];
}
int DataSetter::GetMovingSpeed()
{
	return jsonPathObject["path"]["parameters"]["speed"];
}
int DataSetter::GetTagId()
{
	return jsonPathObject["tag_short_id"];
}
int DataSetter::Get_Y_ConsecutiveCoordinate(int index)
{
	return jsonPathObject["path"]["coordinates"][index]["y"];
}
int DataSetter::Get_X_ConsecutiveCoordinate(int index)
{
	return jsonPathObject["path"]["coordinates"][index]["x"];
}
int DataSetter::GetCoordinatesSize()
{
	return jsonPathObject["path"]["coordinates"].size();
}

/* ======================================================= */

/* class package */
/* ======================================================= */

typedef array<int, 10> distancesOfEachAnchor;

class Package
{
	public:
		Package(array<unsigned , 10> anchorsShortIds, unsigned TagShortId, array<distancesOfEachAnchor, 10> distances);
		~Package();
		string StringifyJsonPackageObject(void);
	private:
		json jsonPackageObject;
};
Package::Package(array<unsigned , 10> anchorsShortIds, unsigned TagShortId, array<distancesOfEachAnchor, 10> distances)
{
	jsonPackageObject["info"] = {0};
	jsonPackageObject["measures"] = {};

	unsigned n;
	unsigned o;

	for(n = 0; n < distances.size(); n++)
	{
		for(o = 0; o < distances[n].size(); o++)
		{
			if(distances[n][o] != -1)
			{
				jsonPackageObject["measures"].push_back({{"id_0", anchorsShortIds[o]}, {"id_1", TagShortId}, {"distance", distances[n][o]}});
			}
		}
	}
}
Package::~Package()
{}
string Package::StringifyJsonPackageObject(void)
{
	return jsonPackageObject.dump();
}

/* ======================================================= */