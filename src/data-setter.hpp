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
		fileRead >> jsonPathObject;
	}
	~DataSetter(){};

	int getCoordinatesSize()
	{
		return jsonPathObject["path"]["coordinates"].size();
	}

	int get_X_ConsecutiveCoordinate(int index)
	{
		return jsonPathObject["path"]["coordinates"][index]["x"];
	}

	int get_Y_ConsecutiveCoordinate(int index)
	{
		return jsonPathObject["path"]["coordinates"][index]["y"];
	}

	int getTagId()
	{
		return jsonPathObject["tag_short_id"];
	}

	int getMovingSpeed()
	{
		return jsonPathObject["path"]["parameters"]["speed"];
	}

	int getLossValue()
	{
		return jsonPathObject["path"]["parameters"]["loss"];
	}

	bool getPathIsCurved()
	{
		return jsonPathObject["path"]["parameters"]["curved"];
	}

	bool getPathIsClosed()
	{
		return jsonPathObject["path"]["parameters"]["closed"];
	}


private:
	json jsonPathObject;
	string jsonFilePath;
	int coordinatesSize;
	int numberOf_X_coordinates = 0;
	int numberOf_Y_coordinates = 0;
};

class Package
{
	public:
		Package(array<int , 10> anchorsShortIds, int TagShortId, array<int, 10> distances){
			jsonPackageObject["info"] = {};
			jsonPackageObject["measures"] = {};
			for(int index = 0; index < distances.size(); index++)
			{
				if(distances[index] != -1)
				{
					jsonPackageObject["measures"].push_back({{"id_0", anchorsShortIds[index]}, {"id_1", TagShortId}, {"distance", distances[index]}});
				}
			}
		}
		~Package(){};
		string stringifyJsonPackageObject(void)
		{
			return jsonPackageObject.dump();
		}
	private:
		json jsonPackageObject;
};
