#include <iostream>
#include <vector>
using namespace std;

int n = 0, m = 0;
vector<vector<int>> a(n, vector<int>(m, 0));

int Cal(int x,int y,int StartColor)
{
	int count = 0;
	int Color = StartColor;
	if (x + 8 > n || y + 8 > m)
	{
		return 1000000; // Return a large number if the 8x8 square is out of bounds
	}

	for (int i = x; i < x+8; i++)
	{
		for (int j = y; j < y+8; j++)
		{
			if (((i-x) + (j-y)) % 2 == 0)//Â¦¼ö
			{
				if (a[i][j] != Color)
				{
					count++;
				}
			}
			else//È¦¼ö
			{
				if (a[i][j] == Color)
				{
					count++;
				}
			}
		}
	}
	return count;
}


int main()
{
	//ÀÔ·Â

	cin >> n >> m;

	a.resize(n, vector<int>(m, 0)); // Resize

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			char TempColor;
			cin >> TempColor;
			if (TempColor == 'W')
			{
				a[i][j] = 0;
			}
			else
			{
				a[i][j] = 1;
			}
		}
	}
	int result = 1000000; 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			result = min(result, Cal(i, j, 0)<Cal(i,j,1)?Cal(i,j,0): Cal(i, j, 1));
		}
	}

	cout << result;
}