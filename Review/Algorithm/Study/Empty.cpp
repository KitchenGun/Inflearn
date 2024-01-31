#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	vector<vector<int>> v;
	v.resize(10);
	for (int i = 0; i <= 9; i++)
	{
		v[i].resize(9);
	}

	int max =0;
	int x=0,y=0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin>>v[i][j];
			if (v[i][j]>max)
			{
				max = v[i][j];
				x = i;
				y = j;
			}
		}
	}

	cout<< max <<endl;
	cout<<x+1 <<" " << y + 1 << endl;
	
}