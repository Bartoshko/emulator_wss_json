#include <iostream>
#include <vector>
#include <cmath>
#include <array>

typedef array<int, 2> coordinates;
typedef array<int, 10> distancesOfEachAnchor;

/* class Path */
/* ======================================================= */

class Path
{

public:
	array<distancesOfEachAnchor, 10> ConsecutiveDistanceOfTagToAnchors(array<coordinates, 10> distancesTab);
	Path(vector<int> &rCoordinatesX, vector<int> &rCoordinatesY, bool isClosed, bool isCurved);
	~Path();
private:
	unsigned consecutiveDistanceCounter = 0;
	vector<int> checkPointCoordinatesX, checkPointCoordinatesY, pathAllCoords_X, pathAllCoords_Y;
	array<distancesOfEachAnchor, 10> consecutiveDistanceTable;
	static bool isClosed, isCurved;
	void ClosingPathSetter(bool closed, vector<int> &checkPointsX, vector<int> &checkPointsY);
	void CalculatePath(bool curved, vector<int> &allCoords_X, vector<int> &allCoords_Y);

};
Path::Path(vector<int> &rCoordinatesX, vector<int> &rCoordinatesY, bool isClosed, bool isCurved)
{
	checkPointCoordinatesX = rCoordinatesX;
	checkPointCoordinatesY = rCoordinatesY;
	isClosed = isClosed;
	isCurved = isCurved;
	ClosingPathSetter(isClosed, checkPointCoordinatesX, checkPointCoordinatesY);
	CalculatePath(isCurved, pathAllCoords_X, pathAllCoords_Y);
}
Path::~Path()
{}
array<distancesOfEachAnchor, 10> Path::ConsecutiveDistanceOfTagToAnchors(array<coordinates, 10> distancesTab)
{
	for(unsigned c = 0; c < 10; c++)
	{
		for(unsigned i = 0; i < 10; i++)
		{
			if(distancesTab[i][0] != -1 && distancesTab[i][1] != -1)
			{
				consecutiveDistanceTable[c][i] = lround(sqrt(pow(distancesTab[i][0] - pathAllCoords_X[consecutiveDistanceCounter], 2) + pow(distancesTab[i][1] - pathAllCoords_Y[consecutiveDistanceCounter], 2)));
			}
			else
			{
				consecutiveDistanceTable[c][i] = -1;
			}
		}
		if(consecutiveDistanceCounter == pathAllCoords_X.size())
		{
			consecutiveDistanceCounter = 0;
		}
		else
		{
			consecutiveDistanceCounter++;
		}
	}
	return consecutiveDistanceTable;
}

void Path::ClosingPathSetter(bool closed, vector<int> &checkPointsX, vector<int> &checkPointsY)
{
	if(closed)
	{
		checkPointsX.push_back(checkPointsX[0]);
		checkPointsY.push_back(checkPointsY[0]);
	}
	else
	{
		int index = checkPointsX.size();
		while(index > 0)
		{
			index--;
			checkPointsX.push_back(checkPointsX[index]);
			checkPointsY.push_back(checkPointsY[index]);
		}
	}
}
void Path::CalculatePath(bool curved, vector<int> &allCoords_X, vector<int> &allCoords_Y)
{
	int vector_X, vector_Y, inertia_X, inertia_Y, step;
	unsigned i;
	double sectorVector, stepVector_X, stepVector_Y, increment_X, increment_Y, inertiaStep_X, inertiaStep_Y, inertiaChange_X, inertiaChange_Y;

	if(curved) // TODO: analize with valgrind for memory leaks, implement should be chcked and for curved paths
	{
		for(i = 0; i < checkPointCoordinatesX.size() -1; i++)
		{
			vector_X = checkPointCoordinatesX[i+1] - checkPointCoordinatesX[i];
			vector_Y = checkPointCoordinatesY[i+1] - checkPointCoordinatesY[i];
			if(i == 0){
				inertia_X = 0;
				inertia_Y = 0;
			}
			else
			{
				inertia_X = checkPointCoordinatesX[i] - checkPointCoordinatesX[i-1];
				inertia_Y = checkPointCoordinatesY[i] - checkPointCoordinatesY[i-1];
			}
			sectorVector = sqrt(pow((vector_X + inertia_X), 2) + pow((vector_Y + inertia_Y), 2));
			stepVector_X = vector_X / sectorVector;
			stepVector_Y = vector_Y / sectorVector;
			inertiaStep_X = inertia_X / sectorVector;
			inertiaStep_Y = inertia_Y / sectorVector;
			inertiaChange_X = inertiaStep_X;
			inertiaChange_Y = inertiaStep_Y;
			step = 0;
			while(step < sectorVector - 1)
				{
					increment_X += (stepVector_X + inertiaStep_X);
					increment_Y += (stepVector_Y + inertiaStep_Y);
					inertiaChange_X -= inertiaStep_X / (sectorVector * 2);
					inertiaChange_Y -= inertiaStep_Y / (sectorVector * 2);
					allCoords_X.push_back(lround(checkPointCoordinatesX[i] + increment_X));
					allCoords_Y.push_back(lround(checkPointCoordinatesY[i] + increment_Y));
					step++;
				}
		}
	}
	else
	{
		for(i = 0; i < checkPointCoordinatesX.size() - 1; i++)
		{
			vector_X = checkPointCoordinatesX[i+1] - checkPointCoordinatesX[i];
			vector_Y = checkPointCoordinatesY[i+1] - checkPointCoordinatesY[i];
			sectorVector = sqrt(pow(vector_X, 2) + pow(vector_Y, 2));
			stepVector_X = vector_X / sectorVector;
			stepVector_Y = vector_Y / sectorVector;
			increment_X = 0;
			increment_Y = 0;
			step = 0;
			while(step < sectorVector - 1)
			{
				increment_X += stepVector_X;
				increment_Y += stepVector_Y;
				allCoords_X.push_back(lround(checkPointCoordinatesX[i] + increment_X));
				allCoords_Y.push_back(lround(checkPointCoordinatesY[i] + increment_Y));
				step++;
			}
		}
	}
	cout << "Path has " << pathAllCoords_Y.size() << " points." << endl;
}

/* ======================================================= */