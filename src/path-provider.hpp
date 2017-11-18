#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <bits/stdc++.h>

typedef array<int, 2> coordinates;
typedef array<int, 10> distancesOfEachAnchor;
struct Coords
{
    int x, y;
};

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
	double Interpolate(Coords sectionPoints[3], int xi, int n);
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
double Path::Interpolate(Coords sectionPoints[3], int xi, int n)
{
    double result = 0;

    for (unsigned i_n = 0; i_n < n; i_n++)
    {
        double term = sectionPoints[i_n].y;

        for (unsigned j_n = 0 ; j_n < n; j_n++)
        {
            if (j_n != i_n)
                term = term*(xi - sectionPoints[j_n].x) / double(sectionPoints[i_n].x - sectionPoints[j_n].x);
        }
        result += term;
    }
    return result;
}
void Path::CalculatePath(bool curved, vector<int> &allCoords_X, vector<int> &allCoords_Y)
{
	double sectorVector, stepVector_X, stepVector_Y, increment_X, increment_Y;
	int vector_X, vector_Y;
	unsigned i, step;

	if(curved)
	{
		/*
		* This implementation was taken as a challange and is not working properly
		* at the moment. Path coords are properly interpolated, based on simplification:
		* 1. path is interpolated from 3 points only, i - 1, i, and i + 1.
		* 2. i coords are beginning of the section that is calculated.
		* 3. i is as well end of section befor section that is calculated in given iteration
		* 4. i - 1 is beginning of section before.
		* 5. i + 1 is an end of section that is calculeted in given iteration i.
		* Distances betweeen points are not equal, for each path section it's path length should
		* be calculated and than sectorVector for x and y should be calculated for each sector.
		* In simplified approuch for 3 pointsthat are taken to calculate interpolation
		* path length maybe very big value,
		* probobly even with more crossing points taken to account this will be hard to calculate,
		* so use curved path setter with care.
		* I am using lagrange polynomial interpolation.
		* I will rethink this implementation in the future.
		*/
		for(i = 0; i < checkPointCoordinatesX.size() - 1; i++)
		{
			vector_X = checkPointCoordinatesX[i+1] - checkPointCoordinatesX[i];
			vector_Y = checkPointCoordinatesY[i+1] - checkPointCoordinatesY[i];
			sectorVector = sqrt(pow(vector_X, 2) + pow(vector_Y, 2));
			stepVector_X = vector_X / sectorVector;
			stepVector_Y = vector_Y / sectorVector;
			increment_X = 0;
			increment_Y = 0;
			/*
			* It is assumed that path between first two points will be a line
			*/
			if(i < 1)
			{
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
			else
			{
				Coords aPoints[3] = {{x: checkPointCoordinatesX[i - 1], y: checkPointCoordinatesY[i - 1]}, {x: checkPointCoordinatesX[i], y: checkPointCoordinatesY[i]}, {x: checkPointCoordinatesX[i + 1], y: checkPointCoordinatesY[i + 1]}};

				double appendable_X, appendable_Y;

				stepVector_X = vector_X / sectorVector;
				appendable_X = checkPointCoordinatesX[i];
				step = 0;
				while(step < sectorVector - 1)
				{
					appendable_Y = Interpolate(aPoints, appendable_X, 3);
					allCoords_X.push_back(lround(appendable_X));
					allCoords_Y.push_back(lround(appendable_Y));
					appendable_X += stepVector_X;
					step++;
				}
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