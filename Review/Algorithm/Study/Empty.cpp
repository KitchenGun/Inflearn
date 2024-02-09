#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <queue>
using namespace std;

int main()
{
	int n;
	vector<vector<bool>> v(100, vector<bool>(100));
	cin >> n;
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		int a=0, b=0;
		
		cin>>a >> b;
		int amax=a+10,bmax=b+10;
		for (int x = a; x < amax; x++)
		{
			for (int y = b; y < bmax; y++)
			{
				if (v[x][y] == 0)
				{
					v[x][y] = 1;
					result++;
				}
			}
		}
	}
	cout<<result;
}