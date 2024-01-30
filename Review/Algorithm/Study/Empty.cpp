#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int x=0,y=0;
	cin >> x >> y;
	vector<vector<int>> arr;
	arr.resize(x);
	cin.ignore();
	for (int i = 0; i < x; i++)
	{
		arr[i].resize(y);
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			int temp;
			cin >> temp;
			arr[i][j] = temp;
		}
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			int temp;
			cin>>temp;
			arr[i][j] += temp;
		}
	}


	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout << endl;
	}

	return 0;
}