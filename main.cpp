
#include <iostream>
#include "CAstar.h"

enum class E_Direction
{
	E_UP,
	E_DOWN,
	E_LEFT,
	E_RIGHT,
};

void printMap(char map[MAX_X][MAX_Y],int width,int height)
{
    for (int i = 0; i<width; i++)
    {
        for (int j = 0; j<height; j++)
        {
            printf("%c\t",map[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[])
{
	cout<<"---Map---"<<endl;
	char mapdata[MAX_X][MAX_Y] =
    {
        {'1','0','0','1','0','1','1','1','1','1'},
        {'1','1','1','1','0','1','1','1','1','1'},
        {'0','0','0','1','0','1','1','1','1','1'},
        {'1','0','0','1','0','1','1','1','1','0'},
        {'1','1','1','1','0','1','1','1','1','1'},
        {'1','1','0','0','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','1','1','1'},
        {'1','0','0','1','1','1','1','1','1','1'},
        {'1','1','0','0','1','1','1','1','1','1'},
        {'1','0','1','1','1','1','1','1','1','1'},
    };
	printMap(mapdata, MAX_X, MAX_Y);

	vector<vector<APoint*>> map;
	for (int i = 0; i < MAX_X; ++i)
	{
		vector<APoint*> tmp;
		for (int j = 0; j < MAX_Y; ++j)
		{
			APoint* point = new APoint();
			point->x = i;
			point->y = j;
			if (mapdata[i][j] == '0')
			{
				point->RetState = E_ResultState::E_BLOCK;
			}
			tmp.push_back(point);
		}
		map.push_back(tmp);
	}
	auto star = new CAStar();
	auto point = star->FindWay(map[3][3], map[0][5], map);;
	auto end_point = point;
	auto parent = point->Parent;
	if (!point || !parent)
    {
        return 0;
    }	
	mapdata[point->x][point->y] = 'E';
	E_Direction dir = E_Direction::E_UP;
	while (parent)
	{
		int delt_x = point->x - parent->x;
		int delt_y = point->y - parent->y;
		if (delt_x == 0)
		{
			if (delt_y > 0)
			{
				mapdata[point->x][point->y] = 0x1a;
				
			}
			else if (delt_y < 0)
			{
				mapdata[point->x][point->y] = 0x1b;
				
			}
		}
		if (delt_y == 0)
		{
			if (delt_x > 0)
			{
				
				mapdata[point->x][point->y] = 0x19;
			}
			else
			{
				mapdata[point->x][point->y] = 0x18;
				
			}
		}
		//cout<<point->x<<","<<point->y<<endl;
		point = point->Parent;
		parent = point->Parent;
		if (!parent)
		{
			mapdata[point->x][point->y] = 'S';
			break;
		}
	}
	mapdata[end_point->x][end_point->y] = 'E';
	
	cout<<"---Path---"<<endl;
    printMap(mapdata, MAX_X, MAX_Y);
	delete star;
    
    for (int i = 0; i<MAX_X; i++)
    {
        for (int j = 10; j<MAX_Y; j++)
        {
            delete map[i][j];
            map[i][j] = nullptr;
        }
    }

	system("pause");
	return 0;
}