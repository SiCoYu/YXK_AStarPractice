#include "CAStar.h"
#include <algorithm>

bool GetLowestPoint(const APoint* p1,const APoint* p2)
{
    return p1->f < p2->f;
}

CAStar::CAStar():m_EndPoint(nullptr),m_CurPoint(nullptr)
{
	
}

CAStar::~CAStar()
{
	m_OpenList.clear();
    m_CloseList.clear();
    m_NeighbourList.clear();
    m_AllPoints.clear();
}

APoint* CAStar::FindWay(APoint* Start, APoint* End, vector<vector<APoint*>>& AllPoints)
{
	m_AllPoints = AllPoints;
	m_EndPoint = End;
	if (m_EndPoint->RetState == E_ResultState::E_BLOCK)
	{
		cout << "This point is block" << endl;
		return nullptr;
	}
	if (*m_EndPoint == *Start)
	{
		cout << "Start point is same to end point" << endl;
		return nullptr;
	}
	m_OpenList.push_back(Start);
	Start->RetState = E_ResultState::E_OPENED;
	Start->f = GetF(Start);
	do 
	{
		m_CurPoint = m_OpenList[0];
		m_OpenList.erase(m_OpenList.begin());
		m_CurPoint->RetState = E_ResultState::E_CLOSED;
		m_CloseList.push_back(m_CurPoint);

		if (*m_CurPoint == *m_EndPoint)
		{
			cout << "Success find way" << endl;
			return m_CurPoint;
		}
		vector<APoint*> NearVec = GetNeighboringPoint(m_CurPoint);
		for (int i = 0; i < NearVec.size(); ++i)
		{
			auto tmpoint = NearVec[i];
			if (tmpoint->RetState == E_ResultState::E_CLOSED)
			{
				continue;
			}
			if (tmpoint->RetState != E_ResultState::E_OPENED)
			{
				tmpoint->Parent = m_CurPoint;
				tmpoint->g = m_CurPoint->g + 10;
				tmpoint->h = GetH(tmpoint);
				m_OpenList.push_back(tmpoint);
				tmpoint->RetState = E_ResultState::E_OPENED;
			}
			else
			{
				if (tmpoint->h < m_CurPoint->h)
				{
					tmpoint->Parent = m_CurPoint;
					tmpoint->g = m_CurPoint->g + 10;
				}				
			}
		}
		sort(m_OpenList.begin(), m_OpenList.end(), GetLowestPoint);
	} while (m_OpenList.size() > 0);
	cout << "Failed find way" << endl;
	return nullptr;
}

int CAStar::GetF(APoint* Point)
{
	 return (Point->g + GetH(Point));
}

int CAStar::GetH(APoint* Point)
{
	return (abs(m_EndPoint->y - Point->y) + abs(m_EndPoint->x - Point->x))*10;
}

std::vector<APoint*> CAStar::GetNeighboringPoint(APoint* Point)
{
	m_NeighbourList.clear();
	if (Point->x < MAX_X - 1)
	{
		if (m_AllPoints[Point->x + 1][Point->y]->RetState != E_ResultState::E_BLOCK)
		{
			m_NeighbourList.push_back(m_AllPoints[Point->x + 1][Point->y]);
		}
	}
	if (Point->x > 0)
	{
		if (m_AllPoints[Point->x - 1][Point->y]->RetState != E_ResultState::E_BLOCK)
		{
			m_NeighbourList.push_back(m_AllPoints[Point->x - 1][Point->y]);
		}
	}
	if (Point->y < MAX_Y - 1)
	{
		if (m_AllPoints[Point->x][Point->y + 1]->RetState != E_ResultState::E_BLOCK)
		{
			m_NeighbourList.push_back(m_AllPoints[Point->x][Point->y + 1]);
		}
	}
	if (Point->y > 0)
	{
		if (m_AllPoints[Point->x][Point->y - 1]->RetState != E_ResultState::E_BLOCK)
		{
			m_NeighbourList.push_back(m_AllPoints[Point->x][Point->y - 1]);
		}
	}
	return m_NeighbourList;
}

APoint::APoint() : x(0),y(0),h(0),f(0),g(0),Parent(nullptr)
                ,RetState(E_ResultState::E_UNKNOWN)
{

}

APoint::~APoint()
{

}
