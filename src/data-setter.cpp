#include "../lib/json.hpp"
#include <fstream>
#include <iostream>
// #include <array>

using json = nlohmann::json;
using namespace std;

class DataSetter
{
public:
	DataSetter(string pathToJson)
	{
		jsonFilePath = pathToJson;
	}
	void printOutPath()
	{
		cout << "Path to json file is: " << jsonFilePath << endl;
	}
	void setJsonObj()
	{
		fstream fileRead(jsonFilePath);
		fileRead >> jsonObj;
	}
	string getJsonObjectAsString()
	{
		return jsonObj.dump();
	}
private:
	json jsonObj;
	string jsonFilePath;
};
