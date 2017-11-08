#include <iostream>
#include <vector>
#include <cmath>
#include <array>

/*
Path class constructs two arrays: pathAllCoords_X and pathAllCoords_Y
that are representing path that is taken by interpolating lines if path is not curved,
or are calculated from calculating polinomial interpolation for smallest logical vector step
between given crossing points in checkPointCoordinatesX and checkPointCoordinatesY.
This path calculates crossing points from velocity of traveling tag between given crossing
points.
*/

class Path
{
public:
	Path(vector<int> &rCoordinatesX, vector<int> &rCoordinatesY, bool isClosed, bool isCurved, int &rAnchors)
	{
		checkPointCoordinatesX = rCoordinatesX;
		checkPointCoordinatesY = rCoordinatesY;
		isClosed = isClosed;
		isCurved = isCurved;
		pAnchors = &rAnchors;
		closingPathSetter(isClosed, checkPointCoordinatesX, checkPointCoordinatesY);
		calculatePath(isCurved, pathAllCoords_X, pathAllCoords_Y);
		calculateDistancesForEachAnchor(pathAllCoords_X, pathAllCoords_Y, pAnchors, distancesAnchor_Tag);
	}
	array<int, 10> getConsecutiveDistance(void)
	{
		if (consecutiveDistanceCounter < distancesAnchor_Tag[0].size())
		{
			for (int c = 0; c < distancesAnchor_Tag.size(); c++)
			{
				consecutiveDistanceTable[c] = distancesAnchor_Tag[c][consecutiveDistanceCounter];
			}
			consecutiveDistanceCounter++;
			return consecutiveDistanceTable;
		}
		else
		{
			consecutiveDistanceCounter = 0;
		}
	}

private:
	int consecutiveDistanceCounter = 0;
	int *pAnchors = 0;
	vector<int> checkPointCoordinatesX, checkPointCoordinatesY, pathAllCoords_X, pathAllCoords_Y;
	array<vector<int>, 10> distancesAnchor_Tag;
	array<int, 10> consecutiveDistanceTable;
	static bool isClosed, isCurved;

	void closingPathSetter(bool closed, vector<int> &checkPointsX, vector<int> &checkPointsY)
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

	void calculatePath(bool curved, vector<int> &allCoords_X, vector<int> &allCoords_Y)
	{
		int vector_X, vector_Y, step;
		double sectorVector, stepVector_X, stepVector_Y, increment_X, increment_Y;

		if(curved)
		{
			for(int i = 0; i < checkPointCoordinatesX.size() -1; i++)
			{
				/*
				polinomial interpolation method will not work when applied straight away,
				becouse curvature is rarely symetric according to X or Y axis
				and coordinates system needs to be rotated, so better approuch is to
				use quantified vector method, what will be coded soon...
				*/
				cout << "Check point curved X: " << checkPointCoordinatesX[i] << endl;
				cout << "Check point curved Y: " << checkPointCoordinatesY[i] << endl;
			}
		}
		else
		{
			for(int i = 0; i < checkPointCoordinatesX.size() - 1; i++)
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
			cout << "Path has " << pathAllCoords_Y.size() << " points." << endl;
		}
	}

	void calculateDistancesForEachAnchor(vector<int> &rAllCoords_X, vector<int> &rAllCoords_Y, int *pAnchors, array<vector<int>, 10> &rDistancesAnchor_Tag)
	{
		int counter = 0;
		while (counter < rDistancesAnchor_Tag.size())
		{
			int anchor_X = *pAnchors++;
			int anchor_Y = *pAnchors++;
			if (anchor_X >= 0 && anchor_Y >= 0)
			{
				for(int i = 0; i < rAllCoords_X.size(); i++)
				{
					rDistancesAnchor_Tag[counter].push_back(lround(sqrt(pow(anchor_X - rAllCoords_X[i], 2) + pow(anchor_Y - rAllCoords_Y[i], 2))));
					/*
					prints distances from tag to each anchor, delete forr final compilation
					*/
					cout << "Distance of : " << counter << " is: " << rDistancesAnchor_Tag[counter][i] << endl;
				}
			}
			counter++;
		}
	}
};
