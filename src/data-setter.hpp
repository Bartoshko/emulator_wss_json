#include "../lib/json.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace std;

/* CLASS DATASETTER */
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

/* CLASS PACKAGE */
/* ======================================================= */

class Package
{
	public:
		Package(array<int , 10> anchorsShortIds, int TagShortId, array<int, 10> distances);
		~Package();
		string StringifyJsonPackageObject(void);
	private:
		json jsonPackageObject;
};
Package::Package(array<int , 10> anchorsShortIds, int TagShortId, array<int, 10> distances){
	jsonPackageObject["info"] ={0};
	jsonPackageObject["measures"] = {};
	for(int index = 0; index < distances.size(); index++)
	{
		if(distances[index] != -1)
		{
			jsonPackageObject["measures"].push_back({{"id_0", anchorsShortIds[index]}, {"id_1", TagShortId}, {"distance", distances[index]}});
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