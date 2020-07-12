#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_X 10
#define MAX_Y 10

enum class E_ResultState
{
	E_UNKNOWN,
	E_CLOSED,
	E_OPENED,
	E_BLOCK,
};

class APoint
{
public:
	 APoint();
    ~APoint();
    int x;
    int y;
	E_ResultState RetState;
	int f;
    int g;
    int h;
	APoint *Parent;
	bool operator == (const APoint& po)
    {
        if (x == po.x && y == po.y)
        {
            return true;
        }
        return false;
    }
};

class CAStar
{
	vector<APoint*> m_OpenList;
	vector<APoint*> m_CloseList;
	vector<APoint*> m_NeighbourList;
	vector<vector<APoint*>> m_AllPoints;

	APoint* m_EndPoint;
	APoint* m_CurPoint;

public:
	CAStar();
	~CAStar();
	APoint* FindWay(APoint* Start, APoint* End, vector<vector<APoint*>>& AllPoints);

private:
	int GetF(APoint* Point);
	int GetH(APoint* Point);
	vector<APoint*> GetNeighboringPoint(APoint* Point);
};

