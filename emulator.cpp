/*

BARTOSHCO EMULATOR C++

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2013-2017 Bartoshco Lenart

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

using namespace std;

/*
	anchors are hardcoded this needs to be changed
	after building websocket class that will connect with server
	and get anchors coordinates as json file,
	and allocate values in to anchors array,
	if there will be less anchors then anchors array size,
	than it needs to allocate {-1, -1} for each not existing anchor.
	*/
int anchorsInitialization[10][2] =  {{10, 20}, {100, 200}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
/*
below allocated values should stay as they are after websocket implementation
*/
array<array<int, 2>, 10> anchors;
vector<int> passingPointsX, passingPointsY;
int counter = 0;
string pathToJsonFile = "./paths/basic.json";
array<int, 10> distances;

int main()
{

	/*
	allocation of anchorsInitialization distances in to anchors array
	this will be changed after websocket implementation
	*/
	for(int anchorsCounter = 0; anchorsCounter < 10; anchorsCounter++)
	{
		anchors[anchorsCounter][0] = anchorsInitialization[anchorsCounter][0];
		anchors[anchorsCounter][1] = anchorsInitialization[anchorsCounter][1];
	}

	DataSetter setter(pathToJsonFile);

	for(int index = 0; index < setter.getCoordinatesSize(); index++)
	{
		passingPointsX.push_back(setter.get_X_ConsecutiveCoordinate(index));
		passingPointsY.push_back(setter.get_Y_ConsecutiveCoordinate(index));
	}

	Path path(passingPointsX, passingPointsY, setter.getPathIsClosed(), setter.getPathIsCurved());

	for(int a = 0; a < 100000; a++)
	{
		sleep(1);
		cout << "Package number: "<< a << endl;
		distances = path.consecutiveDistanceOfTagToAnchors(anchors);
		// for(int consecAnchor = 0; consecAnchor < distances.size(); consecAnchor++)
		// {
		// 	cout << "Distance from anchor " << consecAnchor << " is: " << distances[consecAnchor] << endl;
		// }
		Package package({10099, 10199, 10299, 10399, 10499, 10599, 10699, 10799, 10899, 10999}, 99, distances);
		cout << package.stringifyJsonPackageObject() << endl;
	}


	return 0;
}
