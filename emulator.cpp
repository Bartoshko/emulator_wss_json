/*

BARTOSHCO EMULATOR C++

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2017-2022 Bartoshco Lenart

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFT

*/

#include <iostream>
#include <vector>
#include <unistd.h>
#include "./src/data-setter.hpp"
#include "./src/path-provider.hpp"
#include "./src/socket-client.hpp"

using namespace std;

/*
	anchors are hardcoded this needs to be changed
	after building websocket class that will connect with server
	and get anchors coordinates as json file,
	and allocate values in to anchors array,
	if there will be less anchors then anchors array size,
	than it needs to allocate {-1, -1} for each not existing anchor.
	*/
int anchorsInitialization[10][2] = {{10, 20}, {500, 700}, {100, 100}, {400, 400}, {300, 900}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
typedef array<int, 2> coordinates;
bool isJsonCompatible;
array<coordinates, 10> anchors;
vector<int> passingPointsX, passingPointsY;
int counter = 0;
string pathToJsonFile;
typedef array<int, 10> distancesOfEachAnchor;
array<distancesOfEachAnchor, 10> distancesOnePackage; // 10 colllections of 10 anchor - tag dimensions

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please specify path to json file" << endl;
		return 1;
	}
	else
	{
		pathToJsonFile = argv[1];
	}
	/*
	allocation of anchorsInitialization distances in to anchors array
	this will be changed after websocket implementation
	*/
	for(unsigned anchorsCounter = 0; anchorsCounter < 10; anchorsCounter++)
	{
		anchors[anchorsCounter][0] = anchorsInitialization[anchorsCounter][0];
		anchors[anchorsCounter][1] = anchorsInitialization[anchorsCounter][1];
	}

	DataSetter setter(pathToJsonFile);
	setter.CheckJsonCompatibility(isJsonCompatible);
	if(!isJsonCompatible)
	{
		cout << "Your json file has wrong notation or some data is missing." << endl;
		return 2;
	}

	for(unsigned index = 0; index < setter.GetCoordinatesSize(); index++)
	{
		passingPointsX.push_back(setter.Get_X_ConsecutiveCoordinate(index));
		passingPointsY.push_back(setter.Get_Y_ConsecutiveCoordinate(index));
	}

	Path path(passingPointsX, passingPointsY, setter.GetPathIsClosed(), setter.GetPathIsCurved());

	for(unsigned a = 0; a < 100000; a++)
	{
		sleep(1);
		cout << "Package number: "<< a << endl;
		distancesOnePackage = path.ConsecutiveDistanceOfTagToAnchors(anchors);
		Package package({10099, 10199, 10299, 10399, 10499, 10599, 10699, 10799, 10899, 10999}, 99, distancesOnePackage);
		cout << package.StringifyJsonPackageObject() << endl;
	}

	return 0;
}
